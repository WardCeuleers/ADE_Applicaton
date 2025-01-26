#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>

namespace ade {

using size_t = std::size_t;

struct Config {
  int processState = 0;
};

// Singleton parser classs
class ConfigParser {
public:
  static ConfigParser &getInstance() {  // static such that there can only be one instance of the ConfigParser
    static ConfigParser instance;       // Create the ConfigParser called Instance when getInstance is called for the first time
    return instance;
  }

  bool parse(const std::string &filename); 
  const Config &getConfig() const;     // getter that can't change any class members and returns a reference of which you cannot change the content

  bool saveProcessState(const int processState, const std::string &filename);

  ConfigParser(ConfigParser const &) = delete;    // delete the copy constructor
  void operator=(ConfigParser const &) = delete;  // delete the assignment operator

private:
  ConfigParser() = default; // Private constructor
  Config config_;
  std::vector<std::string> parseVectorString(const std::string &str);
};

} // namespace ade
#endif // CONFIG_PARSER_HPP