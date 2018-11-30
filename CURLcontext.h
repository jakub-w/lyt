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
  // PRIVATE VARIABLES
  static bool is_initialized_;
  static std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl_;
  static char curl_error_buffer[CURL_ERROR_SIZE];
  static std::stringstream curl_output_stream;

  // PRIVATE FUNCTIONS
  static size_t curl_write_callback(char* buffer, size_t,
                                    size_t nmemb, void*);

public:
  CURLcontext() = delete;

  static void Initialize();
  static Response Get(const Query& query);
};
}

#endif // YT_CURLCONTEXT_H
