#ifndef HUOGUO_UTILS_OPTION_H_
#define HUOGUO_UTILS_OPTION_H_

#include <string>
#include <map>
#include <typeinfo>

namespace huoguo {
namespace utils {

#define OPTION huoguo::utils::Option::option

class Option {
    struct OptionCmd {
        std::string cmd_short;
        std::string cmd_long;
        std::string cmd_help;
        std::string cmd_value;
        bool cmd_exists;
        OptionCmd(): cmd_exists(false) {}
    };
public:
    Option() = default;
    template <typename T>
    Option &add(const std::string &s, const std::string &l, const std::string &h, const T &v = T());
    template <typename T>
    T get(const std::string &cmd);
    bool is_exists(const std::string &cmd);
    void parse(int argc, char *argv[]);
public:
    static Option option;
private:
    std::map<std::string, OptionCmd> m_option;
};

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_OPTION_H_