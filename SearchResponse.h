#ifndef YT_SEARCHRESPONSE_H
#define YT_SEARCHRESPONSE_H

#include "Response.h"

#include "Video.h"

namespace yt {
class SearchResponse : public Response {
  std::vector<Video> videos_;

  // Extract videos from json_doc_ into videos_
  void ExtractVideos();

 public:
  inline SearchResponse(std::string_view uri, std::string_view text)
       : Response(uri, text) {}

  inline SearchResponse(const SearchResponse& response)
      : Response(response.Uri(), response.Text()){
    videos_ = response.videos_;
  }

  // inline SearchResponse(const Response& basic_response)
    // : Response(basic_response.Uri(), basic_response.Text()){}
  // inline SearchResponse(const Response&& basic_response) {

  // }
  inline const std::vector<Video> &Videos() {
    // if videos are not populated and there were no errors,
    // they weren't extracted
    if (videos_.empty() && false == HasErrors())
      ExtractVideos();

    return videos_;
  }
};
}

#endif // YT_SEARCHRESPONSE_H
