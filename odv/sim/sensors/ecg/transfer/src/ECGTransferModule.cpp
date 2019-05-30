#include "ECGTransferModule.hpp"
#include "bsn/libbsn/include/msg/MessageQueueCodes.hpp"

using namespace odcore::base::module;
using namespace odcore::data;

using namespace bsn::range;
using namespace bsn::generator;
using namespace bsn::operation;
using namespace bsn::configuration;

using namespace bsn::msg::data;
using namespace bsn::msg::info;
using namespace bsn::msg::control;

ECGTransferModule::ECGTransferModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "ecg"),
    buffer(),
    type("ecg"),
    battery("ecg_batt",100,100,1),
    available(true),
    data_accuracy(1),
    comm_accuracy(1),
    active(true),
    params({{"freq",0.9},{"m_avg",5}}),
    markov(),
    filter(5),
    sensorConfig(),
    persist(1),
    path("ecg_output.csv"),
    fp() {}

ECGTransferModule::~ECGTransferModule() {}

void ECGTransferModule::setUp() {
    //srand(time(NULL));
    addDataStoreFor(ECGTRANSFERMODULE_MSG_QUE, buffer);
    
    Operation op;
    
    std::vector<string> t_probs;
    std::array<float, 25> transitions;
    std::array<bsn::range::Range,5> ranges;

    { // Configure sensor configuration
        Range low_range = ranges[2];
        
        array<Range,2> midRanges;
        midRanges[0] = ranges[1];
        midRanges[1] = ranges[3];
        
        array<Range,2> highRanges;
        highRanges[0] = ranges[0];
        highRanges[1] = ranges[4];

        array<Range,3> percentages;

        vector<string> low_p = op.split(getKeyValueConfiguration().getValue<string>("global.lowrisk"), ',');
        percentages[0] = Range(stod(low_p[0]),stod(low_p[1]));

        vector<string> mid_p = op.split(getKeyValueConfiguration().getValue<string>("global.midrisk"), ',');
        percentages[1] = Range(stod(mid_p[0]),stod(mid_p[1]));

        vector<string> high_p = op.split(getKeyValueConfiguration().getValue<string>("global.highrisk"), ',');
        percentages[2] = Range(stod(high_p[0]),stod(high_p[1]));

        sensorConfig = SensorConfiguration(0,low_range,midRanges,highRanges,percentages);
    }

    { // Configure accuracy
        data_accuracy = getKeyValueConfiguration().getValue<double>("ecg.data_accuracy") / 100;
        comm_accuracy = getKeyValueConfiguration().getValue<double>("ecg.comm_accuracy") / 100;
    }

    { // Configure sensor persistency
        persist = getKeyValueConfiguration().getValue<int>("ecg.persist");
        path = getKeyValueConfiguration().getValue<std::string>("ecg.path");

        if (persist) {
            fp.open(path);
            fp << "ID,DATA,RISK,TIME_MS" << endl;
        }
    }
}

void ECGTransferModule::tearDown() {
    if (persist)
        fp.close();
}

void ECGTransferModule::sendTaskInfo(const std::string &task_id, const double &cost, const double &reliability, const double &frequency) {
    TaskInfo task(task_id, cost, reliability, frequency);
    Container taskContainer(task);
    getConference().send(taskContainer);
}

void ECGTransferModule::sendContextInfo(const std::string &context_id, const bool &value) {
    ContextInfo context(context_id, value, 0, 0, "");
    Container contextContainer(context);
    getConference().send(contextContainer);
}

void ECGTransferModule::sendMonitorTaskInfo(const std::string &task_id, const double &cost, const double &reliability, const double &frequency) {
    MonitorTaskInfo task(task_id, cost, reliability, frequency);
    Container taskContainer(task);
    getConference().send(taskContainer);
}

void ECGTransferModule::sendMonitorContextInfo(const std::string &context_id, const bool &value) {
    MonitorContextInfo context(context_id, value, 0, 0, "");
    Container contextContainer(context);
    getConference().send(contextContainer);
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode ECGTransferModule::body() {
  
    Container container;
    double data;
    double risk;
    bool first_exec = true;
    uint32_t id = 0;

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        
        if(first_exec){ // Send context info warning controller that this sensor is available
            sendContextInfo("ECG_available",true);
            sendMonitorContextInfo("ECG_available",true);
            first_exec = false; 
        }

        {  // update controller with task info
           
            sendContextInfo("ECG_available",true);
            sendTaskInfo("G3_T1.21",0.076,1,1);
            sendTaskInfo("G3_T1.22",0.076*params["m_avg"],1,1);
            sendTaskInfo("G3_T1.23",0.076,1,1);
           // and the monitor..
            sendMonitorContextInfo("ECG_available",true);
            sendMonitorTaskInfo("G3_T1.21",0.076,1,1);
            sendMonitorTaskInfo("G3_T1.22",0.076*params["m_avg"],1,1);
            sendMonitorTaskInfo("G3_T1.23",0.076,1,1);
        }

       
        while(!buffer.isEmpty()){ // Receive control command and module update
            container = buffer.leave();

            active = container.getData<ECGControlCommand>().getActive();
            params["freq"] = container.getData<ECGControlCommand>().getFrequency();
        }

       

        /*
         * Module execution
         */
        if((rand() % 100)+1 < int32_t(params["freq"]*100)){
            
            // TASK: Transfer information to CentralHub
            risk = sensorConfig.evaluateNumber(data);
            
            SensorData sdata(type, data, risk);
            Container sdataContainer(sdata);
            if((rand() % 100)+1 > int32_t(comm_accuracy*100)) getConference().send(sdataContainer);
            battery.consume(0.1);

            // for debugging
            //cout << "Risk: " << risk << "%"  << endl;
            
        }
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}
