#ifndef YT_VIDEO_H
#define YT_VIDEO_H

#include <unordered_map>
#include <vector>

namespace yt {
class Video {
 public:
  // TODO: move to a separate file (if we'll need it for anything else)
  struct Thumbnail {
    std::string url;
    unsigned int width;
    unsigned int height;
  };

  // Can be obtained with SearchOperation
  std::string id_;
  std::string published_at_; // std::tm ?
  std::string channel_id_;
  std::string title_;
  std::string description_shortened_; // short version ending with "..."
  std::unordered_map<std::string, const Thumbnail> thumbnails_;
  std::string channel_title_;
  // std::string live_broadcast_content;

  // Only from VideosOperation
  // Those should probably have accessors returning std::optional or
  // std::future
  std::string description_; // full video description
  std::vector<std::string> tags_;
  std::string category_id_;

 public:
  // CONSTRUCTORS
   Video(std::string id,
         std::string published_at,
         std::string channel_id,
         std::string title,
         std::string description_shortened,
         std::unordered_map<std::string, const Thumbnail> thumbnails,
         std::string channel_title) :
       id_(id), published_at_(published_at), channel_id_(channel_id),
       title_(title), description_shortened_(description_shortened),
       thumbnails_(thumbnails), channel_title_(channel_title) {}

  Video(std::string_view id,
        std::string_view published_at,
        std::string_view channel_id,
        std::string_view title,
        std::string_view description_shortened,
        std::unordered_map<std::string, const Thumbnail>&& thumbnails,
        std::string_view channel_title) :
      id_(id), published_at_(published_at), channel_id_(channel_id),
      title_(title), description_shortened_(description_shortened),
      thumbnails_(std::move(thumbnails)), channel_title_(channel_title) {}

   // ACCESSORS
   inline const std::string &Id() const { return id_; }

   inline const std::string &PublishedAt() const { return published_at_; }

   inline const std::string &ChannelId() const { return channel_id_; }

   inline const std::string &Title() const { return title_; }

   inline const std::string &DescriptionShortened() const {
     return description_shortened_;
  }

  inline const std::unordered_map<std::string, const Thumbnail>&
  Thumbnails() const {
    return thumbnails_;
  }

  inline const std::string& ChannelTitle() const {
    return channel_title_;
  }

  inline const std::string& Description() const {
    throw std::logic_error("Not yet implemented.");
    return description_;
  }

  inline const std::vector<std::string>& Tags() const {
    throw std::logic_error("Not yet implemented.");
    return tags_;
  }

  inline const std::string& CategoryId() const {
    throw std::logic_error("Not yet implemented.");
    return category_id_;
  }
};
}

#endif // YT_VIDEO_H
