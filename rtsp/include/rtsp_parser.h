#ifndef HUOGUO_RTSP_RTSP_PARSER_H_
#define HUOGUO_RTSP_RTSP_PARSER_H_

#include <memory>
#include "rtsp_message.h"
#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

class RtspSession;
class RtspParser {
    friend class RtspSession;
public:
    std::shared_ptr<RtspMessage> parse(const uint8_t *data, size_t size);
private:
    std::shared_ptr<RtspMessage> parse_message(std::string &buffer);
    std::shared_ptr<RtspRequest> parse_request(std::string &buffer);
    std::shared_ptr<RtspResponse> parse_response(std::string &buffer);

    int parse_response_line(std::string &buffer, int &res_code, std::string &res_desc, std::string &version);
    int parse_rtsp_header(std::string &buffer, std::shared_ptr<RtspMessage> message);
    // std::string generate_auth(const std::string &www_authenticate, const std::string &method, const std::string &uri);
private:
    std::string m_buffer;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_PARSER_H_