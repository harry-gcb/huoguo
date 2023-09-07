#ifndef HUOGOU_RTSP_RTSP_CALLBACK_H_
#define HUOGOU_RTSP_RTSP_CALLBACK_H_

#include <memory>
#include <functional>

#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

using RtspOptionRequest = std::function<void (std::shared_ptr<RtspOptions>)>;


} // namespace rtsp
} // namespace huoguo

#endif // HUOGOU_RTSP_RTSP_CALLBACK_H_