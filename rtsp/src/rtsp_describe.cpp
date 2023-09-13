#include "rtsp_describe.h"

namespace huoguo {
namespace rtsp {

RtspDescribeRequest::RtspDescribeRequest()
    : RtspRequest(RTSP_MESSAGE_TYPE_DESCRIBE_REQ, DESCRIBE){

}

std::string RtspDescribeRequest::to_string() {
    std::string request_header;
    std::string request_line = get_request_line();
    std::string user_agent = get_field(RTSP_HEADER_FIELDS_USER_AGENT);
    std::string authorization = get_field(RTSP_HEADER_FIELDS_AUTHORIZATION);
    request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_CSEQ, std::to_string(get_cseq()));
    if (!user_agent.empty()) {
        request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_USER_AGENT, user_agent);
    }
    if (!authorization.empty()) {
        request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_AUTHORIZATION, authorization);
    }
    request_header += RTSP_CRLF;
    return request_line + request_header;
}

}
}