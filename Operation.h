#ifndef YT_OPERATION_H
#define YT_OPERATION_H

#include <regex>
#include <unordered_map>

namespace yt {
  const std::string API_SCHEME = "https";
  const std::string API_AUTHORITY = "www.googleapis.com";
  const std::string API_PATH = "/youtube/v3/";

/**
 * \brief Operation is an abstract base for operation classes
 *
 * It's only purpose is to add a YouTube api key to parameters_ and ensure
 * that its children define `GetActionName()`.
 *
 * ### Inheriting Operation
 *
 * Classes that inherit Operation define queries to the YouTube API and
 * implement calls for specific resources from it.
 *
 * Every Operation's child should define `Perform()` function
 * that returns `std::unique_ptr` to the concrete Response object that
 * corresponds to it.
 * (E.g. for SearchOperation: `std::unique_ptr<SearchResponse> Perform()`).
 *
 * To be continued...
 */
class Operation {
 protected:
  std::unordered_map<std::string, std::string> parameters_;

 public:
  Operation();
  virtual ~Operation() {}

  virtual std::string GetActionName() const = 0;
};
}

#endif // YT_OPERATION_H
