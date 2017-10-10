#include "BodyHubModule.h"

#include "openbasn/model/sensor/Sensor.h"
#include "openbasn/message/Acknowledge.h"

#include "opendavinci/generated/odcore/data/dmcp/PulseAckMessage.h"

#include <iostream>

#include <map>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::base::module;
using namespace odcore::data::dmcp;

using namespace openbasn::data;
using namespace openbasn::message;
using namespace openbasn::model::sensor;

BodyHubModule::BodyHubModule(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "bodyhub"),
    m_id(getIdentifier()),
    m_buffer(),
    m_health_risk("low"),
    m_sensornode(),
    m_sensornodedata_log(),
    m_status_log()
    {}

BodyHubModule::~BodyHubModule() {}

void BodyHubModule::setUp() {
    //setup buffer
    addDataStoreFor(871, m_buffer);
    addDataStoreFor(872, m_buffer);
    addDataStoreFor(873, m_buffer);

    //setup m_sensornodedata_log
    m_sensornodedata_log.open("sensornodedata_log.csv");
    
    //"SensorNode#ID, data, data, ..., Sensor risk category, Sent at, Received at, Processed at"
    m_sensornodedata_log << "SensorNode#ID,";
    for(uint32_t i = 0; i < getKeyValueConfiguration().getValue<uint32_t>("global.sensortypes"); i++) {
        uint32_t sensor_id = i+1;
        m_sensornodedata_log << getKeyValueConfiguration().getValue<string>("global.sensortype."+ to_string(sensor_id)) << ",";
    }
    m_sensornodedata_log << "Sensor risk category,Sent at,Received at,Processed at\n";

    m_status_log.open("status_log.csv");

    //"Active sensors,low risk,moderate risk,high risk,health risk,timestamp"
    m_status_log << "Active sensors,low risk,moderate risk,high risk,health risk,timestamp\n";
}

void BodyHubModule::tearDown() {
    m_sensornodedata_log.close();

    map<uint32_t,string>::iterator it = m_sensornode.begin();
    for(pair<uint32_t,string> element : m_sensornode){

        Request req(Request::UNREGISTER, m_id, element.first);
        Container c_req(req);
        getConference().send(c_req);

        m_sensornode.erase(element.first); 
        CLOG1 << "SensorNode" << element.first << " successfully unregistered." << endl;
    }
}

void BodyHubModule::processRequest(Request request){
    switch(request.getType()) {
        case Request::REGISTER : 
            {
                m_sensornode.insert(pair<uint32_t, string>(request.getSourceID(), "low"));
                Acknowledge ack(Acknowledge::OK, m_id, request.getSourceID()); 
                Container c_ack(ack);
                getConference().send(c_ack);
                CLOG1 << "SensorNode" << request.getSourceID() << " successfully registered." << endl;
            }
            break;
        case Request::UNREGISTER : 
            m_sensornode.erase(request.getSourceID()); 
            CLOG1 << "SensorNode" << request.getSourceID() << " successfully unregistered." << endl;
            break;
        default: break;
    }
}

void BodyHubModule::processSensorNodeData(SensorNodeData sensornodedata){

    //Evaluate and categorize data
    string sensor_risk_category = BodyHubModule::categorizeSensorNodeData(sensornodedata);
    
    //Take action if data has changed
    if(m_sensornode[sensornodedata.getSensorNodeID()].compare(sensor_risk_category) != 0){
        m_sensornode[sensornodedata.getSensorNodeID()] = sensor_risk_category;

        Request request(Request::SENSOR_DATA, m_id, sensornodedata.getSensorNodeID(), sensor_risk_category);
        Container c_req(request);
        getConference().send(c_req);
    }
}

string BodyHubModule::categorizeSensorNodeData(SensorNodeData sensornodedata) {
    
    int32_t sensor_risk = BodyHubModule::evaluateSensorDataRisk(sensornodedata.getSensorType(), sensornodedata.getSensorData());

    return (sensor_risk==0)?"low":(sensor_risk==1)?"moderate":(sensor_risk==2)?"high":"unknown";
}

