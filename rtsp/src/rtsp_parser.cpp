#include "rtsp_parser.h"
#include "rtsp_session.h"
#include "utils.h"

namespace huoguo {
namespace rtsp {

std::shared_ptr<RtspMessage> RtspParser::parse(const char *data, int len) {
    m_buffer.append(std::string((const char *)data, len));
    return parse_message(m_buffer);
}

std::shared_ptr<RtspMessage> RtspParser::parse_message(std::string &buffer) {
    uint32_t readlen = 0;
    std::shared_ptr<RtspMessage> message = nullptr;
    auto rtsp_header_pos = buffer.find(RTSP_END);
    if (rtsp_header_pos == std::string::npos) {
        return message;
    }
    readlen += static_cast<uint32_t>(rtsp_header_pos)+RTSP_END_LEN;
    std::string rtsp_header = buffer.substr(0, readlen);
    if (utils::starts_with(rtsp_header, RTSP_VERSION))
    {
        message = parse_response(rtsp_header);
    } else {
        message = parse_request(rtsp_header);
    }
    auto content_length = std::atoi(message->get_rtsp_header(RTSP_HEADER_FIELDS_CONTENT_LENGTH).c_str());
    if (message && content_length > 0) {
        if (readlen + content_length > m_buffer.length()) {
            ErrorL("readlen=%d, content_len=%d, buffer.length=%d", readlen, content_length, m_buffer.length());
            return nullptr;
        }
        message->set_rtsp_body(m_buffer.substr(readlen, content_length));
        readlen += content_length;
    }
    if (readlen >= m_buffer.length()) {
        m_buffer.clear();
    } else {
        m_buffer = m_buffer.erase(readlen);
    }
    
    return message;
}

std::shared_ptr<RtspRequest> RtspParser::parse_request(std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    // TODO
    // auto request = generate_request();
    return nullptr;
}

std::shared_ptr<RtspResponse> RtspParser::parse_response(std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    auto rtsp_header = utils::split(buffer, RTSP_CRLF);
    if (rtsp_header.empty()) {
        WarnL("error rtsp header, buffer=%s", buffer.c_str());
        return nullptr;
    }
    int res_code;
    std::string res_desc;
    std::string version;
    parse_response_line(rtsp_header[0], res_code, res_desc, version);
    auto response = std::make_shared<RtspResponse>(res_code, res_desc, version);
    parse_rtsp_header(buffer, response);
    return response;
}

int RtspParser::parse_response_line(std::string &buffer, int &res_code, std::string &res_desc, std::string &version) {
    size_t pos = 0;
    version = buffer.substr(0, strlen(RTSP_VERSION));
    pos += version.length();

    pos = buffer.find_first_not_of(RTSP_SP, pos);
    if (pos == std::string::npos || pos + RTSP_STATUS_CODE_LEN > buffer.length()) {
        return 0;
    }
    std::string status_code = buffer.substr(pos, RTSP_STATUS_CODE_LEN).c_str();
    pos += status_code.length();
    res_code = std::atoi(status_code.c_str());

    pos = buffer.find_first_not_of(RTSP_SP, pos);
    if (pos != std::string::npos) {
        res_desc = buffer.substr(pos);
    }
    return 0;
}

int RtspParser::parse_rtsp_header(std::string &buffer, std::shared_ptr<RtspMessage> message) {
    if (buffer.empty()) {
        return -1;
    }
    auto rtsp_header = utils::split(buffer, RTSP_CRLF);
    if (rtsp_header.empty()) {
        WarnL("error rtsp header, buffer=%s", buffer.c_str());
        return -1;
    }
    int pos = 0;
    for (size_t i = 1; i < rtsp_header.size(); ++i) {
        pos = static_cast<int>(rtsp_header[i].find_first_of(RTSP_COLON));
        if (pos == std::string::npos || pos == 0 || pos == rtsp_header[i].length() - 1) {
            continue;
        }
        std::string field = utils::trim(rtsp_header[i].substr(0, pos));
        std::string value = utils::trim(rtsp_header[i].substr(pos + 1));
        message->set_rtsp_header(field, value);
    }
    return 0;
}

}
}