#include "BaseOperation.h"

#include "Config.h"
#include "CURLcontext.h"
#include "Query.h"

namespace yt {
Response BaseOperation::Perform() {
  parameters_["key"] = yt::Config::Get("api_key");

  return CURLcontext::Get({yt::API_SCHEME,
                           yt::API_AUTHORITY,
                           yt::API_PATH + GetActionName(),
                           parameters_});
}
}
