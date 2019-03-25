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

void print_usage(char* program_name) {
  std::cout << "Usage: " << program_name << " <command> [<args>]\n\n"
            << "Commands:\n"
            << "\tsearch\n";
}

void print_search_usage(char* program_name) {
  std::cout << "Usage:\n"
            << program_name << " search [OPTION...] <query>\n\n"
            << "Options:\n"
            << "  -c, --channel-id=ID\n"
            << "  -h, --help\n"
            << "  -n, --max-results=NUMBER\n"
            << "  -t, --type=TYPE\t\tchannel, video (default), playlist\n"
            << "  --relevance-language=LANG\n"
            << "  --published-after=DATE\tDate should be RFC 3339 formatted\n"
            << "  --published-before=DATE\tDate should be RFC 3339 formatted\n"
            << "  -o, --order=ORDER\t\tdate, rating, relevance (default),"
      " title,\n\t\t\t\tvideoCount, viewCount\n"
            << "  --safe-search=TYPE\t\tmoderate, none (default), strict\n"
            << "  --video-definition=TYPE\tany (default), high, standard\n"
      "\t\t\t\t--type must be set for it to work\n"
            << "  --video-duration=DURATION\tany (default), long, medium, "
      "short\n\t\t\t\t--type must be set for it to work\n";
}

// returns empty string if not found
std::string get_option_value(std::string_view option) {
  const std::regex re("--[^=]*=(.*)");
  std::cmatch results;
  if (not std::regex_search(option.begin(), option.end(), results, re)) {
    return "";
  }

  return results[1];
}

