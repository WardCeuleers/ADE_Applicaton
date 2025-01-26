#include <iostream>
#include <vector>
#include <ADE.hpp>

namespace ade{
/*****************************************************************************/
/*****************************************************************************/
void ProductionProcess::run() {
    while (processing_state_ < size_) {
        if (workflow_[processing_state_] == "A" or workflow_[processing_state_] == "a" ) {
            process_station_A();
        } else if (workflow_[processing_state_] == "B" or workflow_[processing_state_] == "b") {
            process_station_B();
        } else if (workflow_[processing_state_] == "C" or workflow_[processing_state_] == "c") {
            process_station_C();
        }
    }
}
/*****************************************************************************/
/*****************************************************************************/
void ProductionProcess::process_station_A() {
    product_state_++;
    processing_state_++;
    count_A_++;
}
void ProductionProcess::process_station_B() {
    product_state_--;
    processing_state_++;
    count_B_++;
}
void ProductionProcess::process_station_C() {
    if (product_state_%2 == 0) {
        processing_state_ += 2;
    } else {
        processing_state_++;
    }
    count_C_++;
}
/*****************************************************************************/
/*****************************************************************************/
bool ProductionProcess::isValidStep(std::string &str) {
    for (size_t i = 0; i < nb_stations_; i++) {
        if (str == workStations_[i]) {
            return true;
        }
    }
  return false;
}
/*****************************************************************************/
/*****************************************************************************/
bool ProductionProcess::askForWorkFlowStep(std::string &input) {
  std::cin >> input;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cout << "The input was not a string. Please try again.\n";
    return false;
  }
  else if (!isValidStep(input)) {
    std::cout << "The input was not a valid workstation. Please try again.\n";
    return false;
  }
  return true;
}
/*****************************************************************************/
/*****************************************************************************/
void ProductionProcess::askWorkFlow() {
    std::string input;
    std::cout << "Please enter the first step in the workflow: ";
    while (!askForWorkFlowStep(input));
    workflow_[0] = input;

    for (int i = 1; i < size_; i++) {
        std::cout << "Please enter the next step in the workflow: ";
        while (!askForWorkFlowStep(input));
        workflow_[i] = input;
    }
}
/*****************************************************************************/
/*****************************************************************************/
void ProductionProcess::showResult() {
    std::cout << "The final product state is: " << product_state_ << std::endl;
    std::cout << "The number of times each station was processed is as follows: \n";
    std::cout << "Station A was processed " << count_A_ << " times"<< std::endl;
    std::cout << "Station B was processed " << count_B_ << " times"<< std::endl;
    std::cout << "Station C was processed " << count_C_ << " times"<< std::endl;
};

} // namespace ade