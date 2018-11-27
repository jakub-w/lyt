#ifndef YT_CONFIG_H
#define YT_CONFIG_H

#include <fstream>
#include <iostream>
#include <regex>
#include <string_view>
#include <unordered_map>

namespace yt {
class Config {
  static const std::string conf_file;
  static std::unordered_map<std::string, std::string> config_;
  static bool is_loaded_;

  static void Load();

public:
  static const std::string& Get(std::string_view variable);
};
}

#endif // YT_CONFIG_H