int32_t BodyHubModule::evaluateSensorDataRisk(uint32_t type, double data) {
    
    switch(type){

        case Sensor::THERMOMETER:
            if(37 >= data && data > 35){
                return 0; 
            } else if ( (35 >= data && data > 30) || (38 >= data && data > 37) ) {
                return 1;
            } else if ( (50 >= data && data > 38) || (30 >= data && data > 0) ) {
                return 2;
            } else {
                return -1; 
            }
            break;

        case Sensor::ECG:
            if ( (150 >= data && data > 120) || (80 >= data && data > 0) ) {
                return 2;
            } else if (120 >= data && data > 80) {
                return 0;
            } else {
                return -1;
            }
            break;

        case Sensor::OXIMETER:
            if( 100 >= data && data > 94) {
                return 0;
            } else if ( 94 >= data && data > 90) {
                return 1;
            } else if ( 90 >= data && data > 0) {
                return 2;
            } else {
                return -1;
            }
            break;

        default:
            return -1;
            break;
    }
}

void BodyHubModule::persistSensorNodeData(SensorNodeData sensornodedata, TimeStamp sent_timestamp, TimeStamp received_timestamp){

    //"SensorNode#ID, data, data, ..., Sensor risk category, Sent at, Received at, Processed at"
    m_sensornodedata_log << "SensorNode#" << sensornodedata.getSensorNodeID() << ",";
    for(int32_t i = 0; i < getKeyValueConfiguration().getValue<int32_t>("global.sensortypes"); i++){
        int32_t sensor_id = i+1;
        if(sensornodedata.getSensorType() == sensor_id){
            m_sensornodedata_log << sensornodedata.getSensorData() << ",";
        } else {
            m_sensornodedata_log << "-,";
        }
    }

    m_sensornodedata_log << m_sensornode[sensornodedata.getSensorNodeID()] << ",";
    m_sensornodedata_log << sent_timestamp.getYYYYMMDD_HHMMSS() << ",";
    m_sensornodedata_log << received_timestamp.getYYYYMMDD_HHMMSS() << ",";
    m_sensornodedata_log << TimeStamp().getYYYYMMDD_HHMMSS() << "\n";
}

string BodyHubModule::calculateHealthRisk(){
    double hr = 0;
    for(uint32_t i = 0; i < m_sensornode.size(); i++){
        if (m_sensornode[i].compare("low") == 0) {
            hr += 0.1;
        } else if (m_sensornode[i].compare("moderate") == 0) {
            hr += 1;
        } else if (m_sensornode[i].compare("high") == 0) {
            hr += 5;
        } else {
            hr += 20;
        }
    }

    return (hr<=0)?"unknown":(hr<1)?"low":(hr<5)?"moderate":(hr<20)?"high":"unknown";
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode BodyHubModule::body() { 
    
    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        while(!m_buffer.isEmpty()){
            Container container = m_buffer.leave();

            if(container.getDataType() == Request::ID()) {
                BodyHubModule::processRequest(container.getData<Request>());
            } else if (container.getDataType() == SensorNodeData::ID()) {
                SensorNodeData sensornodedata = container.getData<SensorNodeData>(); 
                BodyHubModule::processSensorNodeData(sensornodedata);
                BodyHubModule::persistSensorNodeData(sensornodedata, container.getSentTimeStamp(), container.getReceivedTimeStamp());
            }
        } 

        
        //Evaluate and categorize health risk
        m_health_risk = BodyHubModule::calculateHealthRisk();

        //Persist Data
        //"Active sensors,low risk,moderate risk,high risk,health risk,timestamp"
        m_status_log << m_sensornode.size() << ",";

        uint32_t low=0;
        uint32_t moderate=0;
        uint32_t high=0;
        for(uint32_t i=0;  i < m_sensornode.size(); i++){
            
            if(m_sensornode[i].compare("low") == 0){
                low++;
            } else if(m_sensornode[i].compare("moderate") == 0) {
                moderate++;
            } else if(m_sensornode[i].compare("high") == 0) {
                high++;
            } else {
                unknown++;
            }
        }

        m_status_log << low << ",";
        m_status_log << moderate << ",";
        m_status_log << high << ",";
        m_status_log << m_health_risk << ",";
        m_status_log << TimeStamp().getYYYYMMDD_HHMMSS() << "\n"; 

        PulseAckMessage pulseackmessage;
        Container container(pulseackmessage);
        getConference().send(container);
    }
    
    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}