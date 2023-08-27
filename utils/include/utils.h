#ifndef HUOGUO_UTILS_H_
#define HUOGUO_UTILS_H_

namespace huoguo {
namespace utils {

#define OK   0
#define ERR -1

bool is_power_of_2(unsigned int n);
unsigned int roundup_pow_of_2(unsigned int n);

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_H_