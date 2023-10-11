#ifndef HUOGUO_UTILS_NONCOPYABLE_H_
#define HUOGUO_UTILS_NONCOPYABLE_H_

namespace huoguo {
namespace utils {

class Noncopyable {
public:
    Noncopyable(const Noncopyable &other) = delete;
    Noncopyable &operator=(const Noncopyable &other) = delete;
    Noncopyable(Noncopyable &&other) = delete;
    Noncopyable &operator=(Noncopyable &&other) = delete;
protected:
    Noncopyable() = default;
    ~Noncopyable() = default;
};

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_NONCOPYABLE_H_