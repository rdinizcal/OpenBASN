#ifndef OXIMETER_COLLECT_MODULE_HPP
#define OXIMETER_COLLECT_MODULE_HPP

#include <fstream>
#include <chrono>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/FIFOQueue.h"

#include "bsn/range/Range.hpp"
#include "bsn/resource/Battery.hpp"
#include "bsn/generator/Markov.hpp"
#include "bsn/filters/MovingAverage.hpp"
#include "bsn/operation/Operation.hpp"
#include "bsn/configuration/SensorConfiguration.hpp"

#include "bsn/msg/data/SensorData.h"
#include "bsn/msg/info/TaskInfo.hpp"
#include "bsn/msg/info/ContextInfo.hpp"
#include "bsn/msg/info/MonitorTaskInfo.hpp"
#include "bsn/msg/info/MonitorContextInfo.hpp"
#include "bsn/msg/control/OximeterControlCommand.hpp"

class OximeterCollectModule : public odcore::base::module::TimeTriggeredConferenceClientModule{
    
	private:
      	OximeterCollect
		Module(const OximeterCollect
		Module &);
    	OximeterCollect
	Module &operator=(const OximeterCollect
	Module &);

    	virtual void setUp();
    	virtual void tearDown();

		void sendTaskInfo(const std::string &/*task_id*/, const double &/*cost*/, const double &/*reliability*/, const double &/*frequency*/);
		void sendContextInfo(const std::string &/*context_id*/, const bool &/*value*/);

		void sendMonitorTaskInfo(const std::string &/*task_id*/, const double &/*cost*/, const double &/*reliability*/, const double &/*frequency*/);
		void sendMonitorContextInfo(const std::string &/*context_id*/, const bool &/*value*/);

  	public:
    	OximeterCollect
	Module(const int32_t &argc, char **argv);
    	virtual ~OximeterCollect
	Module();

    	odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

  	private:
	    odcore::base::FIFOQueue buffer;
		
		std::string type;
		bsn::resource::Battery battery;
		bool available;
  
		double data_accuracy;
		double comm_accuracy;

		bool active;
		std::map<std::string,double> params;

		bsn::generator::Markov markov;
		bsn::filters::MovingAverage filter;
		bsn::configuration::SensorConfiguration sensorConfig;

		int persist;
		std::string path;
		std::ofstream fp;
};

#endif 