#ifndef YT_CURLCONTEXT_H
#define YT_CURLCONTEXT_H

#include <iostream>
#include <memory>
#include <sstream>

#include <curl/curl.h>
#include <curl/easy.h>

#include "Query.h"
#include "Response.h"

namespace yt {
class CURLcontext {
  struct CURLresponse {
    std::string uri;
    std::string content;
  };

  // PRIVATE VARIABLES
  static bool is_initialized_;
  static std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl_;
  static char curl_error_buffer[CURL_ERROR_SIZE];
  static std::stringstream curl_output_stream;

  // PRIVATE FUNCTIONS
  static size_t curl_write_callback(char* buffer, size_t,
                                    size_t nmemb, void*);

  static CURLresponse Get_(const Query& query);

public:
  CURLcontext() = delete;

  static void Initialize();
  template<typename T>
  static std::unique_ptr<T> Get(const Query& query) {
    static_assert(std::is_base_of<Response, T>::value,
		  "In CURLcontext::Get<T>(): T must be derived "
		  "from Response.");

    CURLresponse response = Get_(query);
    return std::make_unique<T>(std::move(response.uri),
			       std::move(response.content));
  }
};
}

#endif // YT_CURLCONTEXT_H
