#ifndef HUOGUO_UTILS_CONFIG_H_
#define HUOGUO_UTILS_CONFIG_H_

#include <map>
#include <any>
#include <string>

namespace huoguo {
namespace utils {

#define CONFIG huoguo::utils::Config::config

class Config {
public:
    void init(const std::string &cfg);

    int get(const std::string &section, const std::string &name, int value);
    bool get(const std::string &section, const std::string &name, bool value);
    std::string get(const std::string &section, const std::string &name, const std::string &value);
    std::string get(const std::string &section, const std::string &name, const char *value);
public:
    static Config config;
private:
    template <typename T>
    T get(const std::string &section, const std::string &name, const T &value);

    std::map<std::string, std::map<std::string, std::string>> m_config;
};

} // namespace utils
} // namespace huoguo



#endif // HUOGUO_UTILS_CONFIG_H_