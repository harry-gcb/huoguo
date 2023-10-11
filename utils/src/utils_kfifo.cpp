#include "utils_kfifo.h"
#include "utils_bits.h"
#include <cstring>

namespace huoguo {
namespace utils {

#define KFIFO_IF_SIZE_EQ_ZERO 1024

Kfifo::Kfifo(uint32_t size) {
    if (0 == size) {
        size = KFIFO_IF_SIZE_EQ_ZERO;
    } else if (!is_power_of_2(size)) {
        size = roundup_pow_of_2(size);
    }
    m_data = new uint8_t[size];
    m_size = size;
    m_mask = m_size - 1;
    m_in   = 0;
    m_out  = 0;
}

Kfifo::~Kfifo() {
    if (m_data) {
        delete []m_data;
        m_data = nullptr;
    }
}

// 返回实际写入缓冲区中的数据
uint32_t Kfifo::put(const uint8_t *buffer, uint32_t len) {
    uint32_t l = 0;
    // 当前缓冲区空闲空间
    len = std::min(len, m_size - m_in + m_out);
    // 当前in位置到buffer末尾的长度
    l = std::min(len, m_size - (m_in & m_mask));
    memcpy(m_data + (m_in & m_mask), buffer, l);
    memcpy(m_data, buffer + l, len - l);
    m_in.fetch_add(len, std::memory_order_release);
    return len;
}

uint32_t Kfifo::get(uint8_t *buffer, uint32_t len) {
    uint32_t l = 0;
    len = std::min(len, m_in - m_out);
    l = std::min(len, m_size - (m_out & m_mask));
    memcpy(buffer, m_data + (m_out & m_mask), l);
    memcpy(buffer + l, m_data, len - l);
    m_out.fetch_add(len, std::memory_order_acq_rel);
    return len;
}

uint32_t Kfifo::size() const {
    return m_size;
}

uint32_t Kfifo::length() const {
    return m_in - m_out;
}

uint32_t Kfifo::avail() const {
    return m_size - length();
}

bool Kfifo::is_empty() const {
    return m_in == m_out;
}

bool Kfifo::is_full() const {
    return length() > m_mask;
}

void Kfifo::reset() {
    m_in = m_out = 0;
}

}
}