#ifndef DATA_PROCESSOR_HPP
#define DATA_PROCESSOR_HPP

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <fstream>
#include <unistd.h>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/FIFOQueue.h"

#include "bsn/configuration/SensorConfiguration.hpp"
#include "bsn/operation/Operation.hpp"
#include "bsn/processor/Processor.hpp"
#include "bsn/data/SensorData.h"
#include "bsn/range/Range.hpp"
#include "bsn/data/ResourceUpdate.h"
#include "bsn/data/PatientStatusInfo.h"

class DataProcessor : public odcore::base::module::TimeTriggeredConferenceClientModule{
    private:
        DataProcessor(const DataProcessor & /*obj*/);
        DataProcessor &operator=(const DataProcessor & /*obj*/);
        virtual void setUp();
        virtual void tearDown();        
        void print_packs();

    public:
        /**
         * Construtor e destrutor da classe.
        */
        DataProcessor(const int32_t &argc, char **argv);
        virtual ~DataProcessor();

        /**
         * Método efetivamente executado.
        */
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

    private:
        std::vector<std::list<double>> packets_received;
        odcore::base::FIFOQueue data_buffer;
};

#endif 