#ifndef HUOGUO_UTILS_SINGLETON_H_
#define HUOGUO_UTILS_SINGLETON_H_

namespace huoguo {
namespace utils {

template <typename T>
class Singleton {
public:
    static T &getInstance() {
        static T instance;
        return instance;
    }
public:
    Singleton(const Singleton &other) = delete;
    Singleton &operator=(const Singleton &other) = delete;
    Singleton(Singleton &&other) = delete;
    Singleton &operator=(Singleton &&other) = delete;
protected:
    Singleton() = default;
    ~Singleton() = default;
};

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_SINGLETON_H_