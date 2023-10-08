#include "utils_string.h"
#include <memory>
#include <gtest/gtest.h>

namespace huoguo {
namespace utils {

TEST(utils, starts_with) {
    EXPECT_TRUE(starts_with("hello", "h"));
}

}
}