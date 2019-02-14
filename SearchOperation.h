#ifndef YT_SEARCHOPERATION_H
#define YT_SEARCHOPERATION_H

// #include "OperationInterface.h"

#include <memory>
#include <unordered_map>

#include "Operation.h"
#include "SearchResponse.h"
#include "util.h"

namespace yt {
class SearchOperation : public Operation {
 public:
  // bitmask operators are enabled outside of class at the bottom of the file
  enum class SearchType : int {
    VIDEO = 0x1,
    PLAYLIST = 0x2,
    CHANNEL = 0x4,
    ANY = VIDEO | PLAYLIST | CHANNEL
  };

  enum class ChannelTypes {
    ANY,
    SHOW
  };

  enum class OrderTypes {
    DATE,
    RATING,
    RELEVANCE,
    TITLE,
    VIDEO_COUNT,
    VIEW_COUNT
  };

  enum class SafeSearchTypes {
    MODERATE,
    NONE,
    STRICT
  };

  enum class VideoCaptionTypes {
    ANY,
    CLOSED_CAPTION,
    NONE
  };

  enum class VideoDefinitionTypes {
    ANY,
    HIGH,
    STANDARD
  };

  enum class VideoDimensionTypes {
    THREE_D,
    TWO_D,
    ANY
  };

  // bitmask operators are enabled outside of class at the bottom of the file
  enum class VideoDurationTypes : int {
    LONG =   0x1,   // longer than 20 minutes
    MEDIUM = 0x2,   // between 4 and 20 minutes
    SHORT =  0x4,   // shorter than 4 minutes
    ANY = LONG | MEDIUM | SHORT
  };

  enum class VideoEmbeddableTypes {
    ANY,
    TRUE
  };

  enum class VideoLicenseTypes {
    ANY,
    CREATIVE_COMMON,
    YOUTUBE
  };

  enum class VideoSyndicatedTypes {
    ANY,
    TRUE
  };

  enum class VideoTypes {
    ANY,
    EPISODE,
    MOVIE
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
  SearchOperation& ForContentOwner(bool forContentOwner);
  SearchOperation& ForDeveloper(bool forDeveloper);
  SearchOperation& ForMine(bool forMine);
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
  /**
   * \param publishedAfter Time in UTC
   */
  SearchOperation& PublishedAfter(time_t publishedAfter);
  /**
   * \param publishedAfter RFC 3339 formatted date-time value
   *                       (1970-01-01T00:00:00Z)
   */
  SearchOperation& PublishedAfter(std::string_view publishedAfter);
  /**
   * \param publishedBefore Time in UTC
   */
  SearchOperation& PublishedBefore(time_t publishedBefore);
  /**
   * \param publishedBefore RFC 3339 formatted date-time value
   *                       (1970-01-01T00:00:00Z)
   */
  SearchOperation& PublishedBefore(std::string_view publishedBefore);
  SearchOperation& ChannelType(ChannelTypes channelType);
  SearchOperation& Order(OrderTypes order);
  SearchOperation& VideoCaption(VideoCaptionTypes videoCaption);
  SearchOperation& SafeSearch(SafeSearchTypes safeSearch);
  SearchOperation& VideoDefinition(VideoDefinitionTypes videoDefinition);
  SearchOperation& VideoDimension(VideoDimensionTypes videoDimension);
  SearchOperation& VideoDuration(VideoDurationTypes videoDuration);
  SearchOperation& VideoEmbeddable(VideoEmbeddableTypes videoEmbeddable);
  SearchOperation& VideoLicense(VideoLicenseTypes videoLicense);
  SearchOperation& VideoSyndicated(VideoSyndicatedTypes videoSyndicated);
  SearchOperation& VideoType(VideoTypes videoType);


  inline std::string GetActionName() const final { return "search"; }

  std::unique_ptr<SearchResponse> Perform();
};

inline SearchOperation Search(std::string_view query) {
  return SearchOperation(query);
}

ENABLE_BITMASK_OPERATORS(SearchOperation::SearchType)
ENABLE_BITMASK_OPERATORS(SearchOperation::VideoDurationTypes)

} // namespace yt

#endif // YT_SEARCHOPERATION_H
