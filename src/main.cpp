#include <ADE.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <parser.hpp>

bool askNbofSteps(int &number) {
  std::cout << "Please enter the number of steps in the workflow: ";
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cout << "The input was not a integer. Please try again.\n";
    return false;
  }
  return true;
}

int main () {
    // Retrieve stored data
    ade::ConfigParser &parser = ade::ConfigParser::getInstance();
    std::cout << "########################### Parsing results: ####"
                    "########################## \n";
    if (!parser.parse("process_data.txt")) {
        std::cout << "Error parsing process data" << std::endl;
        return 1;
    } else {
        std::cout << "Stored stored product state is "<<  parser.getConfig().processState << std::endl;
    }
    std::cout << "########################### Input: ####"
                    "########################## \n";
    // ask for number of steps in the workflow
    int nb_production_steps;
    while (!askNbofSteps(nb_production_steps));

    // Create the production process
    ade::ProductionProcess process(nb_production_steps, parser.getConfig().processState);
    process.run();
    process.showResult();
    // save process state
    parser.saveProcessState(process.get_product_state(), "process_data.txt");
}