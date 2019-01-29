#ifndef YT_QUERY_H
#define YT_QUERY_H

#include <string>
#include <unordered_map>

namespace yt {
struct Query {
  // https://www.example.com/path/action?param1=val1&param2=val2
  // ^^^^^   ^^^^^^^^^^^^^^ ^^^^^^ ^^^^^ ^^^^^^^^^^^^^^^^^^^^^^^
  // scheme     authority    path action        parameters

  const std::string scheme;
  const std::string authority;
  const std::string path;
  const std::string action;
  const std::unordered_map<std::string, std::string>& parameters;
};
}

#endif // YT_QUERY_H
