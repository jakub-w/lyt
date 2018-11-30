#include "CURLcontext.h"

namespace yt {
bool CURLcontext::is_initialized_ = false;

std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>
CURLcontext::curl_(nullptr, nullptr);

char CURLcontext::curl_error_buffer[CURL_ERROR_SIZE];
std::stringstream CURLcontext::curl_output_stream;

size_t CURLcontext::curl_write_callback(char *buffer, size_t, size_t nmemb,
                                        void *) {
  try {
    curl_output_stream.write(buffer, nmemb);
  } catch (const std::exception &e) {
    // TODO: pass an error down the line instead of cerr it
    std::cerr << "write_callback() error: " << e.what() << '\n';
    return 0;
  }

  return nmemb;
}

void CURLcontext::Initialize() {
  if (is_initialized_) // it's a singleton
    throw std::logic_error("CURLcontext already exists.");

  if (CURLcode result = curl_global_init(CURL_GLOBAL_NOTHING);
      CURLE_OK != result) {
    curl_global_cleanup();
    throw std::runtime_error(curl_easy_strerror(result));
  }

  curl_ = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>(
      curl_easy_init(), &curl_easy_cleanup);

  if (nullptr == curl_) {
    throw std::runtime_error("Couldn't initialize curl-easy.");
  }

  // TODO: check return values of those functions.
  curl_easy_setopt(curl_.get(), CURLOPT_USE_SSL, CURLUSESSL_ALL);
  curl_easy_setopt(curl_.get(), CURLOPT_WRITEFUNCTION, &curl_write_callback);
  curl_easy_setopt(curl_.get(), CURLOPT_ERRORBUFFER, curl_error_buffer);

  is_initialized_ = true;
}

Response CURLcontext::QuerySend(std::string_view query) {
  if (false == is_initialized_)
    Initialize();

  curl_easy_setopt(curl_.get(), CURLOPT_URL, query.data());

  if (CURLE_OK != curl_easy_perform(curl_.get())) {
    throw std::runtime_error(std::string("In function '") +
                             __PRETTY_FUNCTION__ + "': " + curl_error_buffer);
  }

  Response response{query, curl_output_stream.str()};

  curl_output_stream.str(""); // reset stream

  return response;
}
} // namespace yt
