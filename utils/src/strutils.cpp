#include <algorithm>
#include <cctype>
#include "strutils.h"

namespace huoguo {
namespace utils {

static const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &str) {
    if (str.empty()) return str;
    auto start = str.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string rtrim(const std::string &str) {
    if (str.empty()) return str;
    size_t end = str.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string trim(const std::string &str) {
    return rtrim(ltrim(str));
}

std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(str.substr(pos_start));
    return res;
}

bool starts_with(const std::string &str, const std::string &delimiter) {
    if (str.empty() && delimiter.empty()) { return true; }
    else if (str.empty()) { return false; }
    else { return 0 == str.find(delimiter); }
}

bool ends_with(const std::string &str, const std::string &delimiter) {
    if (str.empty() && delimiter.empty()) { return true; }
    else if (str.empty()) { return false; }
    else { return str.length() - delimiter.length() == str.find(delimiter); }
}

std::string to_lower(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string to_upper(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

} // namespace uitls
} // namespace huoguo