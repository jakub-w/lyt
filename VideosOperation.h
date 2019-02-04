#ifndef YT_VIDEOSOPERATION_H
#define YT_VIDEOSOPERATION_H

#include "Operation.h"

#include <vector>

#include "VideosResponse.h"

namespace yt {
  class VideosOperation : public Operation {
  public:
    inline VideosOperation(const std::vector<std::string>& video_ids) {
      parameters_["part"] = "snippet";

      auto& id = parameters_["id"];
      for (auto& video_id : video_ids) {
	id += video_id + ',';
      }
    }

    inline std::string GetActionName() const final { return "videos"; }

    std::unique_ptr<VideosResponse> Perform();
  };

  inline VideosOperation Videos(const std::vector<std::string>& video_ids) {
    return VideosOperation(video_ids);
  }
}

#endif // YT_VIDEOSOPERATION_H
