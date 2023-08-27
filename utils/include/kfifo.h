#ifndef HUOGUO_UTILS_KFIFO_H_
#define HUOGUO_UTILS_KFIFO_H_

#include <mutex>
#include <atomic>

namespace huoguo {
namespace utils {

class Kfifo {
public:
    Kfifo(uint32_t size);
    ~Kfifo();

    uint32_t put(const uint8_t *buffer, uint32_t len);
    uint32_t get(uint8_t *buffer, uint32_t len);

    uint32_t size() const;
    uint32_t length() const;
    uint32_t avail() const;
    bool is_empty() const;
    bool is_full() const;
     
    void reset();
private:
    uint8_t *m_data;
    uint32_t m_size;
    uint32_t m_mask;
    std::atomic<uint32_t> m_in;
    std::atomic<uint32_t> m_out;
    std::mutex m_mutex;
};

}
}

#endif // HUOGUO_UTILS_KFIFO_H_