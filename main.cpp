#include <iostream>
#include <algorithm>

#include "SearchOperation.h"
// #include "CURLcontext.h"
#include "Video.h"
#include "SearchResponse.h"


int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " QUERY\n";
    return 1;
  }

  std::unique_ptr<yt::SearchResponse> sr = yt::Search(argv[1]).Perform();

  for (auto &video : sr->Videos()) {
    std::cout << video.Title() << '\n';
  }

  return 0;
}
