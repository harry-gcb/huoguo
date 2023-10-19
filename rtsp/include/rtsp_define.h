#ifndef HUOGUO_RTSP_RTSP_METHOD_H_
#define HUOGUO_RTSP_RTSP_METHOD_H_

namespace huoguo {
namespace rtsp {


#define OPTIONS "OPTIONS"
#define DESCRIBE "DESCRIBE"
#define ANNOUNCE "ANNOUNCE"
#define SETUP "SETUP"
#define SET_PARAMETER "SET_PARAMETER"
#define GET_PARAMETER "GET_PARAMETER"
#define PLAY "PLAY"
#define PAUSE "PAUSE"
#define RECORD "RECORD"
#define REDIRECT "REDIRECT"
#define TEARDOWN "TEARDOWN"

typedef enum RTSP_STATUS {
    OK = 200,
    UNAUTHORIZED = 401,
} RTSP_STATUS;

static std::map<int, std::string> rtsp_status_map = {
    {OK, "OK"},
    {UNAUTHORIZED, "Unauthorized"}
};

#define RTSP_COLON   ":"
#define RTSP_SPACE   " "
#define RTSP_SP      RTSP_SPACE
#define RTSP_CRLF    "\r\n"
#define RTSP_END     "\r\n\r\n"
#define RTSP_VERSION "RTSP/1.0"
#define RTSP_STATUS_CODE_LEN 3
#define RTSP_END_LEN 4
#define RTSP_SDP_TYPE "application/sdp"

#define RTSP_AUTH_SIZE    256
#define RTSP_AUTH_REALM   "realm"
#define RTSP_AUTH_NONCE   "nonce"
#define RTSP_AUTH_BASIC   "Basic"
#define RTSP_AUTH_DIGEST  "Digest"
#define RTSP_AUTH_STALE   "stale"

#define RTSP_HEADER_FIELDS_CSEQ "CSeq"
#define RTSP_HEADER_FIELDS_USER_AGENT "User-Agent"
#define RTSP_HEADER_FIELDS_WWW_AUTHENTICATE "WWW-Authenticate"
#define RTSP_HEADER_FIELDS_AUTHORIZATION "Authorization"
#define RTSP_HEADER_FIELDS_CONTENT_LENGTH "Content-Length"
#define RTSP_HEADER_FIELDS_CONTENT_TYPE   "Content-Type"
#define RTSP_HEADER_FIELDS_TRANSPORT      "Transport"
#define RTSP_HEADER_FIELDS_SESSION      "Session"
#define RTSP_HEADER_FIELDS_RANGE "Range"

#define RTSP_HEADER_FIELDS(FIELDS, VALUES) \
    ((std::string("")) + (FIELDS) + (RTSP_COLON) + (RTSP_SP) + (VALUES) + (RTSP_CRLF))

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_METHOD_H_