#ifndef OXIMETER_TRANSFER_MODULE_HPP
#define OXIMETER_TRANSFER_MODULE_HPP

#include <fstream>
#include <chrono>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/FIFOQueue.h"

#include "bsn/range/Range.hpp"
#include "bsn/filters/MovingAverage.hpp"

#include "bsn/msg/data/SensorData.h"

class OximeterModule : public odcore::base::module::TimeTriggeredConferenceClientModule{
    
	private:
      	OximeterModule(const OximeterModule &);
    	OximeterModule &operator=(const OximeterModule &);

    	virtual void setUp();
    	virtual void tearDown();

  	public:
    	OximeterModule(const int32_t &argc, char **argv);
    	virtual ~OximeterModule();

    	odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

  	private:
	    odcore::base::FIFOQueue buffer;
		std::string type;
		bool active;
		std::map<std::string,double> params;
		bsn::filters::MovingAverage filter;
};

#endif 