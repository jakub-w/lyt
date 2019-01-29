#ifndef YT_OPERATION_H
#define YT_OPERATION_H

#include <unordered_map>

namespace yt {
  const std::string API_SCHEME = "https";
  const std::string API_AUTHORITY = "www.googleapis.com";
  const std::string API_PATH = "/youtube/v3/";

class Operation {
 protected:
  std::unordered_map<std::string, std::string> parameters_;

 public:
  Operation();
  virtual ~Operation() {}

  virtual std::string GetActionName() const = 0;
};
}

#endif // YT_OPERATION_H
