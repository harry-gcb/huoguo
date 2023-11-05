#ifndef HUOGUO_UTILS_BITS_UNITTEST_H_
#define HUOGUO_UTILS_BITS_UNITTEST_H_

#include <gtest/gtest.h>
#include "utils_bits.h"

namespace huoguo {
namespace utils {

TEST(utils, is_power_of_2) {
    EXPECT_FALSE(is_power_of_2(0));
    EXPECT_TRUE(is_power_of_2(1));
    EXPECT_TRUE(is_power_of_2(2));
    EXPECT_FALSE(is_power_of_2(3));
    EXPECT_TRUE(is_power_of_2(4));
    EXPECT_FALSE(is_power_of_2(1023));
    EXPECT_TRUE(is_power_of_2(1024));
    EXPECT_FALSE(is_power_of_2(1025));
}

TEST(utils, roundup_pow_of_2) {
    EXPECT_EQ(0, roundup_pow_of_2(0));
    EXPECT_EQ(1, roundup_pow_of_2(1));
    EXPECT_EQ(2, roundup_pow_of_2(2));
    EXPECT_EQ(4, roundup_pow_of_2(3));
    EXPECT_EQ(4, roundup_pow_of_2(4));
    EXPECT_EQ(8, roundup_pow_of_2(5));
    EXPECT_EQ(1024, roundup_pow_of_2(1023));
    EXPECT_EQ(1024, roundup_pow_of_2(1024));
    EXPECT_EQ(2048, roundup_pow_of_2(1025));
}

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_BITS_UNITTEST_H_

