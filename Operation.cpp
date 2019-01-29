#include "Operation.h"

#include "Config.h"
#include "CURLcontext.h"
#include "Query.h"

namespace yt {
  Operation::Operation() {
    parameters_["key"] = yt::Config::Get("api_key");
  }
}
