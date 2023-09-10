#include "option.h"
#include "utils_string.h"
#include "logger.h"
#include <set>
#include <iostream>

namespace huoguo {
namespace utils {

Option Option::option;

Option::OptionGroup &Option::group(const std::string &n, const std::string &h) {
    auto it = m_option.find(n);
    if (it == m_option.end()) {
        m_option.insert({n, OptionGroup(n, h)});
    }
    return m_option[n];
}

Option::OptionGroup &Option::add(const std::string &s, const std::string &l, const std::string &h, bool with_value) {
    return group("").add(s, l, h, with_value);
}

#if 0
template <typename T>
T Option::get(const std::string &cmd) {
    return group("").get<T>(cmd);
}
#endif
std::string Option::get(const std::string &cmd) {
    return group("").get(cmd);
}

bool Option::is_exists(const std::string &cmd) {
    return group("").is_exists(cmd);
}

int Option::init(int argc, char *argv[]) {
    if (!argv) {
        return -1;
    }
    std::string g("");
    m_procname = argv[0];
    int i = 1;
    while (i < argc) {
        if (!argv[i]) {
            break;
        } else if (1 == i && !starts_with(argv[i], "-") && m_option.count(argv[i])) {
            g = argv[i];
        } else if (starts_with(argv[i], "--")) {
            auto arg = std::string(argv[i] + 2);
            if (arg.empty()) {
                i++;
                continue;
            }
            auto it = m_option[g].group_option.find(arg);
            if (it == m_option[g].group_option.end()) {
                ERROR("argv[%d]=%s not identified");
                return -1;
            }
            if (it->second->cmd_with_value && i + 1 < argc) {
                if (i + 1 < argc) {
                    it->second->cmd_value = argv[++i];
                } else {
                    ERROR("argv[%d]=%s has no args", i, argv[i]);
                    return -1;
                }
            }
            it->second->cmd_exists = true;
        } else if (starts_with(argv[i], "-")) {
            auto arg = std::string(argv[i] + 1);
            if (arg.empty()) {
                i++;
                continue;
            }
            if (arg.length() > 1) {
                for (auto &c: arg) {
                    auto it = m_option[g].group_option.find(std::string(c, 1));
                    if (it == m_option[g].group_option.end()) {
                        ERROR("argv[%d]=%s not identified", i, argv[i]);
                        return -1;
                    }
                    if (it->second->cmd_with_value) {
                        ERROR("argv[%d]=%s can't with args");
                        return -1;
                    }
                    it->second->cmd_exists = true;
                }
            } else {
                auto it = m_option[g].group_option.find(arg);
                if (it == m_option[g].group_option.end()) {
                    ERROR("argv[%d]=%s not identified");
                    return -1;
                }
            if (it->second->cmd_with_value && i + 1 < argc) {
                if (i + 1 < argc) {
                    it->second->cmd_value = argv[++i];
                } else {
                    ERROR("argv[%d]=%s has no args", i, argv[i]);
                    return -1;
                }
            }
                it->second->cmd_exists = true;
            }          
        }
        i++;
    }
    return 0;
}

void Option::usage(const std::string &g) {
    std::set<std::string> over_show;
    for (auto &cmd: m_option[g].group_option) {
        if (!cmd.second) {
            continue;
        }
        if (over_show.find(cmd.first) != over_show.end()) {
            continue;
        }
        if (!cmd.second->cmd_short.empty()) {
            std::cout << "-" << cmd.second->cmd_short;
        } else {
            std::cout << "   ";
        }
        if (!cmd.second->cmd_long.empty()) {
            if (!cmd.second->cmd_short.empty()) {
                std::cout << ", ";
            } else {
                std::cout << " ";
            }
            std::cout << "--" << cmd.second->cmd_long;
        } else if (!cmd.second->cmd_short.empty()) {
            std::cout << "   ";
        }
        std::cout << " " << cmd.second->cmd_help << std::endl;
        over_show.insert(cmd.second->cmd_short);
        over_show.insert(cmd.second->cmd_long);
    }
    std::cout << std::endl;
}

}
}