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

    Video vid;
    vid.SetId((*video)["id"]["videoId"].GetString());
    vid.SetPublishedAt((*video)["snippet"]["publishedAt"].GetString());
    vid.SetChannelId((*video)["snippet"]["channelId"].GetString());
    vid.SetTitle((*video)["snippet"]["title"].GetString());
    vid.SetDescriptionShortened(
        (*video)["snippet"]["description"].GetString());
    vid.SetThumbnails(std::move(thumbnails));
    vid.SetChannelTitle((*video)["snippet"]["channelTitle"].GetString());

    videos_.push_back(std::move(vid));
  }
}
} // namespace yt
