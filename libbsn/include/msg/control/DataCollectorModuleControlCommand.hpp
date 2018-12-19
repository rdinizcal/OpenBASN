#ifndef DATACOLLECTORMODULE_CONTROL_COMMAND_H
#define DATACOLLECTORMODULE_CONTROL_COMMAND_H

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include <stdint.h>
#include <map>
#include <sstream>

namespace bsn {
    namespace msg {
        namespace control {
            
            class DataCollectorModuleControlCommand : public odcore::data::SerializableData {
            
                public:
                    DataCollectorModuleControlCommand(const bool &/*active*/, const std::map<std::string,double> &/*params*/);
    
                    DataCollectorModuleControlCommand();        
                    virtual ~DataCollectorModuleControlCommand();
                    
                    DataCollectorModuleControlCommand(const DataCollectorModuleControlCommand &/*obj*/);
                    DataCollectorModuleControlCommand& operator=(const DataCollectorModuleControlCommand &/*obj*/);
                
                // Métodos abstratos
                public:
                    virtual int32_t getID() const;
                    virtual const std::string getShortName() const;
                    virtual const std::string getLongName() const;

                    static int32_t ID();
                    static const std::string ShortName();
                    static const std::string LongName();
            
                public:
                    virtual std::ostream& operator<<(std::ostream &out) const;
                    virtual std::istream& operator>>(std::istream &in);
            
                    virtual const std::string toString() const;
                    
                // setters e getters
                public:
                    void setActive(const bool &/*active*/);
                    bool getActive() const;

                    void setParams(const std::map<std::string,double>  &/*params*/);
                    std::map<std::string,double> getParams() const;
                
                private:
                    bool active;
                    std::map<std::string,double> params;
            };
        }
    }
}

#endif