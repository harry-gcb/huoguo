#ifndef HUOGUO_UTILS_STRUTILS_H_
#define HUOGUO_UTILS_STRUTILS_H_

#include <string>
#include <vector>

namespace huoguo {
namespace utils {

// #ifdef __cplusplus
// extern "C" {
// #endif

static const std::string WHITESPACE = " \n\r\t\f\v";
std::string ltrim(const std::string &str, const std::string &delimiter=WHITESPACE);
std::string rtrim(const std::string &str, const std::string &delimiter=WHITESPACE);
std::string trim(const std::string &str, const std::string &delimiter=WHITESPACE);
std::vector<std::string> split(const std::string &str, const std::string &delimiter);
bool starts_with(const std::string &str, const std::string &delimiter);
bool ends_with(const std::string &str, const std::string &delimiter);
std::string to_lower(std::string &str);
std::string to_upper(std::string &str);

// #ifdef __cplusplus
// }
// #endif

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_STRUTILS_H_