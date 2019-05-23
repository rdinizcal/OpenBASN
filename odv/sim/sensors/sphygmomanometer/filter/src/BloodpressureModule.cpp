#include "BloodpressureModule.hpp"

using namespace odcore::base::module;
using namespace odcore::data;

using namespace bsn::range;
using namespace bsn::generator;
using namespace bsn::operation;
using namespace bsn::configuration;

using namespace bsn::msg::data;
using namespace bsn::msg::info;
using namespace bsn::msg::control;

BloodpressureModule::BloodpressureModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "bloodpressure"),
    buffer(),
    type("bloodpressure"),
    active(true),
    params({{"freq",0.90},{"m_avg",5}}),
    filterSystolic(5),
    filterDiastolic(5),
    {}

BloodpressureModule::~BloodpressureModule() {}

void BloodpressureModule::setUp() {
    addDataStoreFor(903, buffer);
    
}

void BloodpressureModule::tearDown() {
    
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode BloodpressureModule::body(){

    double dataS;
    double dataD;

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
      
        while(!buffer.isEmpty()){ // Receive control command and module update
            container = buffer.leave();

            data = container.getData<SensorData>().getData();
         
        /*
         * Module execution
         */
        
        // TASK: Filter data with moving average
            filterSystolic.setRange(params["m_avg"]);
            filterSystolic.insert(dataS, "bpms");
            dataS = filterSystolic.getValue("bpms");
           

            filterDiastolic.setRange(params["m_avg"]);
            filterDiastolic.insert(dataD, "bpmd");
            dataD = filterDiastolic.getValue("bpmd");
           
            SensorData sdata(type, data, risk);
            Container sdataContainer(sdata);
            getConference().send(sdataContainer);
        
            }
        }
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}
