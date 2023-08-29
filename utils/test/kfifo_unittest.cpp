#include "kfifo.h"
#include <memory>
#include <gtest/gtest.h>

namespace huoguo {
namespace utils {

TEST(utils, kfifo) {
    auto kfifo = std::make_shared<Kfifo>(15);
    EXPECT_EQ(16, kfifo->size());
    EXPECT_EQ(0, kfifo->length());
    EXPECT_EQ(16, kfifo->avail());
    EXPECT_TRUE(kfifo->is_empty());
    EXPECT_FALSE(kfifo->is_full());
    std::string a(10, 'a');
    EXPECT_EQ(10, kfifo->put((const uint8_t *)a.c_str(), a.length()));
    EXPECT_EQ(10, kfifo->length());
    EXPECT_EQ(6, kfifo->avail());
    EXPECT_FALSE(kfifo->is_empty());
    EXPECT_FALSE(kfifo->is_full());
}

}
}