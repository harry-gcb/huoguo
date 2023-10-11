#include <fstream>
#include <iostream>
#include <sstream>
#include "utils_config.h"
#include "utils_string.h"

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

bool Config::get(const std::string &section, const std::string &name, std::string &value) {
    auto s = m_config.find(section);
    if (s == m_config.end()) {
        return false;
    }
    auto n = s->second.find(name);
    if (n == s->second.end())
    {
        return false;
    }
    value = n->second;
    return true;
}

int Config::get(const std::string &section, const std::string &name, int value) {
    std::string out;
    if (!get(section, name, out)) {
        return value;
    }
    std::stringstream ss(out);
    ss >> value;
    return value;
}

bool Config::get(const std::string &section, const std::string &name, bool value) {
    std::string in;
    if (!get(section, name, in)) {
        return value;
    }
    return (to_lower(in) == "false" || in == "0" || to_lower(in) == "disable") ? false : true;
}

std::string Config::get(const std::string &section, const std::string &name, const std::string &value) {
    std::string out;
    if (!get(section, name, out)) {
        return value;
    }
    return out;
}

std::string Config::get(const std::string &section, const std::string &name, const char *value) {
    std::string out;
    if (!get(section, name, out)) {
        return value;
    }
    return out;
}

} // namespace utils
} // namespace huoguo