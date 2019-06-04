#include "ECGTransferModule.hpp"

using namespace odcore::base::module;
using namespace odcore::data;

using namespace bsn::range;
using namespace bsn::operation;
using namespace bsn::configuration;

using namespace bsn::msg::taskMsg;

ECGTransferModule::ECGTransferModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "ecgtransfer"),
    buffer(),
    type("ecg"),
    active(true),
    params({{"freq",0.9},{"m_avg",5}}),
    sensorConfig(),
    falhaRand()
    {}

ECGTransferModule::~ECGTransferModule() {}

void ECGTransferModule::setUp() {
    addDataStoreFor(ECGFILTERMODULE_MSG_QUE, buffer);
    addDataStoreFor(ECGTRANSFERMODULE_MSG_QUE, buffer);
    
    Operation op;
    
    std::vector<string> t_probs;
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

}

void ECGTransferModule::tearDown() {

}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode ECGTransferModule::body() {
  
    Container container;
    double filterResponse;
    double risk;

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {


        
        if (buffer.isEmpty()){
            //Falha
            usleep(40000);
        }
        

        while(!buffer.isEmpty()){ // Receive control command and module update
            container = buffer.leave();


            if (container.getDataType()!=ECGFILTERMODULE_MSG_QUE){
                //Falha : A mensagem recebida não é do tipo esperado
                usleep(40000);
            }


            filterResponse = container.getData<ECGFilterTaskMessage>().getData();
            
            

            // TASK: Transfer information to CentralHub
            risk = sensorConfig.evaluateNumber(filterResponse);
            

            if(falhaRand.seOcorreuFalha() ){
                    //Falha
                    usleep(40000);
            }

            ECGTransferTaskMessage data(risk);
            Container transferContainer(data);
            getConference().send(transferContainer);
       }
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}
