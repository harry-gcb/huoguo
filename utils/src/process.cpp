#include "process.h"

#include <unistd.h>

namespace huoguo {
namespace utils {

int getpid() {
    return ::getpid();
}

} // namespace utils
} // namespace huoguo
