#ifndef YT_RESPONSE_H
#define YT_RESPONSE_H

#include <string>
#include <optional>

#include "rapidjson/document.h"

namespace yt {
class Response {
  std::string uri_;
  std::string text_;
  rapidjson::Document json_doc_;
  std::optional<bool> has_errors_;

public:
  inline Response(std::string_view uri, std::string_view text)
      : uri_(uri), text_(text) {
    json_doc_.Parse(text_.data());
    assert(json_doc_.IsObject());
  }

  virtual ~Response() {}

  inline const std::string& Uri() const { return uri_; }
  inline const std::string& Text() const { return text_; }
  inline const rapidjson::Document& Json() const { return json_doc_; }

  inline bool HasErrors() {
    if (false == has_errors_.has_value())
      has_errors_ = json_doc_.HasMember("error");

    return *has_errors_;
  }
};
} // namespace yt

#endif // YT_RESPONSE_H
