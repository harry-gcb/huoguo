#ifndef HUOGUO_UTILS_OPTION_H_
#define HUOGUO_UTILS_OPTION_H_

#include <string>
#include <map>
#include <typeinfo>
#include <memory>

namespace huoguo {
namespace utils {

#define OPTION huoguo::utils::Option::option

class Option {
public:
    struct OptionCmd {
        std::string cmd_short;
        std::string cmd_long;
        std::string cmd_help;
        std::string cmd_value;
        bool cmd_with_value;
        bool cmd_exists;
        OptionCmd(): cmd_with_value(false), cmd_exists(false) {}
    };
    struct OptionGroup {
        std::string group_name;
        std::string group_help;
        std::map<std::string, std::shared_ptr<OptionCmd> > group_option;
        OptionGroup() = default;
        OptionGroup(const std::string &name, const std::string &help): group_name(name), group_help(help) {}
        OptionGroup &add(const std::string &s, const std::string &l, const std::string &h, bool with_value = false) {
            if (s.empty() && l.empty()) {
                return *this;
            }
            if (group_option.count(s) || group_option.count(l)) {
                return *this;
            }
            auto cmd = std::make_shared<OptionCmd>();
            cmd->cmd_short = s;
            cmd->cmd_long = l;
            cmd->cmd_help = h;
            cmd->cmd_with_value = with_value;
            if (!s.empty()) {
                group_option.insert({s, cmd});
            }
            if (!l.empty()) {
                group_option.insert({l, cmd});
            }
            return *this;
        }

        template <typename T>
        T to_T(const std::string &value) {
            if (typeid(std::string) == typeid(T)) {
                return value;
            }
        }

        template <typename T>
        T get(const std::string &cmd) {
            auto it = group_option.find(cmd);
            if (it != group_option.end()) {
                return to_T<T>(it->second->cmd_value);
            }
            return T{};
        }

        bool is_exists(const std::string &cmd) {
            auto it = group_option.find(cmd);
            if (it == group_option.end()) {
                return false;
            }
            return it->second->cmd_exists;
        }
    };

public:
    Option() = default;
    OptionGroup &add(const std::string &s, const std::string &l, const std::string &h, bool with_value = false);
    OptionGroup &group(const std::string &n, const std::string &h = "");
    template <typename T>
    T get(const std::string &cmd);
    bool is_exists(const std::string &cmd);
    int init(int argc, char *argv[]);
    void usage(const std::string &g = "");
public:
    static Option option;
private:
    std::string m_procname;
    std::map<std::string, OptionGroup> m_option;
};

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_OPTION_H_