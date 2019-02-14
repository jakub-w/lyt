#include <iostream>
#include <algorithm>

#include "SearchOperation.h"
#include "Video.h"
#include "VideosOperation.h"
#include "VideosResponse.h"
#include "SearchResponse.h"
#include <iomanip>

void print_video_info(const yt::Video& video, bool additional_info = false) {
  auto old_locale = std::cout.getloc();
  std::cout.imbue(std::locale(""));
  std::cout << "\e[1;32m" << video.Title() << "\e[22;0m\n"
	    << "\e[1mChannel: \e[22m" << video.ChannelTitle() << '\n'
	    << "\e[1mDate: \e[22m"
	    << std::put_time(std::localtime(video.PublishedAt()), "%c")
	    << '\n';
  if (additional_info) {
    std::string_view description = video.Description();
    if ("" == description) {
      description = video.DescriptionShortened();
    }
    std::cout << "\e[1mDescription: \e[22m\n" << description << '\n';
  } else {
    std::cout << "\e[1mDescription: \e[22m\n"
	    << video.DescriptionShortened() << '\n';
  }
  if (additional_info) {
    if (not video.Tags().empty()) {
      std::cout << "\e[1mTags: \e[22m\n";
      for (auto& tag : video.Tags()) {
	std::cout << "  " << tag << '\n';
      }
    }
    if ("" != video.CategoryId()) {
      std::cout << "\e[1mCategory: \e[22m" << video.CategoryId() << '\n';
    }
  }
  std::cout << "https://www.youtube.com/embed/" << video.Id() << "\n\n";
  std::cout.imbue(old_locale);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " QUERY\n";
    return 1;
  }

  // std::tm tm = {};
  // tm.tm_year = 119; // 2019
  // tm.tm_mon = 1;    // february
  // tm.tm_mday = 1;
  // std::time_t time = std::mktime(&tm);
  std::unique_ptr<yt::SearchResponse> sr =
      yt::Search(argv[1]).MaxResults(5)
      .Type(yt::SearchOperation::SearchType::VIDEO)
      .Perform();

  std::cout << sr->Uri() << '\n';
  for (auto &video : sr->Videos()) {
    print_video_info(video);
  }

  // std::vector<std::string> video_ids;
  // for (auto &video : sr->Videos()) {
  //     video_ids.push_back(video.Id());
  // }
  // auto vr = yt::Videos(video_ids).Perform();

  // std::cout << vr->Uri() << '\n';
  // for (auto &video : vr->Videos()) {
  //   print_video_info(video);
  // }

  return 0;
}
