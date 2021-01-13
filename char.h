#ifndef NNOVEL_CHAR
#define NNOVEL_CHAR

#include <os.h>
#include <algorithm>
#include <functional>

uint32_t getWidth(uint32_t value);

template<typename Pointer>
uint32_t decodeUTF8(Pointer &i) {
    if (*i < 0x80) {
        uint32_t res = i[0];
        i += 1;
        return res;
    }
    if (*i < 0xE0) {
        uint32_t res = ((i[0] & 0x1Fu) << 6u) | (i[1] & 0x3Fu);
        i += 2;
        return res;
    }
    if (*i < 0xF0) {
        uint32_t res = ((i[0] & 0x0Fu) << 12u) | ((i[1] & 0x3Fu) << 6u) | (i[2] & 0x3Fu);
        i += 3;
        return res;
    }
    if (*i < 0xF8) {
        uint32_t res = ((i[0] & 0x07u) << 18u) | ((i[1] & 0x3Fu) << 12u) | ((i[2] & 0x3Fu) << 6u) | (i[3] & 0x3Fu);
        i += 4;
        return res;
    }
    return 0;
}

#endif
