#include "SearchOperation.h"

#include <stdexcept>

#include "CURLcontext.h"

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

  std::unique_ptr<SearchResponse> SearchOperation::Perform() {

    return CURLcontext::Get<SearchResponse>({yt::API_SCHEME,
					     yt::API_AUTHORITY,
					     yt::API_PATH,
					     GetActionName(),
					     parameters_});
  }
}
