#include <sstream>
#include <thread>
#include "utils_thread.h"

namespace huoguo {
namespace utils {

uint64_t thread_id() {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return std::stoull(ss.str());
}

}
}