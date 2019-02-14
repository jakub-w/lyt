#include "SearchOperation.h"

#include <stdexcept>

#include "CURLcontext.h"
#include "util.h"

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
SearchOperation& SearchOperation::Type(SearchType type) {
  auto& temp_type = parameters_["type"];
  temp_type = "";

  if ((type & SearchType::VIDEO) != static_cast<SearchType>(0))
    temp_type += "video,";
  if ((type & SearchType::PLAYLIST) != static_cast<SearchType>(0))
    temp_type += "playlist,";
  if ((type & SearchType::CHANNEL) != static_cast<SearchType>(0))
    temp_type += "channel,";

  return *this;
}
SearchOperation& SearchOperation::ChannelId(std::string_view channelId) {
  parameters_["channelId"] = channelId;

  return *this;
}
SearchOperation& SearchOperation::ForContentOwner(bool forContentOwner) {
  parameters_["forContentOwner"] = forContentOwner ? "true" : "false";

  return *this;
}
SearchOperation& SearchOperation::ForDeveloper(bool forDeveloper) {
  parameters_["forDeveloper"] = forDeveloper ? "true" : "false";

  return *this;
}
SearchOperation& SearchOperation::ForMine(bool forMine) {
  parameters_["forMine"] = forMine ? "true" : "false";

  return *this;
}
SearchOperation& SearchOperation::RelatedToVideoId(
    std::string_view relatedToVideoId) {
  parameters_["relatedToVideoId"] = relatedToVideoId;

  return *this;
}
SearchOperation& SearchOperation::EventType(std::string_view eventType) {
  parameters_["eventType"] = eventType;

  return *this;
}
SearchOperation& SearchOperation::Location(std::string_view location) {
  parameters_["location"] = location;

  return *this;
}
SearchOperation& SearchOperation::LocationRadius(
    std::string_view locationRadius) {
  parameters_["locationRadius"] = locationRadius;

  return *this;
}
SearchOperation& SearchOperation::OnBehalfOfContentOwner(
    std::string_view onBehalfOfContentOwner) {
  parameters_["onBehalfOfContentOwner"] = onBehalfOfContentOwner;

  return *this;
}
SearchOperation& SearchOperation::PageToken(std::string_view pageToken) {
  parameters_["pageToken"] = pageToken;

  return *this;
}
SearchOperation& SearchOperation::RegionCode(std::string_view regionCode) {
  parameters_["regionCode"] = regionCode;

  return *this;
}
SearchOperation& SearchOperation::RelevanceLanguage(
    std::string_view relevanceLanguage) {
  parameters_["relevanceLanguage"] = relevanceLanguage;

  return *this;
}
SearchOperation& SearchOperation::TopicId(std::string_view topicId) {
  parameters_["topicId"] = topicId;

  return *this;
}
SearchOperation& SearchOperation::VideoCategoryId(
    std::string_view videoCategoryId) {
  parameters_["videoCategoryId"] = videoCategoryId;

  return *this;
}
SearchOperation& SearchOperation::PublishedAfter(time_t publishedAfter) {
  char timestr[100];
  strftime(timestr, 100, "%FT%TZ", std::localtime(&publishedAfter));
  parameters_["publishedAfter"] = timestr;

  return *this;
}
SearchOperation& SearchOperation::PublishedAfter(
    std::string_view publishedAfter) {
  if (not check_date(publishedAfter)) {
    throw std::invalid_argument(std::string("In ") + __PRETTY_FUNCTION__ +
                                ": Date must be formatted like "
                                "\"1970-01-01T00:00:00Z\"");
  }
  parameters_["publishedAfter"] = publishedAfter;

  return *this;
}

