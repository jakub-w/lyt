#ifndef YT_UTIL_H
#define YT_UTIL_H

#include <regex>
#include <string_view>

namespace yt {
  const std::regex DATE_REGEX{
      "\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}(?:.\\d{3})?Z"};

  inline bool check_date(std::string_view date_str) {
    return std::regex_match(date_str.begin(), date_str.end(), DATE_REGEX);
  }
}


#endif // YT_UTIL_H
