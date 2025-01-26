#include <iostream>
#include <memory>
#include <vector>

namespace ade{

class ProductionProcess {
  public:
  using size_t = std::size_t;
    // Constructor
   ProductionProcess(size_t size, int product_state) {
    product_state_ = product_state;
    processing_state_ = 0;
    size_ = size;
    workflow_.resize(size_);
    count_A_ = 0;
    count_B_ = 0;
    count_C_ = 0;
    askWorkFlow();
  };
    // Getters
    int get_processing_state() {return processing_state_;};
    int get_product_state() {return product_state_;};
    // Deconstructor
    ~ProductionProcess() = default;

    // Methods
    void run();
    void process_station_A();
    void process_station_B();
    void process_station_C();
    bool isValidStep(std::string &str);
    bool askForWorkFlowStep(std::string &input);
    void askWorkFlow();
    void showResult();

  private:
    int product_state_;
    int processing_state_;
    int count_A_;
    int count_B_;
    int count_C_;
    std::vector<std::string> workflow_;
    size_t size_; //nb of steps in the workflow
    std::vector<std::string> workStations_ = {"A","B","C","a","b","c"};
    size_t nb_stations_ = 6;
 
};

} // namespace ade