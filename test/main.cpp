#include <stdio.h>
#include <chrono>
#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <iomanip>

std::string date_time(std::time_t posix)
{
    char buf[20]; // big enough for 2015-07-08 10:06:51\0
    std::tm tp = *std::localtime(&posix);
    return {buf, std::strftime(buf, sizeof(buf), "%F %T", &tp)};
}

std::string stamp()
{
    using namespace std;
    using namespace std::chrono;

    auto now = system_clock::now();

    // use microseconds % 1000000 now
    auto us = duration_cast<microseconds>(now.time_since_epoch()) % 1000000;

    std::ostringstream oss;
    oss.fill('0');

    oss << date_time(system_clock::to_time_t(now));
    oss << '.' << setw(6) << us.count();

    return oss.str();
}


int main(void)
{
    std::cout << stamp() << std::endl;
    // int i, j, n;

    // for (i = 0; i < 11; i++) {
    //     for (j = 0; j < 10; j++) {
    //         n = 10 * i + j;
    //         if (n > 108) break;
    //         printf("%d", n);
    //         printf("\033[%dm%3d\033[m", n, n);
    //     }
    //     printf("\n");
    // }
    // return 0;
}