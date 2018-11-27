#ifndef YT_BASEOPERATION_H
#define YT_BASEOPERATION_H

#include "OperationInterface.h"

#include <unordered_map>

namespace yt {
class BaseOperation : public OperationInterface {
 protected:
  std::unordered_map<std::string, std::string> parameters_;

 public:
  virtual Response Perform();

  virtual std::string GetActionName() const = 0;
};
}

#endif // YT_BASEOPERATION_H
