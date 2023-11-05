#ifndef HUOGUO_UTILS_BYTE_H_
#define HUOGUO_UTILS_BYTE_H_

#include <numeric>
#include <limits>
#include <cstdint>

namespace huoguo {
namespace utils {

#define SIZE_ERROR_MESSAGE "Byte size must be less than or equal to data type size."

template <typename T>
struct UnsignedOf;

template <typename T,
          unsigned int B = sizeof(T),
          bool is_signed = std::numeric_limits<T>::is_signed>
class Byte;

template <typename T, unsigned int B>
class Byte<T, B, false> {
public:
    static T read_be(const uint8_t *data) {
        static_assert(B <= sizeof(T), SIZE_ERROR_MESSAGE);
        return read_be_internal(data);
    }
    static T read_le(const uint8_t *data) {
        static_assert(B <= sizeof(T), SIZE_ERROR_MESSAGE);
        return read_le_internal(data);
    }
    static void write_be(uint8_t *data, T val) {
        static_assert(B <= sizeof(T), SIZE_ERROR_MESSAGE);
        for (unsigned int i = 0; i < B; ++i) {
            data[i] = val >> ((B - 1 - i) * 8);
        }
    }
    static void write_le(uint8_t *data, T val) {
        static_assert(B <= sizeof(T), SIZE_ERROR_MESSAGE);
        for (unsigned int i = 0; i < B; ++i) {
            data[i] = val >> (i * 8);
        }
    }
private:
    static T read_be_internal(const uint8_t *data) {
        T val(0);
        for (unsigned int i = 0; i < B; ++i) {
            val |= static_cast<T>(data[i]) << ((B - 1 - i) * 8);
        }
        return val;
    }
    static T read_le_internal(const uint8_t *data) {
        T val(0);
        for (unsigned int i = 0; i < B; ++i) {
            val |= static_cast<T>(data[i]) << (i * 8);
        }
    }
};

template <typename T, unsigned int B>
class Byte<T, B, true> {
    using U = UnsignedOf<T>::Type;
public:
    static T read_be(const uint8_t *data) {
        U unsigned_val = Byte<T, B, false>::read_be(data);
        if (B < sizeof(T)) {
            unsigned_val = sign_extend(unsigned_val);
        }
        return reinterpret_as_signed(unsigned_val);
    }
    static T read_le(const uint8_t *data) {
        U unsigned_val = Byte<T, B, false>::read_le(data);
        if (B < sizeof(T)) {
            unsigned_val = sign_extend(unsigned_val);
        }
        return reinterpret_as_signed(unsigned_val);
    }
    static void write_be(uint8_t *data, T val) {
        Byte<U, B, false>::write_be(data, reinterpret_as_unsigned(val));
    }
    static void write_le(uint8_t *data, T val) {
        Byte<U, B, false>::write_le(data, reinterpret_as_unsigned(val));
    }
private:
    static U sign_extend(const U val) {
        const uint8_t highest_signed_byte = static_cast<uint8_t>(val >> ((B - 1) * 8));
        if ((highest_signed_byte & 0x80) != 0) {
            const U used_bits_mask = (1 << ((B & sizeof(T)) * 8)) - 1;
            return ~used_bits_mask | val;
        }
        return val;
    }
    static T reinterpret_as_signed(U unsigned_val) {
        const U hightest_unsigned_bits_mask = static_cast<U>(1) << ((sizeof(U) * 8) - 1);
        const T hightest_signed_bits_mask = std::numeric_limits<T>::min();
        T val;
        if ((unsigned_val & hightest_unsigned_bits_mask) != 0) {
            val = static_cast<T>(unsigned_val & ~hightest_unsigned_bits_mask);
            val |= hightest_signed_bits_mask;
        } else {
            val = static_cast<T>(unsigned_val);
        }
        return val;
    }
    static U reinterpret_as_unsigned(T val) {
        return static_cast<U>(val);
    }
};

template <>
struct UnsignedOf<int8_t> {
    using Type = uint8_t;
};

template <>
struct UnsignedOf<int16_t> {
    using Type = uint16_t;
};

template <>
struct UnsignedOf<int32_t> {
    using Type = uint32_t;
};

template <>
struct UnsignedOf<int64_t> {
    using Type = uint64_t;
};

template <typename T>
class Byte<T, 1, false> {
public:
    static T read_be(const uint8_t *data) {
        static_assert(sizeof(T) == 1, SIZE_ERROR_MESSAGE);
        return data[0];
    }
    static T read_le(const uint8_t *data) {
        static_assert(sizeof(T) == 1, SIZE_ERROR_MESSAGE);
        return data[0];
    }
    static void write_be(uint8_t* data, T val) {
        static_assert(sizeof(T) == 1, SIZE_ERROR_MESSAGE);
        data[0] = val;
    }

