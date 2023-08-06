#include "option.h"

namespace huoguo {
namespace utils {

Option Option::option;

template <typename T>
T to_T(const std::string &value) {
    if (typeid(std::string) == typeid(T)) {
        return value;
    }
}

template <typename T>
Option &Option::add(const std::string &s, const std::string &l, const std::string &h, const T &v) {
    return *this;
}

template <typename T>
T Option::get(const std::string &cmd) {
    auto it = m_option.find(cmd);
    if (it != m_option.end()) {
        return to_T<T>(it->second.cmd_value);
    }
    return {};
}

bool Option::is_exists(const std::string &cmd) {
    auto it = m_option.find(cmd);
    if (it == m_option.end()) {
        return false;
    }
    return it->second.cmd_exists;
}

}}