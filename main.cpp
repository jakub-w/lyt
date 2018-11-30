#include <iostream>
#include <algorithm>

#include "SearchOperation.h"
#include "CURLcontext.h"
#include "Video.h"


int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " QUERY\n";
    return 1;
  }

  yt::Response response =
      yt::Search(argv[1]).MaxResults(10).Perform();
  std::cout << response.Uri() << '\n';

  for (auto &video : response.Videos()) {
    std::cout << video.Title() << '\n';
  }

  return 0;
}
