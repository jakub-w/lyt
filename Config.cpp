#include "Config.h"

namespace yt {
// Define static variables
const std::string Config::conf_file = "config.txt";
std::unordered_map<std::string, std::string> Config::config_ = {};
bool Config::is_loaded_ = false;

// Define methods
void Config::Load() {
  std::ifstream fs(conf_file);
  if (false == fs.is_open())
    throw std::runtime_error("File could not be read: " + conf_file);

  for (std::string line; std::getline(fs, line);) {
    std::smatch smatch;
    if (false == std::regex_match(line, smatch,
                                  std::regex("(\\w+)\\s?=\\s?(\\S+)"))) {
      std::cerr << "Line: '" << line << "' could not be parsed.\n";
      continue;
    }

    config_[smatch[1]] = smatch[2];
  }

  is_loaded_ = true;
}

const std::string& Config::Get(std::string_view variable) {
  if (false == is_loaded_) Load();

  return config_[variable.data()];
}
}
