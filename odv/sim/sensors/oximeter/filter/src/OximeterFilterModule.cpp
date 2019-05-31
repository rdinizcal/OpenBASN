#include "OximeterFilterModule.hpp"
#include "bsn/msg/MessageQueueCodes.hpp"

using namespace odcore::base::module;
using namespace odcore::data;

using namespace bsn::range;
using namespace bsn::generator;
using namespace bsn::operation;
using namespace bsn::configuration;

using namespace bsn::msg::taskMsg;

OximeterFilterModule::OximeterFilterModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "oximeter"),
    buffer(),
    type("oximeter"),
    active(true),
    params({{"freq",0.90},{"m_avg",5}}),
    filter(5)
    {}

OximeterFilterModule::~OximeterFilterModule() {}

void OximeterFilterModule::setUp() {
    
    addDataStoreFor(OXIMETERFILTERMODULE_MSG_QUE, buffer);
}

void OximeterFilterModule::tearDown() {
    
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode OximeterFilterModule::body(){

    Container container;
    double data;
    double type;
    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        
        
        /*
         * Module execution
         */
        while(!buffer.isEmpty()){ // Receive control command and module update
            container = buffer.leave();

            data = container.getData<OximeterCollectTaskMsg>().getData();
            
         // TASK: Filter data with moving average
            filter.setRange(params["m_avg"]);
            filter.insert(data, type);
            data = filter.getValue(type);
            
            data = data*noise;
            bool passou = Oraculo(data);

            if(!passou)
                sleep(TIMEOUT_PADRAO_ECG_FAULT_TOLERANCE);

            OximeterFilterTaskMsg sdata(data);
            Container filterContainer(sdata);
            getConference().send(filterContainer);

        }
    }
    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}