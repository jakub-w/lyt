#include <iostream>
#include <algorithm>

#include "SearchOperation.h"
#include "CURLcontext.h"
#include "Video.h"


int main(/*int argc, char** argv*/) {
  yt::Response response =
      yt::Search("northernlion isaac").MaxResults(2).Perform();
  // std::cout << response.Text() << '\n';

  for (auto it = response.Json().MemberBegin();
       it < response.Json().MemberEnd(); ++it) {
    std::cout << it->name.GetString() << ": "
              << (it->value.IsString() ? it->value.GetString() : "[]")
              << '\n';
  }
  std::cout << "\n\n";

  auto items = response.Json().FindMember("items");
  if (response.Json().MemberEnd() == items) return 1;

  for (auto items_it = items->value.Begin();
       items_it < items->value.End();
       ++items_it) {
    for (auto it = items_it->MemberBegin();
         it != items_it->MemberEnd();
         ++it) {
      std::cout << it->name.GetString() << ": "
                << (it->value.IsString() ? it->value.GetString() : "[]")
                << '\n';
    }
    std::cout << '\n';
  }
  // std::cout << response.Json() << '\n';

  return 0;
}
