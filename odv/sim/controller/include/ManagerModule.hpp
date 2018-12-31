#ifndef MANAGER_MODULE_HPP
#define MANAGER_MODULE_HPP

#include <map>
#include <iostream>
#include <fstream>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/FIFOQueue.h"

#include "bsn/goalmodel/Task.hpp"
#include "bsn/goalmodel/Context.hpp"

#include "bsn/msg/info/TaskInfo.hpp"
#include "bsn/msg/info/ContextInfo.hpp"

#include "lepton/Lepton.h"

class ManagerModule : public odcore::base::module::TimeTriggeredConferenceClientModule {

    private:
      	ManagerModule(const ManagerModule &);
    	ManagerModule &operator=(const ManagerModule &);

    	virtual void setUp();
    	virtual void tearDown();

  public:
    	ManagerModule(const int32_t &argc, char **argv);
    	virtual ~ManagerModule();

    	odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

  	private:
		odcore::base::FIFOQueue buffer;

		std::map<std::string, bsn::goalmodel::Task> tasks;
		std::map<std::string, bsn::goalmodel::Context> contexts;

		std::string cost_formula;
		std::string reliability_formula;
};

#endif 