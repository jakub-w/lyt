#ifndef YT_RESPONSE_H
#define YT_RESPONSE_H

#include <string>
#include <vector>

#include "rapidjson/document.h"

#include "Video.h"

namespace yt {
class Response {
  std::string uri_;
  std::string text_;
  rapidjson::Document json_doc_;
  std::optional<bool> has_errors_;
  std::vector<Video> videos_;

  // Extract videos from json_doc_ into videos_
  void ExtractVideos();

public:
  inline Response(std::string_view uri, std::string_view text)
      : uri_(uri), text_(text) {
    json_doc_.Parse(text_.data());
  }

  inline const std::string& Uri() const { return uri_; }
  inline const std::string& Text() const { return text_; }
  inline const rapidjson::Document& Json() const { return json_doc_; }

  inline bool HasErrors() {
    if (false == has_errors_.has_value())
      has_errors_ = json_doc_.HasMember("error");

    return *has_errors_;
  }

  const std::vector<Video>& Videos() {
    // if videos are not populated and there were no errors,
    // they weren't extracted
    if (videos_.empty() && false == HasErrors())
      ExtractVideos();

    return videos_;
  }
};
} // namespace yt

#endif // YT_RESPONSE_H
