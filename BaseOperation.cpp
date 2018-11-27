#include "BaseOperation.h"
#include "Config.h"

#include <iostream>

namespace yt {
Response BaseOperation::Perform() {
  std::string query = yt::API_URI + GetActionName() +
      "?key=" + yt::Config::Get("api_key") + '&';

  for (auto &parameter : parameters_) {
    query += parameter.first + '=' + parameter.second + '&';
  }

  return Response{query, ""};
}
}
