#ifndef YT_OPERATIONINTERFACE_H
#define YT_OPERATIONINTERFACE_H

#include <string>

#include "Response.h"

namespace yt {
const std::string API_URI = "https://www.googleapis.com/youtube/v3/";

class OperationInterface {
 public:
  virtual ~OperationInterface() {};

  virtual Response Perform() = 0;
};
}

#endif // YT_OPERATIONINTERFACE_H
