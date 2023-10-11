#include "utils_process.h"
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

namespace huoguo {
namespace utils {

int getpid() {
#ifdef _WIN32
    return _getpid();
#else
    return ::getpid();
#endif
}

} // namespace utils
} // namespace huoguo
