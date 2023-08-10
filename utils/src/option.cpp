#include "option.h"
#include "strutils.h"
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

template <typename T>
T Option::get(const std::string &cmd) {
    return group("").get<T>(cmd);
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
        } else if (1 == i && !starts_with(argv[i], "-") && m_option.count(argv[i])) {
            g = argv[i];
        } else if (starts_with(argv[i], "--")) {
            auto arg = std::string(argv[i] + 2);
            if (arg.empty()) {
                i++;
                continue;
            }
            auto korkv = split(arg, "=");
            auto it = m_option[g].group_option.find(korkv[0]);
            if (it == m_option[g].group_option.end()) {
                std::cout << "argv[" << i << "] " << argv[i] << " not identified" << std::endl; 
                return -1;
            }
            if (it->second->cmd_with_value) {
                if (korkv.size() < 2) {
                    std::cout << "argv[" << i << "] " << argv[i] << " has no args" << std::endl;
                    return -1;
                }
                it->second->cmd_value = korkv[1];
            }
            it->second->cmd_exists = true;
        } else if (starts_with(argv[i], "-")) {
            auto arg = std::string(argv[i] + 1);
            if (arg.empty()) {
                i++;
                continue;
            }
            auto korkv = split(arg, "=");
            if (korkv[0].size() > 1) {
                for (auto &c: korkv[0]) {
                    auto it = m_option[g].group_option.find(std::string(c, 1));
                    if (it == m_option[g].group_option.end()) {
                        std::cout << "argv[" << i << "] " << argv[i] << " not identified" << std::endl;
                        return -1;
                    }
                    if (it->second->cmd_with_value) {
                        std::cout << "argv[" << i << "] " << argv[i] << "can't with args" << std::endl;
                        return -1;
                    }
                    if (!it->second->cmd_with_value && korkv.size() > 1) {
                        std::cout << "argv[" << i << "] " << argv[i] << "has no args" << std::endl;
                        return -1;
                    }
                    it->second->cmd_exists = true;
                }
            } else {
                auto it = m_option[g].group_option.find(korkv[0]);
                if (it == m_option[g].group_option.end()) {
                    std::cout << "argv[" << i << "] " << argv[i] << " not found" << std::endl;
                    return -1;
                }
                if (it->second->cmd_with_value) {
                    if (korkv.size() < 2) {
                        std::cout << "argv[" << i << "] " << argv[i] << " has no args" << std::endl;
                        return -1;        
                    }
                    it->second->cmd_value = korkv[1];
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
        std::cout << "-" << cmd.second->cmd_short << ", --" << cmd.second->cmd_long;
        over_show.insert(cmd.second->cmd_short);
        over_show.insert(cmd.second->cmd_long);
    }
    std::cout << std::endl;
}

}
}