#ifndef YT_VIDEOSRESPONSE_H
#define YT_VIDEOSRESPONSE_H

#include "Response.h"
#include "Video.h"

namespace yt {
  class VideosResponse : public Response {
    std::vector<Video> videos_;

    // Extract videos from json_doc_ into videos_
    void ExtractVideos();
  public:
    inline VideosResponse(std::string_view uri, std::string_view text)
      : Response(uri, text) {}

    inline const std::vector<Video>& Videos() {
      // if videos are not populated and there were no errors,
      // they weren't extracted
      if (videos_.empty() && false == HasErrors())
	ExtractVideos();

      return videos_;
    }
  };
}

#endif // YT_VIDEOSRESPONSE_H
