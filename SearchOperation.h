#ifndef YT_SEARCHOPERATION_H
#define YT_SEARCHOPERATION_H

// #include "OperationInterface.h"

#include <memory>
#include <unordered_map>

#include "Operation.h"
#include "SearchResponse.h"

namespace yt {
class SearchOperation : public Operation {
public:
  inline SearchOperation(std::string_view query) {
    parameters_["part"] = "snippet";
    parameters_["q"] = query;
  };

  SearchOperation &MaxResults(unsigned int maxResults);
  SearchOperation &ChannelId(std::string channelId);

  inline std::string GetActionName() const final { return "search"; }

  std::unique_ptr<SearchResponse> Perform();
};

inline SearchOperation Search(std::string_view query) {
  return SearchOperation(query);
}


} // namespace yt

#endif // YT_SEARCHOPERATION_H
