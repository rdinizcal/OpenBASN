#include "SensorNodeModule.h"

#include "openbasn/data/SensorData.h"
#include "openbasn/model/sensor/Sensor.h"

#include <iostream>

using namespace std;

using namespace odcore;
using namespace odcore::data;
using namespace odcore::base::module;

using namespace openbasn::data;
using namespace openbasn::model::sensor;


SensorNodeModule::SensorNodeModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "SensorNodeModule"),
    m_id(getIdentifier())
     {}

SensorNodeModule::~SensorNodeModule() {}

void SensorNodeModule::setUp() {}

void SensorNodeModule::tearDown() {}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode SensorNodeModule::body() { 

    //Instantiate Sensors
    Sensor thermometer(Sensor::THERMOMETER, 2, true, 36, 2);
    Sensor ecg(Sensor::ECG, 2, true, 90, 30);

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        if(thermometer.isActive()){
            SensorData sd(m_id, thermometer.getSensorType(), thermometer.getData());
            Container c(sd);
            getConference().send(c);
            cout << sd.toString() << " sent." << endl;
        }

        if(ecg.isActive()) {
            SensorData sd(m_id, ecg.getSensorType(), ecg.getData());
            Container c(sd);
            getConference().send(c);
            cout << sd.toString() << " sent." << endl;
        }
    }
    
return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}