int search_command(int argc, char** argv) {
  bool help = false;
  for (int i = 2; i < argc; ++i) {
    if (0 == strcmp(argv[i], "--help") or
        0 == strcmp(argv[i], "-h")) {
      help = true;
      break;
    }
  }
  if (argc < 3 or help) {
    print_search_usage(argv[0]);
    return 0;
  }
  if (0 == strncmp(argv[argc - 1], "-", 1)) {
    std::cerr << "Error: Bad value for <query>.\n";
    return 1;
  }

  // last argument is a query
  auto sr = yt::Search(argv[argc-1]);
  for (int i = 2; i < argc - 1; ++i) {
    std::string_view current_arg = argv[i];
    // channel-id
    if (0 == current_arg.find("--channel-id")) {
      sr.ChannelId(get_option_value(current_arg));
    } else if (0 == strcmp(argv[i], "-c")) {
      sr.ChannelId(argv[i + 1]);
      // max-results
    } else if (0 == current_arg.find("--max-results")) {
      try {
      sr.MaxResults(std::stoi(get_option_value(current_arg)));
      } catch (std::invalid_argument& e) {
        std::cerr << "Error: Bad value for --max-results.\n";
      }
    } else if (0 == strcmp(argv[i], "-n")) {
      try {
        sr.MaxResults(std::stoi(argv[i + 1]));
      } catch (std::invalid_argument& e) {
        std::cerr << "Error: Bad value for --max-results.\n";
      }
      // type
    } else if (0 == current_arg.find("--type")) {
      std::string type = get_option_value(current_arg);
      if (type == "channel")
        sr.Type(yt::SearchOperation::SearchType::CHANNEL);
      else if (type == "playlist")
        sr.Type(yt::SearchOperation::SearchType::PLAYLIST);
      else if (type == "video")
        sr.Type(yt::SearchOperation::SearchType::VIDEO);
      else std::cerr << "Error: Bad value for --type\n";
    } else if (0 == strcmp(argv[i], "-t")) {
      std::string type = argv[i + 1];
      if (type == "channel")
        sr.Type(yt::SearchOperation::SearchType::CHANNEL);
      else if (type == "playlist")
        sr.Type(yt::SearchOperation::SearchType::PLAYLIST);
      else if (type == "video")
        sr.Type(yt::SearchOperation::SearchType::VIDEO);
      else std::cerr << "Error: Bad value for --type\n";
      // relevance-language
    } else if (0 == current_arg.find("--relevance-language")) {
      sr.RelevanceLanguage(get_option_value(current_arg));
      // published-after
    } else if (0 == current_arg.find("--published-after")) {
      try {
        sr.PublishedAfter(get_option_value(current_arg));
      } catch (std::invalid_argument& e) {
        std::cerr << "Error: Bad value for --published-after.\n"
            "       Date must be formatted like \"1970-01-01T00:00:00Z\"\n";
      }
      // published-before
    } else if (0 == current_arg.find("--published-before")) {
      try {
        sr.PublishedBefore(get_option_value(current_arg));
      } catch (std::invalid_argument& e) {
        std::cerr << "Error: Bad value for --published-before.\n"
            "       Date must be formatted like \"1970-01-01T00:00:00Z\"\n";
      }
      // order
    } else if (0 == current_arg.find("--order")) {
      std::string order = get_option_value(current_arg);
      yt::SearchOperation::OrderTypes order_type;
      if (order == "date") {
        order_type = yt::SearchOperation::OrderTypes::DATE;
      } else if (order == "rating") {
        order_type = yt::SearchOperation::OrderTypes::RATING;
      } else if (order == "title") {
        order_type = yt::SearchOperation::OrderTypes::TITLE;
      } else if (order == "videoCount") {
        order_type = yt::SearchOperation::OrderTypes::VIDEO_COUNT;
      } else if (order == "viewCount") {
        order_type = yt::SearchOperation::OrderTypes::VIEW_COUNT;
      } else if (order == "relevance") {
        order_type = yt::SearchOperation::OrderTypes::RELEVANCE;
      } else {
        std::cerr << "Error: Bad value for --order.\n";
        continue;
      }
      sr.Order(order_type);
    } else if (0 == strcmp(argv[i], "-o")) {
      std::string order = argv[i + 1];
      yt::SearchOperation::OrderTypes order_type;
      if (order == "date") {
        order_type = yt::SearchOperation::OrderTypes::DATE;
      } else if (order == "rating") {
        order_type = yt::SearchOperation::OrderTypes::RATING;
      } else if (order == "title") {
        order_type = yt::SearchOperation::OrderTypes::TITLE;
      } else if (order == "videoCount") {
        order_type = yt::SearchOperation::OrderTypes::VIDEO_COUNT;
      } else if (order == "viewCount") {
        order_type = yt::SearchOperation::OrderTypes::VIEW_COUNT;
      } else if (order == "relevance") {
        order_type = yt::SearchOperation::OrderTypes::RELEVANCE;
      } else {
        std::cerr << "Error: Bad value for --order.\n";
        continue;
      }
      sr.Order(order_type);
      // safe-search
    } else if (0 == current_arg.find("--safe-search")) {
      std::string safe_search = get_option_value(current_arg);
      if (safe_search == "moderate") {
        sr.SafeSearch(yt::SearchOperation::SafeSearchTypes::MODERATE);
      } else if (safe_search == "strict") {
        sr.SafeSearch(yt::SearchOperation::SafeSearchTypes::STRICT);
      } else if (safe_search == "none") {
        sr.SafeSearch(yt::SearchOperation::SafeSearchTypes::NONE);
      }
      // video-definition
    } else if (0 == current_arg.find("--video-definition")) {
      std::string video_def = get_option_value(current_arg);
      if (video_def == "any") {
        sr.VideoDefinition(yt::SearchOperation::VideoDefinitionTypes::ANY);
      } else if (video_def == "high") {
        sr.VideoDefinition(yt::SearchOperation::VideoDefinitionTypes::HIGH);
      } else if (video_def == "standard") {
        sr.VideoDefinition(
            yt::SearchOperation::VideoDefinitionTypes::STANDARD);
      } else {
        std::cerr << "Error: Bad value for --video-defitinion.\n";
      }
      // video-duration
    } else if (0 == current_arg.find("--video-duration")) {
      std::string video_dur = get_option_value(current_arg);
      if (video_dur == "any") {
        sr.VideoDuration(yt::SearchOperation::VideoDurationTypes::ANY);
      } else if (video_dur == "long") {
        sr.VideoDuration(yt::SearchOperation::VideoDurationTypes::LONG);
      } else if (video_dur == "medium") {
        sr.VideoDuration(yt::SearchOperation::VideoDurationTypes::MEDIUM);
      } else if (video_dur == "short") {
        sr.VideoDuration(yt::SearchOperation::VideoDurationTypes::SHORT);
      } else {
        std::cerr << "Error: Bad Value for --video-duration.\n";
      }
    }
  }

  auto response = sr.Perform();
  // std::cout << response->Uri() << '\n';

  for (auto& video : response->Videos()) {
    print_video_info(video);
  }

  return 0;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  if (0 == strcmp(argv[1], "search")) {
    return search_command(argc, argv);
  }
  else {
    print_usage(argv[0]);
    return 1;
  }

  // std::tm tm = {};
  // tm.tm_year = 119; // 2019
  // tm.tm_mon = 1;    // february
  // tm.tm_mday = 1;
  // std::time_t time = std::mktime(&tm);
  // std::unique_ptr<yt::SearchResponse> sr =
  //     yt::Search(argv[1]).MaxResults(5)
  //     .Type(yt::SearchOperation::SearchType::VIDEO)
  //     .Perform();

  // std::cout << sr->Uri() << '\n';
  // for (auto &video : sr->Videos()) {
  //   print_video_info(video);
  // }

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
