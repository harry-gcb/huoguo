#include <gtest/gtest.h>
#include "utils_string.h"

namespace huoguo {
namespace utils {

TEST(utils, starts_with) {
    EXPECT_TRUE(starts_with("hello", "h"));
}

}
}