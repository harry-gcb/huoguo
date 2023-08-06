#include <fstream>
#include <iostream>
#include <sstream>
#include "config.h"
#include "strutils.h"

namespace huoguo {
namespace utils {

Config Config::config;

void Config::init(const std::string &cfg) {
    std::ifstream infile(cfg, std::ios::in);
    std::string line;
    std::string section;
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        auto sz = line.find_first_of("#");
        std::string content = std::string::npos == sz ? line : line.substr(0, sz);
        content = huoguo::utils::trim(content);
        if (huoguo::utils::starts_with(content, "[") && huoguo::utils::ends_with(content, "]")) {
            section = huoguo::utils::trim(content.substr(1, content.length() - 2));
            continue;
        }
        if (section.empty()) {
            continue;
        }
        sz = content.find_first_of("=");
        if (std::string::npos == sz) {
            continue;
        }
        std::string name = huoguo::utils::trim(content.substr(0, sz));
        std::string value = huoguo::utils::trim(content.substr(sz + 1, content.length() - sz));
        m_config[section][name] = value;
    }
}

template <typename T>
T Config::get(const std::string &section, const std::string &name, const T &value) {
    auto s = m_config.find(section);
    if (s == m_config.end()) {
        return value;
    }
    auto n = s->second.find(name);
    if (n == s->second.end())
    {
        return value;
    }
    T out;
    std::stringstream ss(n->second);
    ss >> out;
    return out;
}

int Config::get(const std::string &section, const std::string &name, int value) {
    return get<int>(section, name, value);
}

bool Config::get(const std::string &section, const std::string &name, bool value) {
    return get<bool>(section, name, value);
}

std::string Config::get(const std::string &section, const std::string &name, const std::string &value) {
    return get<std::string>(section, name, value);
}

std::string Config::get(const std::string &section, const std::string &name, const char *value) {
    return get<std::string>(section, name, std::string(value));
}

} // namespace utils
} // namespace huoguo