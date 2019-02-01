#include <iostream>
#include <algorithm>

#include "SearchOperation.h"
// #include "CURLcontext.h"
#include "Video.h"
#include "SearchResponse.h"
#include <iomanip>

void print_video_info(const yt::Video& video) {
  auto old_locale = std::cout.getloc();
  std::cout.imbue(std::locale(""));
  std::cout << "\e[1;32m" << video.Title() << "\e[22;0m\n"
	    << "\e[1mChannel: \e[22m" << video.ChannelTitle() << '\n'
	    << "\e[1mDate: \e[22m"
	    << std::put_time(std::localtime(video.PublishedAt()), "%c")
	    << '\n'
	    << "\e[1mDescription: \e[22m\n" << video.DescriptionShortened()
	    << "\nhttps://www.youtube.com/embed/" << video.Id() << "\n\n";
  std::cout.imbue(old_locale);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " QUERY\n";
    return 1;
  }

  std::unique_ptr<yt::SearchResponse> sr =
    yt::Search(argv[1]).MaxResults(5).Perform();

  // std::cout << sr->Uri() << '\n';

  for (auto &video : sr->Videos()) {
    print_video_info(video);
  }

  return 0;
}
