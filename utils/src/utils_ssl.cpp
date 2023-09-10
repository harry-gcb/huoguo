#include "utils_ssl.h"
#include <openssl/md5.h>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace huoguo {
namespace utils {

std::string md5(const std::string &s) {
    unsigned char hash[MD5_DIGEST_LENGTH] = { 0 };
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, s.c_str(), s.size());
    MD5_Final(hash, &md5);

    std::stringstream ss;

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
    }
    return ss.str();
}

}
}