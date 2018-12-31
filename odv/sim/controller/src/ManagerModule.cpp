#include "ManagerModule.hpp"

using namespace odcore::base::module;
using namespace odcore::data;

using namespace bsn::goalmodel;
using namespace bsn::msg::info; 

ManagerModule::ManagerModule(const int32_t  &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "manager"),
    buffer(),
    tasks(),
    contexts(),
    cost_formula(),
    reliability_formula() {}

ManagerModule::~ManagerModule() {}

void ManagerModule::setUp() {
    addDataStoreFor(700, buffer);

    { // set up cost and reliability formulae
        std::ifstream cost_file;
        try{
            cost_file.open("../formulae/cost.out");
            std::getline(cost_file,cost_formula);
            cost_file.close();
        } catch (std::ifstream::failure e) { std::cerr << "Exception opening/reading/closing file (cost.out)\n"; }

        std::ifstream reliability_file;
        try{
            reliability_file.open("../formulae/reliability.out");
            std::getline(reliability_file,reliability_formula);
            reliability_file.close();
        } catch (std::ifstream::failure e) { std::cerr << "Exception opening/reading/closing file (reliability.out)\n"; }

    }

    { // Set up map {id,object} of leaf task from goal model
        tasks.insert(std::pair<std::string,Task>("T1.11",Task("T1.11","Read data","W_G3_T1_11",0.3,"rTaskG3_T1_11",0.97)));
        tasks.insert(std::pair<std::string,Task>("T1.12",Task("T1.12","Filter data","W_G3_T1_12",0.4,"rTaskG3_T1_12",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.13",Task("T1.13","Transfer data","W_G3_T1_13",0.8,"rTaskG3_T1_13",0.9)));

        tasks.insert(std::pair<std::string,Task>("T1.21",Task("T1.21","Read data","W_G3_T1_21",0.4,"rTaskG3_T1_21",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.22",Task("T1.22","Filter data","W_G3_T1_22",0.4,"rTaskG3_T1_22",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.23",Task("T1.23","Transfer data","W_G3_T1_22",0.4,"rTaskG3_T1_22",0.95)));

        tasks.insert(std::pair<std::string,Task>("T1.31",Task("T1.31","Read data","W_G3_T1_31",0.3,"rTaskG3_T1_31",0.9)));
        tasks.insert(std::pair<std::string,Task>("T1.32",Task("T1.32","Filter data","W_G3_T1_32",0.3,"rTaskG3_T1_32",0.9)));
        tasks.insert(std::pair<std::string,Task>("T1.33",Task("T1.33","Transfer data","W_G3_T1_33",0.3,"rTaskG3_T1_33",0.9)));

        tasks.insert(std::pair<std::string,Task>("T1.411",Task("T1.411","Read diastolic","W_G3_T1_411",0.8,"rTaskG3_T1_411",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.412",Task("T1.412","Read systolic","W_G3_T1_412",0.8,"rTaskG3_T1_412",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.42",Task("T1.42","Filter data","W_G3_T1_42",0.8,"rTaskG3_T1_42",0.95)));
        tasks.insert(std::pair<std::string,Task>("T1.43",Task("T1.43","Transfer data","W_G3_T1_43",0.8,"rTaskG3_T1_43",0.95)));

        tasks.insert(std::pair<std::string,Task>("T2.1",Task("T2.1","Fuse sensor data","W_G4_T2_1",0.8,"rTaskG4_T2_1",0.93)));
        tasks.insert(std::pair<std::string,Task>("T2.2",Task("T2.2","Detect patient status","W_G4_T2_2",0.8,"rTaskG4_T2_2",0.93)));
        tasks.insert(std::pair<std::string,Task>("T2.3",Task("T2.3","Persist data","W_G4_T2_3",0.8,"rTaskG4_T2_3",0.93)));
    }

    { // Set up map {id,object} of context from goal model
        contexts.insert(std::pair<std::string,Context>("SaO2_available",Context("SaO2_available",true,"CTX_G3_T1_1")));
        contexts.insert(std::pair<std::string,Context>("ECG_available",Context("ECG_available",false,"CTX_G3_T1_2")));
        contexts.insert(std::pair<std::string,Context>("TEMP_available",Context("TEMP_available",false,"CTX_G3_T1_3")));
        contexts.insert(std::pair<std::string,Context>("ABP_available",Context("ABP_available",false,"CTX_G3_T1_4")));
    }
}

void ManagerModule::tearDown(){}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode ManagerModule::body(){

    Lepton::CompiledExpression cost_expression = Lepton::Parser::parse(cost_formula).createCompiledExpression();
    Lepton::CompiledExpression reliability_expression = Lepton::Parser::parse(reliability_formula).createCompiledExpression();
    
    std::map<std::string,double&> cost_formula_reliabilities;
    std::map<std::string,double&> cost_formula_costs;
    std::map<std::string,double&> cost_formula_contexts;

    std::map<std::string,double&> reliability_formula_reliabilities;
    std::map<std::string,double&> reliability_formula_contexts;

    for (std::pair<std::string,Task> task : tasks){
        cost_formula_reliabilities.insert(std::pair<std::string,double&>(task.second.getTask(),cost_expression.getVariableReference(task.second.getReliabilitySymbol())));
        cost_formula_costs.insert(std::pair<std::string,double&>(task.second.getTask(),cost_expression.getVariableReference(task.second.getCostSymbol())));
        reliability_formula_reliabilities.insert(std::pair<std::string,double&>(task.second.getTask(),reliability_expression.getVariableReference(task.second.getReliabilitySymbol())));
    }

    
    for (std::pair<std::string,Context> context : contexts) {
        cost_formula_contexts.insert(std::pair<std::string,double&>(context.second.getContext(),cost_expression.getVariableReference(context.second.getContextSymbol())));
        reliability_formula_contexts.insert(std::pair<std::string,double&>(context.second.getContext(),reliability_expression.getVariableReference(context.second.getContextSymbol())));
    }
    

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {

        while(!buffer.isEmpty()){

            Container container = buffer.leave();

            if(container.getDataType() == 700) { // update task properties

                std::string task_id = container.getData<TaskInfo>().getTask();
                double cost = container.getData<TaskInfo>().getCost();
                double reliability = container.getData<TaskInfo>().getReliability();

                tasks[task_id].setCost(cost);
                tasks[task_id].setReliability(reliability);

            } else if (container.getDataType() == 701) { // update context

                std::string context_id = container.getData<ContextInfo>().getContext();
                bool value = container.getData<ContextInfo>().getValue();

                // context operationalization here ?

                contexts[context_id].setValue(value);

            }
        }

        /*
        RT_FORMULA  
        if (we need adaptation) {
        */
        
        // plug in costs, reliabilities and contexts...
        { // in cost formula
            for (std::pair<std::string,double&> cost_formula_reliabiliy : cost_formula_reliabilities) {
                cost_formula_reliabiliy.second = tasks[cost_formula_reliabiliy.first].getReliability();
            }

            for (std::pair<std::string,double&> cost_formula_cost : cost_formula_costs) {
                cost_formula_cost.second = tasks[cost_formula_cost.first].getCost();
            }

            for (std::pair<std::string,double&> cost_formula_context : cost_formula_contexts) {
                bool val = contexts[cost_formula_context.first].getValue();
                cost_formula_context.second = val ? 1:0;
            }
        }

        
        { // in reliability formula

            for (std::pair<std::string,double&> reliability_formula_reliability : reliability_formula_reliabilities) {
                reliability_formula_reliability.second = tasks[reliability_formula_reliability.first].getReliability();
            }

            for (std::pair<std::string,double&> reliability_formula_context : reliability_formula_contexts) {
                bool val = contexts[reliability_formula_context.first].getValue();
                reliability_formula_context.second = val ? 1:0;
            }
        }
        

        //double value = expression.evaluate();
        std::cout << "cost_expression evaluates to " << cost_expression.evaluate() << std::endl;
        std::cout << "reliability_expression evaluates to " << reliability_expression.evaluate() << std::endl;

        /*
        } 
        */
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}
