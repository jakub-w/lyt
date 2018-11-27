#ifndef YT_SEARCHOPERATION_H
#define YT_SEARCHOPERATION_H

#include "OperationInterface.h"

#include <unordered_map>

#include "BaseOperation.h"

namespace yt {
class SearchOperation : public BaseOperation {
public:
  inline SearchOperation(const std::string& query) {
    parameters_["part"] = "snippet";
    parameters_["q"] = query;
  };

  SearchOperation &MaxResults(unsigned int maxResults);
  SearchOperation &ChannelId(std::string channelId);

  inline virtual std::string GetActionName() const { return "search"; }
};

inline SearchOperation Search(const std::string& query) {
  return SearchOperation(query);
}
} // namespace yt

#endif // YT_SEARCHOPERATION_H
