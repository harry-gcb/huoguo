#include "rtp_parser.h"
#include "utils_byte.h"
#include "utils_logger.h"

namespace huoguo {
namespace rtp {

//  0                   1                   2                   3
//  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |V=2|P|X|  CC   |M|     PT      |       sequence number         |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                           timestamp                           |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |           synchronization source (SSRC) identifier            |
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// |            Contributing source (CSRC) identifiers             |
// |                             ....                              |
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// |  header eXtension profile id  |       length in 32bits        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                          Extensions                           |
// |                             ....                              |
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// |                           Payload                             |
// |             ....              :  padding...                   |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |               padding         | Padding size  |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 
// V：RTP协议的版本号，占2位，当前协议版本号为2
// P：填充标志，占1位，如果P=1，则在该报文的尾部填充一个或多个额外的八位组，它们不是有效载荷的一部分
// X：扩展标志，占1位，如果X=1，则在RTP报头后跟有一个扩展报头
// CC：CSRC计数器，占4位，指示CSRC 标识符的个数
// M: 标记，占1位，不同的有效载荷有不同的含义，对于视频，标记一帧的结束；对于音频，标记会话的开始
// PT: 有效载荷类型，占7位，用于说明RTP报文中有效载荷的类型，如GSM音频、JPEM图像等,在流媒体中大部分是用来区分音频流和视频流的，这样便于客户端进行解析
// sequence number: 序列号, 占16位，用于标识发送者所发送的RTP报文的序列号，每发送一个报文，序列号增1。
//                  这个字段当下层的承载协议用UDP的时候，网络状况不好的时候可以用来检查丢包。同时出现网络抖动的情况可以用来对数据进行重新排序
// timestamp: 时戳(Timestamp)：占32位，时戳反映了该RTP报文的第一个八位组的采样时刻。接收者使用时戳来计算延迟和延迟抖动，并进行同步控制
// ssrc: 同步信源(SSRC)标识符：占32位，用于标识同步信源。该标识符是随机选择的，参加同一视频会议的两个同步信源不能有相同的SSRC
// csrc: 特约信源(CSRC)标识符：每个CSRC标识符占32位，可以有0～15个。每个CSRC标识了包含在该RTP报文有效载荷中的所有特约信源


/* RTP header extension, RFC 3550.
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|      defined by profile       |           length              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                        header extension                       |
|                             ....                              |

扩展字段定义define by profile:16bit两字节，这个由上层的具体实现协议来决定；
扩展头长度length:表示扩展头的长度字段，16bit即2字节，最大扩展长度1024字节；
拓展部分的头部包含一个16-bit的数据来描述拓展块包含多少个32-bit字（不包括拓展部分的头部）。
因为RTP头部后面只能连接一个拓展块，考虑到有些应用可能会有多种类型的拓展块，所以拓展块的头16-bit留给开发者去自定义一些参数

*/


std::shared_ptr<RtpPacket> RtpParser::parse(const uint8_t *data, size_t size) {
    auto rtp_packet = std::make_shared<RtpPacket>();
    if (size < RTP_FIXED_HEADER_SIZE) {
        ErrorL("data size is invalid, size=%d, need=%d", size, RTP_FIXED_HEADER_SIZE);
        return nullptr;
    }

    // 第1个字节
    const uint8_t version = (data[0] >> 6);
    if (version != RTP_VERSION) {
        ErrorL("rtp version is invalid, version=%u, need=%u", version, RTP_VERSION);
        return nullptr;
    }
    size_t payload_offset = 0;

    rtp_packet->set_padding(data[0] & 0x20 >> 5);
    rtp_packet->set_extension(data[0] & 0x10 >> 4);
    rtp_packet->set_number_of_csrc(data[0] & 0x0f);

    // 第2个字节
    rtp_packet->set_marker(data[1] & 0x80 >> 7);
    rtp_packet->set_payload_type(data[1] & 0x7f);
    // 第3-4个字节
    rtp_packet->set_sequence_number(utils::Byte<uint16_t>::read_be((const uint8_t *)&data[2]));
    // 第5-8字节
    rtp_packet->set_timestamp(utils::Byte<uint32_t>::read_be((const uint8_t *)&data[4]));
    // 第8-12字节
    rtp_packet->set_ssrc(utils::Byte<uint32_t>::read_be((const uint8_t *)&data[8]));

    // TODO: check csrc
    if (size < RTP_FIXED_HEADER_SIZE + rtp_packet->get_number_of_csrc() * 4) {
        return nullptr;
    }
    // check extension
    payload_offset = RTP_FIXED_HEADER_SIZE + rtp_packet->get_number_of_csrc() * 4;
    if (rtp_packet->get_extension())
    {
        size_t extension_offset = rtp_packet->get_payload_offset() + 4;
        if (size < extension_offset) {
            return nullptr;
        }
        rtp_packet->set_extension_offset(extension_offset);
        uint16_t profile = utils::Byte<uint16_t>::read_be((const uint8_t *)&data[rtp_packet->get_payload_offset()]);
        uint16_t length = utils::Byte<uint16_t>::read_be((const uint8_t *)&data[rtp_packet->get_payload_offset() + 2]);
        uint32_t extension_capacity = length * 4;
        if (size < extension_offset + extension_capacity) {
            return nullptr;
        }
        rtp_packet->set_extension_capacity(extension_capacity);
        if ((profile != RTP_ONE_BYTE_EXT_PROFILE_ID) && 
           ((profile & RTP_TWO_BYTE_EXT_PROFILE_ID_APP_BITS_FILTER) != RTP_TWO_BYTE_EXT_PROFILE_ID)) {
            WarnL("Unsupported rtp extension: %d", profile);
        } else {
            uint32_t extension_header_length = RTP_ONE_BYTE_EXT_PROFILE_ID == profile ? RTP_ONE_BYTE_EXT_HEADER_LEN : RTP_TWO_BYTE_EXT_HEADER_LEN;
            constexpr uint8_t padding_id = 0;
            constexpr uint8_t padding_byte = 0;
            constexpr uint8_t one_byte_header_ext_reserved_id = 15;
            size_t extension_size = 0;
            while (extension_size + extension_header_length < extension_capacity) {
                if (data[extension_offset + extension_size] == padding_byte) {
                    extension_size++;
                    continue;
                }
                int id = 0;
                uint8_t length = 0;
                if (RTP_ONE_BYTE_EXT_PROFILE_ID == profile) {
                    id     =  data[extension_offset + extension_size] >> 4;
                    length = (data[extension_offset + extension_size] & 0xF) + 1;
                    if (one_byte_header_ext_reserved_id == id || (padding_id == id && length != 1)) {
                        break;
                    }
                } else {
                    id     = data[extension_offset + extension_size];
                    length = data[extension_offset + extension_size + 1];
                }
                if (extension_size + extension_header_length + length > extension_capacity) {
                    WarnL("Oversized rtp header extension");
                    break;
                }
                RtpPacket::Extension &extension = rtp_packet->find_or_create_extension(id);
                if (extension.get_length() != 0) {
                    InfoL("Duplicate rtp header extension id %d. Overwriting.", id);
                }
                size_t offset = extension_offset + extension_size + extension_header_length;
                extension.set_offset(offset);
                extension.set_length(length);
                extension_size += extension_header_length + length;
            }
        }
        payload_offset += extension_offset + extension_capacity;
    }

    if (rtp_packet->get_padding() && payload_offset < size) {
        uint8_t padding_size = data[size - 1];
        if (padding_size == 0) {
            WarnL("Padding was set, but padding size is zero");
            return nullptr;
        }
        rtp_packet->set_padding_size(padding_size);
    }

    if (payload_offset + rtp_packet->get_padding_size() > size) {
        return nullptr;
    }
    rtp_packet->set_payload_offset(payload_offset);
    rtp_packet->set_payload_size(size - payload_offset - rtp_packet->get_padding_size());
    return rtp_packet;
}

}
}