#include "SearchResponse.h"

using namespace std::literals::string_literals;

namespace yt {
void SearchResponse::ExtractVideos() {
  assert(Json().HasMember("items"));

  // rapidjson::GenericArray
  auto &items = Json()["items"];
  assert(items.IsArray());

  if (items.Empty())
    return;

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
        (*video)["snippet"]["description"].GetString(), std::move(thumbnails),
        (*video)["snippet"]["channelTitle"].GetString());
  }
}
} // namespace yt
