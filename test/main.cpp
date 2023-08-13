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

template< typename... Args >
std::string format(const char* format, Args... args) {
    int length = std::snprintf(nullptr, 0, format, args...);
    if (length <= 0) {
        return "";
    }

    char* buf = new char[length + 1];
    std::snprintf(buf, length + 1, format, args...);

    std::string str(buf);
    delete[] buf;
    return std::move(str);
}


// string s = "拉拉黑%saaaa你好";
// string x = format(s.c_str(), "123");

#include <iostream>
#include <string>
#include <stdarg.h>

int format_num(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int num = vsnprintf(0, 0, format, args);
    va_end(args);
    return num;
}

int format_num(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    int num = vswprintf(0, 0, format, args);
    va_end(args);
    return num;
}

int std_string_format(std::string & str, const char * format, ...) {
    std::string tmp;

    va_list marker;
    va_start(marker, format);

    size_t num = format_num(format, marker);
    std::cout << num << std::endl;
    if (num >= tmp.capacity())
        tmp.reserve(num + 1);

    vsnprintf((char *)tmp.data(), tmp.capacity(), format, marker);

    va_end(marker);

    str = tmp.c_str();
    return str.size();
}

int std_wstring_format(std::wstring & str, const wchar_t * format, ...) {
    std::wstring tmp;

    va_list marker;
    va_start(marker, format);

    size_t num = format_num(format, marker);

    if (num >= tmp.capacity())
        tmp.reserve(num + 1);

    vswprintf((wchar_t *)tmp.data(), tmp.capacity(), format, marker);

    va_end(marker);

    str = tmp.c_str();
    return str.size();
}

int main()
{
    std::string hello = "hello";
    std::string std_str;
    int len = std_string_format(std_str, "hello %s!", hello);
    std::cout << "std_str=" << std_str << ", len=" << len << std::endl;

    // std::wcout.imbue(std::locale("chs"));

    // std::wstring std_str_ch;
    // len = std_wstring_format(std_str_ch, L"你好 %s!", L"世界");
    // std::wcout << L"std_str_ch=" << std_str_ch << L", len=" << len << std::endl;
}
#if 0
int main(void)
{
    std::string hello = "hello";
    std::string s = "可以么%s,,,%d";
    std::cout << format(s.c_str(), hello, 123) << std::endl;

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
#endif