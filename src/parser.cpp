#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace ade {

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
bool ConfigParser::parse(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Failed to open " << filename << '\n';
    return false;
  }
  std::string line;
  while (std::getline(file, line)) {
    // Ignore comments and blank lines
    if (line.empty() || line[0] == '#') {
      continue;
    }

    // Split the line into key and value
    std::istringstream iss(line);
    std::string key;
    if (!std::getline(iss, key, '=')) {
      continue;
    }
    std::string value;
    if (!std::getline(iss, value)) {
      continue;
    }

    // Trim leading and trailing whitespace from key and value
    key.erase(0, key.find_first_not_of(" \t"));
    key.erase(key.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);

    // Parse the value based on the key's data type
    if (key == "start_state") {
      try {
        if (std::stoi(value) < 0) {
          std::cerr << "Invalid value for " << key << ": " << value << '\n';
          std::cerr << "It must be a positive integer\n";
          return false;
        }
        config_.processState = std::stoi(value);
      } catch (...) {
        std::cerr << "Invalid value for " << key << ": " << value << '\n';
        std::cerr << "It must be a positive integer\n";
        return false;
      }
    } else {
      std::cerr << "Invalid/Irrelevant key: " << key << '\n';
      std::cerr << "Ignoring...\n";
    }
  }
  return true;
}
/*****************************************************************************/
/*****************************************************************************/
bool ConfigParser::saveProcessState(const int processState, const std::string &filename) {
    std::ifstream inFile(filename);  // Open the file for reading
    std::stringstream buffer;
    buffer << inFile.rdbuf();  // Read the entire file into a stringstream
    std::string content = buffer.str();  // Convert the stringstream to a string
    inFile.close();  // Close the input file

    // Find the "start_state=" line and replace its value
    size_t pos = content.find("start_state=");
    if (pos != std::string::npos) {
        // Find the end of the current value
        size_t endPos = content.find("\n", pos);
        if (endPos == std::string::npos) {
            endPos = content.size();  // If no newline is found, set the end to the end of the file
        }

        // Replace the current start_state with the new value
        content.replace(pos + 12, endPos - pos - 12, std::to_string(processState));
    }

    // Write the modified content back to the file
    std::ofstream outFile(filename);  // Open the file for writing
    outFile << content;
    outFile.close();  // Close the output file
    return true;
}
/*****************************************************************************/
/*****************************************************************************/
const Config &ConfigParser::getConfig() const { return config_; }


} // namespace vbd