#ifndef CENTRALHUB_MODULE_HPP
#define CENTRALHUB_MODULE_HPP

#include <fstream>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/FIFOQueue.h"

#include "bsn/processor/Processor.hpp"
#include "bsn/communication/TCPSend.hpp"

#include "bsn/msg/data/SensorData.h"
#include "bsn/msg/info/PatientStatusInfo.h"


class CentralhubModule : public odcore::base::module::TimeTriggeredConferenceClientModule{
    private:
        CentralhubModule(const CentralhubModule & /*obj*/);
        CentralhubModule &operator=(const CentralhubModule & /*obj*/);
        virtual void setUp();
        virtual void tearDown();        

    public:
        CentralhubModule(const int32_t &argc, char **argv);
        virtual ~CentralhubModule();

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

    private:
        odcore::base::FIFOQueue buffer;

        uint32_t connect;
        uint32_t port;
        std::string ip;
        
        uint32_t persist;
        std::ofstream fp;
        std::string path;
};

#endif 