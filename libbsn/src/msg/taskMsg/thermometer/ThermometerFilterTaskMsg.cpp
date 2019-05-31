#include "bsn/msg/taskMsg/thermometer/ThermometerFilterTaskMsg.hpp"
#include "bsn/msg/MessageQueueCodes.hpp"

namespace bsn {
    namespace msg { 
        namespace taskMsg {
        
            using namespace std;

            ThermometerFilterTaskMessage::ThermometerFilterTaskMessage() : data() {}

            ThermometerFilterTaskMessage::ThermometerFilterTaskMessage(const double &_data) : data(_data) {}

            ThermometerFilterTaskMessage::~ThermometerFilterTaskMessage() {}
            
            ThermometerFilterTaskMessage::ThermometerFilterTaskMessage(const ThermometerFilterTaskMessage &obj) :
                SerializableData(),
                data(obj.getData())
                {}
                
            
            ThermometerFilterTaskMessage& ThermometerFilterTaskMessage::operator=(const ThermometerFilterTaskMessage &obj) {
                data = obj.getData();
                return (*this);
            }
            
            int32_t ThermometerFilterTaskMessage::ID() {
                return THERMFILTERMODULE_MSG_QUE;
            }
            const string ThermometerFilterTaskMessage::ShortName() {
                return "ThermometerFilterTaskMessage";
            }
            const string ThermometerFilterTaskMessage::LongName() {
                return "taskMsg.thermometer.ThermometerFilterTaskMessage";
            }
            
            int32_t ThermometerFilterTaskMessage::getID() const {
                return ThermometerFilterTaskMessage::ID();
            }
            const string ThermometerFilterTaskMessage::getShortName() const {
                return ThermometerFilterTaskMessage::ShortName();
            }
            const string ThermometerFilterTaskMessage::getLongName() const {
                return ThermometerFilterTaskMessage::LongName();
            }
            
            
            void ThermometerFilterTaskMessage::setData(const double &_data) {
                data = _data;
            }

            double ThermometerFilterTaskMessage::getData() const {
                return data;
            }

            ostream& ThermometerFilterTaskMessage::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();
                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);
                
                s->write(1, data);
                return out;
            }
            
            istream& ThermometerFilterTaskMessage::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();
                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);
                
                d->read(1, data);
                return in;
            }
            
            const string ThermometerFilterTaskMessage::toString() const {
                stringstream sstr;

                sstr << "ThermometerFilterTaskMessage#" << endl;
                sstr << "Data: " << data << endl;

                return sstr.str();
            }
        }
    }
}