#ifndef YT_SEARCHOPERATION_H
#define YT_SEARCHOPERATION_H

#include "OperationInterface.h"

#include <unordered_map>

#include "BaseOperation.h"

namespace yt {
class SearchOperation : public BaseOperation {
public:
  inline SearchOperation(std::string_view query) {
    parameters_["part"] = "snippet";
    parameters_["q"] = query;
  };

  SearchOperation &MaxResults(unsigned int maxResults);
  SearchOperation &ChannelId(std::string channelId);

  inline std::string GetActionName() const final { return "search"; }
};

inline SearchOperation Search(std::string_view query) {
  return SearchOperation(query);
}
} // namespace yt

#endif // YT_SEARCHOPERATION_H
