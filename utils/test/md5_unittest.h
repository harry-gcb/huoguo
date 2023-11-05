#ifndef HUOGUO_UTILS_MD5_UNITTEST_H_
#define HUOGUO_UTILS_MD5_UNITTEST_H_

#include <memory>
#include <gtest/gtest.h>
#include <iostream>
#include "utils_md5.h"
#include "utils_ssl.h"

namespace huoguo {
namespace utils {

TEST(utils, md5) {

    std::string s = "hello";
    std::string md5_1 = ssl_md5(s);
    std::string md5_2 = md5(s);
    EXPECT_EQ(md5_1, md5_2);
    std::cout << md5_1 << std::endl;
    std::cout << md5_2 << std::endl;
    // auto kfifo = std::make_shared<Kfifo>(15);
    // EXPECT_EQ(16, kfifo->size());
    // EXPECT_EQ(0, kfifo->length());
    // EXPECT_EQ(16, kfifo->avail());
    // EXPECT_TRUE(kfifo->is_empty());
    // EXPECT_FALSE(kfifo->is_full());
    // std::string a(10, 'a');
    // EXPECT_EQ(10, kfifo->put((const uint8_t *)a.c_str(), a.length()));
    // EXPECT_EQ(10, kfifo->length());
    // EXPECT_EQ(6, kfifo->avail());
    // EXPECT_FALSE(kfifo->is_empty());
    // EXPECT_FALSE(kfifo->is_full());
}

}
}

#endif // HUOGUO_UTILS_MD5_UNITTEST_H_