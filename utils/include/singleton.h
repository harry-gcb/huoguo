#ifndef HUOGUO_UTILS_SINGLETON_H_
#define HUOGUO_UTILS_SINGLETON_H_

#include "noncopyable.h"

namespace huoguo {
namespace utils {

template <typename T>
class Singleton: public Noncopyable {
public:
    static T &getInstance() {
        static T instance;
        return instance;
    }
};

} // namespace utils
} // namespace huoguo

#endif // HUOGUO_UTILS_SINGLETON_H_