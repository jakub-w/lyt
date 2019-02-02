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

  SearchOperation& ChannelId(std::string_view channelId);
  SearchOperation& MaxResults(unsigned int maxResults);
  SearchOperation& Type(SearchType type);
  // Type must be set to VIDEO
  SearchOperation& ForContentOwner(bool forContentOwner);
  SearchOperation& ForDeveloper(bool forDeveloper);
  // Type must be set to VIDEO
  SearchOperation& ForMine(bool forMine);
  // Type must be set to VIDEO
  SearchOperation& RelatedToVideoId(std::string_view relatedToVideoId);
  SearchOperation& EventType(std::string_view eventType);
  SearchOperation& Location(std::string_view location);
  SearchOperation& LocationRadius(std::string_view locationRadius);
  SearchOperation& OnBehalfOfContentOwner(
      std::string_view onBehalfOfContentOwner);
  SearchOperation& PageToken(std::string_view pageToken);
  SearchOperation& RegionCode(std::string_view regionCode);
  SearchOperation& RelevanceLanguage(std::string_view relevanceLanguage);
  SearchOperation& TopicId(std::string_view topicId);
  SearchOperation& VideoCategoryId(std::string_view videoCategoryId);
  // publishedAfter - time in UTC
  SearchOperation& PublishedAfter(time_t publishedAfter);
  // publishedAfter - RFC 3339 formatted date-time value
  //                  (1970-01-01T00:00:00Z)
  SearchOperation& PublishedAfter(std::string_view publishedAfter);
  // publishedBefore - time in UTC
  SearchOperation& PublishedBefore(time_t publishedBefore);
  // publishedBefore - RFC 3339 formatted date-time value
  //                   (1970-01-01T00:00:00Z)
  SearchOperation& PublishedBefore(std::string_view publishedBefore);

  // TODO:
  // channelType enum
  // order enum
  // videoCaption enum
  // safeSearch enum
  // videoDefinition enum
  // videoDimension enum
  // videoDuration enum
  // videoEmbeddable enum
  // videoLicense enum
  // videoSyndicated enum
  // videoType enum


  inline std::string GetActionName() const final { return "search"; }

  std::unique_ptr<SearchResponse> Perform();
};

inline SearchOperation Search(std::string_view query) {
  return SearchOperation(query);
}


} // namespace yt

#endif // YT_SEARCHOPERATION_H
