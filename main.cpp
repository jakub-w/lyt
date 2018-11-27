#include <iostream>

#include "SearchOperation.h"
#include "CURLcontext.h"

using namespace std::literals::string_literals;

int main(/*int argc, char** argv*/) {
  std::string query = yt::Search("foo"s).MaxResults(2).Perform().uri;
  std::cout << query << '\n';

  yt::Response response = yt::CURLcontext::QuerySend(query);
  std::cout << response.text << '\n';

  return 0;
}
