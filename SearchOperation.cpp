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
    parameters_["type"] = "";
    if ((type & SearchType::VIDEO) != 0)
      parameters_["type"] += "video,";
    if ((type & SearchType::PLAYLIST) != 0)
      parameters_["type"] += "playlist,";
    if ((type & SearchType::CHANNEL) != 0)
      parameters_["type"] += "channel,";

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
  std::unique_ptr<SearchResponse> SearchOperation::Perform() {

    return CURLcontext::Get<SearchResponse>({yt::API_SCHEME,
					     yt::API_AUTHORITY,
					     yt::API_PATH,
					     GetActionName(),
					     parameters_});
  }
}
