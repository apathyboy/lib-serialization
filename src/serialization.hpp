
#pragma once

#include <string>
#include <type_traits>

namespace esb {

template <typename StreamT, typename T,
          typename std::enable_if_t<std::is_integral<T>::value, int> = 0>
void read(StreamT& is, T& val) {
    is.read(reinterpret_cast<char*>(&val), sizeof(T));
}

template <typename StreamT, typename T,
          typename std::enable_if_t<std::is_integral<T>::value, int> = 0>
void write(StreamT& os, T& val) {
    os.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template <typename StreamT, typename T,
          typename std::enable_if_t<std::is_enum<T>::value, int> = 0>
void read(StreamT& is, T& val) {
    is.read(reinterpret_cast<char*>(&val), sizeof(T));
}

template <typename StreamT, typename T,
          typename std::enable_if_t<std::is_enum<T>::value, int> = 0>
void write(StreamT& os, const T& val) {
    os.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template <typename StreamT>
void read(StreamT& is, std::string& val) {
    auto length = read<uint16_t>(is);

    val.resize(length);

    is.read(val.data(), length);
}

template <typename StreamT>
void write(StreamT& os, const std::string& val) {
    uint16_t length = static_cast<uint16_t>(val.length());
    write(os, length);

    os.write(val.data(), length);
}

template <typename T, typename StreamT>
T read(StreamT& is) {
    T tmp;
    read(is, tmp);
    return tmp;
}
template <typename T, typename StreamT>
T readAt(StreamT& is, size_t offset) {
    is.seekg(offset);
    return read<T>(is);
}

template <typename T, typename StreamT>
T peekAt(StreamT& is, size_t offset) {
    auto pos = is.tellg();
    T    val = readAt<T>(is, offset);
    is.seekg(pos);
    return val;
}

}  // namespace esb
