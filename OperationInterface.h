#ifndef YT_OPERATIONINTERFACE_H
#define YT_OPERATIONINTERFACE_H

#include <string>

#include "Response.h"

namespace yt {
const std::string API_SCHEME = "https";
const std::string API_AUTHORITY = "www.googleapis.com";
const std::string API_PATH = "/youtube/v3/";

class OperationInterface {
 public:
  virtual ~OperationInterface() {};

  virtual Response Perform() = 0;
};
}

#endif // YT_OPERATIONINTERFACE_H
