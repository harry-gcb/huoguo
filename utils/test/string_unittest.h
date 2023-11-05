#ifndef HUOGUO_UTILS_STRING_UNITTEST_H_
#define HUOGUO_UTILS_STRING_UNITTEST_H_

#include <gtest/gtest.h>
#include "utils_string.h"

namespace huoguo {
namespace utils {

TEST(utils, starts_with) {
    EXPECT_TRUE(starts_with("hello", "h"));
}

}
}

#endif // HUOGUO_UTILS_STRING_UNITTEST_H_