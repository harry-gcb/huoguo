#ifndef HUOGOU_RTSP_RTSP_CALLBACK_H_
#define HUOGOU_RTSP_RTSP_CALLBACK_H_

#include <memory>
#include <functional>

#include "rtsp_options.h"
#include "rtsp_describe.h"
#include "rtsp_setup.h"
#include "rtsp_play.h"
#include "rtsp_teardown.h"

namespace huoguo {
namespace rtsp {

class RtspSession;

using OptionsRequest = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspOptionsRequest>)>;
using DescribeRequest = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspDescribeRequest>)>;
using SetupRequest = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspSetupRequest>)>;
using PlayRequest = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspPlayRequest>)>;
using TeardownRequest = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspTeardownRequest>)>;

using OptionsResponse = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspOptionsResponse>)>;
using DescribeResponse = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspDescribeResponse>)>;
using SetupResponse = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspSetupResponse>)>;
using PlayResponse = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspPlayResponse>)>;
using TeardownResponse = std::function<void (std::shared_ptr<RtspSession>, std::shared_ptr<RtspTeardownResponse>)>;

} // namespace rtsp
} // namespace huoguo

#endif // HUOGOU_RTSP_RTSP_CALLBACK_H_