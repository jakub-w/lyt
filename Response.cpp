#include "Response.h"

#include <utility>

namespace yt {
void Response::ExtractVideos() {
    assert(json_doc_.HasMember("items"));

    // rapidjson::GenericArray
    auto& items = json_doc_["items"];
    assert(items.IsArray());

    if (items.Empty()) return;

    std::string video_signature = "youtube#video";
    for (auto video = items.Begin(); video < items.End(); ++video) {
      // skip everything that is not a video
      if (video_signature != (*video)["id"]["kind"].GetString())
        continue;

      std::unordered_map<std::string, const Video::Thumbnail> thumbnails;
      for (auto thumbnail = (*video)["snippet"]["thumbnails"].MemberBegin();
           thumbnail < (*video)["snippet"]["thumbnails"].MemberEnd();
           ++thumbnail) {
        thumbnails.insert({thumbnail->name.GetString(),
                           {thumbnail->value["url"].GetString(),
                            thumbnail->value["width"].GetUint(),
                            thumbnail->value["height"].GetUint()}});
      }

      videos_.emplace_back(
          (std::string_view)(*video)["id"]["videoId"].GetString(),
          (*video)["snippet"]["publishedAt"].GetString(),
          (*video)["snippet"]["channelId"].GetString(),
          (*video)["snippet"]["title"].GetString(),
          (*video)["snippet"]["description"].GetString(),
          std::move(thumbnails),
          (*video)["snippet"]["channelTitle"].GetString());
    }
  }
}
