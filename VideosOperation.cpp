#include "VideosOperation.h"

#include <CURLcontext.h>

namespace yt {
  std::unique_ptr<VideosResponse> VideosOperation::Perform() {
    return CURLcontext::Get<VideosResponse>({yt::API_SCHEME,
					     yt::API_AUTHORITY,
					     yt::API_PATH,
					     GetActionName(),
					     parameters_});
  }
}