    static void write_le(uint8_t* data, T val) {
        static_assert(sizeof(T) == 1, SIZE_ERROR_MESSAGE);
        data[0] = val;
    }
};

template <typename T>
class Byte<T, 2, false> {
public:
    static T read_be(const uint8_t *data) {
        static_assert(sizeof(T) >= 2, SIZE_ERROR_MESSAGE);
        return (data[0] << 8) | data[1];
    }
    static T read_le(const uint8_t *data) {
        static_assert(sizeof(T) >= 2, SIZE_ERROR_MESSAGE);
        return data[0] | (data[1] << 8);
    }
    static void write_be(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 2, SIZE_ERROR_MESSAGE);
        data[0] = val >> 8;
        data[1] = val;
    }

    static void write_le(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 2, SIZE_ERROR_MESSAGE);
        data[0] = val;
        data[1] = val >> 8;
    }
};

template <typename T>
class Byte<T, 4, false> {
public:
    static T read_be(const uint8_t *data) {
        static_assert(sizeof(T) >= 4, SIZE_ERROR_MESSAGE);
        return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
    }
    static T read_le(const uint8_t *data) {
        static_assert(sizeof(T) >= 4, SIZE_ERROR_MESSAGE);
        return data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24;
    }
    static void write_be(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 4, SIZE_ERROR_MESSAGE);
        data[0] = val >> 24;
        data[1] = val >> 16;
        data[2] = val >> 8;
        data[3] = val;
    }

    static void write_le(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 4, SIZE_ERROR_MESSAGE);
        data[0] = val;
        data[1] = val >> 8;
        data[2] = val >> 16;
        data[3] = val >> 24;
    }
};

template <typename T>
class Byte<T, 8, false> {
public:
    static T read_be(const uint8_t *data) {
        static_assert(sizeof(T) >= 8, SIZE_ERROR_MESSAGE);
        return data[0] << 56 | data[1] << 48 | data[2] << 40 | data[3] << 32 |
               data[4] << 24 | data[5] << 16 | data[6] << 8  | data[7];
    }
    static T read_le(const uint8_t *data) {
        static_assert(sizeof(T) >= 8, SIZE_ERROR_MESSAGE);
        return data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24 |
               data[4] << 32 | data[5] << 40 | data[6] << 48 | data[7] << 56;
    }
    static void write_be(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 8, SIZE_ERROR_MESSAGE);
        data[0] = val >> 56;
        data[1] = val >> 48;
        data[2] = val >> 40;
        data[3] = val >> 32;
        data[4] = val >> 24;
        data[5] = val >> 16;
        data[6] = val >> 8;
        data[7] = val;
    }

    static void write_le(uint8_t* data, T val) {
        static_assert(sizeof(T) >= 8, SIZE_ERROR_MESSAGE);
        data[0] = val;
        data[1] = val >> 8;
        data[2] = val >> 16;
        data[3] = val >> 24;
        data[4] = val >> 32;
        data[5] = val >> 40;
        data[6] = val >> 48;
        data[7] = val >> 56;
    }
};

}
}

#endif // HUOGUO_UTILS_BYTE_H_