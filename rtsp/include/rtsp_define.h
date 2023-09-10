#ifndef HUOGUO_RTSP_RTSP_METHOD_H_
#define HUOGUO_RTSP_RTSP_METHOD_H_

namespace huoguo {
namespace rtsp {

typedef enum RTSP_METHOD {
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
} RTSP_METHOD;

static std::map<RTSP_METHOD, std::string> rtsp_method_map {
    {OPTIONS, "OPTIONS"},
    {DESCRIBE, "DESCRIBE"},
    {ANNOUNCE, "ANNOUNCE"},
    {SETUP, "SETUP"},
    {SET_PARAMETER, "SET_PARAMETER"},
    {GET_PARAMETER, "GET_PARAMETER"},
    {PLAY, "PLAY"},
    {PAUSE, "PAUSE"},
    {RECORD, "RECORD"},
    {REDIRECT, "REDIRECT"},
    {TEARDOWN, "TEARDOWN"},
};

static std::map<int, std::string> rtsp_status_map = {
    {200, "OK"},
};

#define RTSP_COLON   ":"
#define RTSP_SPACE   " "
#define RTSP_SP      RTSP_SPACE
#define RTSP_CRLF    "\r\n"
#define RTSP_END     "\r\n\r\n"
#define RTSP_VERSION "RTSP/1.0"
#define RTSP_STATUS_CODE_LEN 3

#define RTSP_HEADER_FIELDS_CSEQ "CSeq"
#define RTSP_HEADER_FIELDS_USER_AGENT "User-Agent"
#define RTSP_HEADER_FIELDS_WWW_AUTHENTICATE "WWW-Authenticate"

#define RTSP_HEADER_FIELDS(FIELDS, VALUES) \
    ((std::string("")) + (FIELDS) + (RTSP_COLON) + (RTSP_SP) + (VALUES) + (RTSP_CRLF))

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_METHOD_H_