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
  enum SearchType : int {
    VIDEO = 1,
    PLAYLIST = 2,
    CHANNEL = 4,

    ALL = VIDEO | PLAYLIST | CHANNEL
  };

  inline SearchOperation(std::string_view query) {
    parameters_["part"] = "snippet";
    parameters_["q"] = query;
    // default
    Type(SearchType::VIDEO);
  };

  SearchOperation& ChannelId(std::string channelId);
  SearchOperation& MaxResults(unsigned int maxResults);
  SearchOperation& Type(SearchType type);

  inline std::string GetActionName() const final { return "search"; }

  std::unique_ptr<SearchResponse> Perform();
};

inline SearchOperation Search(std::string_view query) {
  return SearchOperation(query);
}


} // namespace yt

#endif // YT_SEARCHOPERATION_H
