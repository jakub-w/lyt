#include "VideosResponse.h"

namespace yt {
  void VideosResponse::ExtractVideos() {
    assert(Json().HasMember("items"));

    auto &items = Json()["items"];
    assert(items.IsArray());

    if (items.Empty())
      return;

    std::string video_signature = "youtube#video";
    for (auto video = items.Begin(); video < items.End(); ++video) {
      // skip everything that is not a video
      if (video_signature != (*video)["kind"].GetString())
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

      std::vector<std::string> tags;
      for (auto tag = (*video)["snippet"]["tags"].Begin();
	   tag < (*video)["snippet"]["tags"].End();
	   ++tag) {
	tags.push_back(tag->GetString());
      }

      Video vid;
      vid.SetId((*video)["id"].GetString());
      vid.SetPublishedAt((*video)["snippet"]["publishedAt"].GetString());
      vid.SetChannelId((*video)["snippet"]["channelId"].GetString());
      vid.SetTitle((*video)["snippet"]["title"].GetString());
      vid.SetDescription(
          (*video)["snippet"]["description"].GetString());
      vid.SetThumbnails(std::move(thumbnails));
      vid.SetChannelTitle((*video)["snippet"]["channelTitle"].GetString());
      vid.SetTags(std::move(tags));
      vid.SetCategoryId((*video)["snippet"]["categoryId"].GetString());
      // liveBroadcastContent
      // localized

      videos_.push_back(std::move(vid));
    }
  }
}
