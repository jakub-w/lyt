#ifndef YT_VIDEO_H
#define YT_VIDEO_H

#include <ctime>
#include <unordered_map>
#include <vector>

namespace yt {
  class Video {
  public:
    struct Thumbnail {
      std::string url;
      unsigned int width;
      unsigned int height;
    };

  private:
    // Can be obtained with SearchOperation
    std::string id_;
    std::time_t published_at_;
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
    Video() {}

    // ACCESSORS
    inline const std::string& Id() const { return id_; }
    inline void SetId(const std::string& id) { id_ = id; }

    inline const std::time_t* PublishedAt() const {
      return &published_at_;
    }
    inline void SetPublishedAt(const std::time_t& published_at) {
      published_at_ = published_at;
    }
    // utc_time_string - string with time in the format of:
    //                   YYYY-MM-DDThh:mm:ss.sZ
    //                   compliant to ISO 8601 standard
    inline void SetPublishedAt(const std::string& utc_time_string) {
      std::tm time = {};
      strptime(utc_time_string.c_str(), "%FT%X", &time);
      // substract timezone because time is in UTC, but std::mktime()
      // interprets it as local time
      published_at_ = std::mktime(&time) - ::timezone;
    }

    inline const std::string& ChannelId() const { return channel_id_; }
    inline void SetChannelId(const std::string& channel_id) {
      channel_id_ = channel_id;
    }

    inline const std::string& Title() const { return title_; }
    inline void SetTitle(const std::string& title) { title_ = title; }

    inline const std::string& DescriptionShortened() const {
      return description_shortened_;
    }
    inline void SetDescriptionShortened(
         const std::string& description_shortened) {
      description_shortened_ = description_shortened; }

    inline const std::unordered_map<std::string, const Thumbnail>&
    Thumbnails() const {
      return thumbnails_;
    }
    inline void SetThumbnails(
        const std::unordered_map<std::string, const Thumbnail>& thumbnails) {
      thumbnails_.clear();
      thumbnails_.reserve(thumbnails.size());
      thumbnails_.insert(thumbnails.begin(), thumbnails.end());
    }
    inline void SetThumbnails(
        const std::unordered_map<std::string, const Thumbnail>&& thumbnails) {
      thumbnails_ = std::move(thumbnails);
    }

    inline const std::string& ChannelTitle() const {
      return channel_title_;
    }
    inline void SetChannelTitle(const std::string& channel_title) {
      channel_title_ = channel_title;
    }

    inline const std::string& Description() const {
      throw std::logic_error(std::string(__FUNCTION__) +
			     ": Not yet implemented.");
      return description_;
    }
    inline void SetDescription(const std::string& description) {
      description_ = description;
    }

    inline const std::vector<std::string>& Tags() const {
      throw std::logic_error(std::string(__FUNCTION__) +
			     ": Not yet implemented.");
      return tags_;
    }
    inline void SetTags(std::vector<std::string>& tags) {
      tags_.assign(tags.begin(), tags.end());
    }
    inline void SetTags(std::vector<std::string>&& tags) {
      tags_ = std::move(tags);
    }

    inline const std::string& CategoryId() const {
      throw std::logic_error(std::string(__FUNCTION__) +
			     ": Not yet implemented.");
      return category_id_;
    }
    inline void SetCategoryId(const std::string& category_id) {
      category_id_ = category_id;
    }
  };
}

#endif // YT_VIDEO_H
