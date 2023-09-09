#ifndef HUOGUO_RTSP_RTSP_METHOD_H_
#define HUOGUO_RTSP_RTSP_METHOD_H_

namespace huoguo {
namespace rtsp {


enum RTSP_METHOD {
    OPTIONS,
    DESCRIBE,
    ANNOUNCE,
    SETUP,
    SET_PARAMETER,
    GET_PARAMETER,
    PLAY,
    PAUSE,
    RECORD,
    REDIRECT,
    TEARDOWN,
};

static const char *rtsp_method[] {
    "OPTIONS",
    "DESCRIBE",
    "ANNOUNCE",
    "SETUP",
    "SET_PARAMETER",
    "GET_PARAMETER",
    "PLAY",
    "PAUSE",
    "RECORD",
    "REDIRECT",
    "TEARDOWN",
};

#define RTSP_COLON   ":"
#define RTSP_SP      " "
#define RTSP_CRLF    "\r\n"
#define RTSP_END     "\r\n\r\n"
#define RTSP_VERSION "RTSP/1.0"

#define RTSP_GERERAL_HEADER_FIELDS_CSEQ "CSeq"

#define RTSP_REQUEST_HEADER_FIELDS_USER_AGENT "User-Agent"

#define RTSP_REQUEST_HEADER_FIELDS(FIELDS, VALUES) \
    (std::string("") + (FIELDS) + (RTSP_COLON) + (RTSP_SP) + (VALUES) + (RTSP_CRLF))

}
}

#endif // HUOGUO_RTSP_RTSP_METHOD_H_