SearchOperation& SearchOperation::PublishedBefore(time_t publishedBefore) {
  char timestr[100];
  strftime(timestr, 100, "%FT%TZ", std::localtime(&publishedBefore));
  parameters_["publishedBefore"] = timestr;

  return *this;
}
SearchOperation& SearchOperation::PublishedBefore(
    std::string_view publishedBefore) {
  if (not check_date(publishedBefore)) {
    throw std::invalid_argument(std::string("In ") + __PRETTY_FUNCTION__ +
                                ": Date must be formatted like "
                                "\"1970-01-01T00:00:00Z\"");
  }
  parameters_["publishedBefore"] = publishedBefore;

  return *this;
}
SearchOperation& SearchOperation::ChannelType(ChannelTypes channelType) {
  switch (channelType) {
    case ChannelTypes::ANY:
      parameters_["channelType"] = "any";
      break;
    case ChannelTypes::SHOW:
      parameters_["channelType"] = "show";
      break;
  }

  return *this;
}
SearchOperation& SearchOperation::Order(OrderTypes order) {
  switch (order) {
    case OrderTypes::DATE:
      parameters_["order"] = "date";
      break;
    case OrderTypes::RATING:
      parameters_["order"] = "rating";
      break;
    case OrderTypes::RELEVANCE:
      parameters_["order"] = "relevance";
      break;
    case OrderTypes::TITLE:
      parameters_["order"] = "title";
      break;
    case OrderTypes::VIDEO_COUNT:
      parameters_["order"] = "videoCount";
      break;
    case OrderTypes::VIEW_COUNT:
      parameters_["order"] = "viewCount";
      break;
  }

  return *this;
}
SearchOperation& SearchOperation::VideoCaption(
    VideoCaptionTypes videoCaption) {
  switch (videoCaption) {
    case VideoCaptionTypes::ANY:
      parameters_["videoCaption"] = "any";
      break;
    case VideoCaptionTypes::CLOSED_CAPTION:
      parameters_["videoCaption"] = "closedCaption";
      break;
    case VideoCaptionTypes::NONE:
      parameters_["videoCaption"] = "none";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::SafeSearch(SafeSearchTypes safeSearch) {
  switch (safeSearch) {
    case SafeSearchTypes::MODERATE:
      parameters_["safeSearch"] = "moderate";
      break;
    case SafeSearchTypes::NONE:
      parameters_["safeSearch"] = "none";
      break;
    case SafeSearchTypes::STRICT:
      parameters_["safeSearch"] = "strict";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoDefinition(
    VideoDefinitionTypes videoDefinition) {
  switch (videoDefinition) {
    case VideoDefinitionTypes::ANY:
      parameters_["videoDefinition"] = "any";
      break;
    case VideoDefinitionTypes::HIGH:
      parameters_["videoDefinition"] = "high";
      break;
    case VideoDefinitionTypes::STANDARD:
      parameters_["videoDefinition"] = "standard";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoDimension(
    VideoDimensionTypes videoDimension) {
  switch (videoDimension) {
    case VideoDimensionTypes::THREE_D:
      parameters_["videoDimension"] = "3d";
      break;
    case VideoDimensionTypes::TWO_D:
      parameters_["videoDimension"] = "2d";
      break;
    case VideoDimensionTypes::ANY:
      parameters_["videoDimension"] = "any";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoDuration(
    VideoDurationTypes videoDuration) {
  auto& duration = parameters_["videoDuration"];
  duration = "";

  if (videoDuration == VideoDurationTypes::ANY) {
    duration = "any";
    return *this;
  }
  if ((videoDuration & VideoDurationTypes::LONG) !=
      static_cast<VideoDurationTypes>(0))
    duration += "long,";
  if ((videoDuration & VideoDurationTypes::MEDIUM) !=
      static_cast<VideoDurationTypes>(0))
    duration += "medium,";
  if ((videoDuration & VideoDurationTypes::SHORT) !=
      static_cast<VideoDurationTypes>(0))
    duration += "short,";
  return *this;
}
SearchOperation& SearchOperation::VideoEmbeddable(
    VideoEmbeddableTypes videoEmbeddable) {
  switch (videoEmbeddable) {
    case VideoEmbeddableTypes::ANY:
      parameters_["videoEmbeddable"] = "any";
      break;
    case VideoEmbeddableTypes::TRUE:
      parameters_["videoEmbeddable"] = "true";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoLicense(
    VideoLicenseTypes videoLicense) {
  switch (videoLicense) {
    case VideoLicenseTypes::ANY:
      parameters_["videoLicense"] = "any";
      break;
    case VideoLicenseTypes::CREATIVE_COMMON:
      parameters_["videoLicense"] = "creativeCommon";
      break;
    case VideoLicenseTypes::YOUTUBE:
      parameters_["videoLicense"] = "youtube";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoSyndicated(
    VideoSyndicatedTypes videoSyndicated) {
  switch (videoSyndicated) {
    case VideoSyndicatedTypes::ANY:
      parameters_["videoSyndicated"] = "any";
      break;
    case VideoSyndicatedTypes::TRUE:
      parameters_["videoSyndicated"] = "true";
      break;
  }
  return *this;
}
SearchOperation& SearchOperation::VideoType(VideoTypes videoType) {
  switch (videoType) {
    case VideoTypes::ANY:
      parameters_["videoType"] = "any";
      break;
    case VideoTypes::EPISODE:
      parameters_["videoType"] = "episode";
      break;
    case VideoTypes::MOVIE:
      parameters_["videoType"] = "movie";
      break;
  }
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
