#include "utils_bits.h"

namespace huoguo {
namespace utils {

bool is_power_of_2(unsigned int n) {
    return (n && !(n & (n - 1)));
}

unsigned int roundup_pow_of_2(unsigned int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

}
}