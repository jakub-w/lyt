#include "SearchOperation.h"

#include <stdexcept>

namespace yt {
SearchOperation& SearchOperation::MaxResults(unsigned int maxResults) {
  if (maxResults > 50)
    throw std::invalid_argument(
        std::string("In function ") + __PRETTY_FUNCTION__ +
        ": max maxResults is 50, " + std::to_string(maxResults) +
        " was given.");

  parameters_["maxResults"] = std::to_string(maxResults);

  return *this;
}
SearchOperation& SearchOperation::ChannelId(std::string channelId) {
  parameters_["channelId"] = channelId;

  return *this;
}
}
