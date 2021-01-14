#include "screen.h"

#include <bitset>

Screen::Screen() : buffer(SIZE, 0) {
#ifdef MOCK_OLD_SCREEN_API
    volatile unsigned *lcd_control = IO_LCD_CONTROL;
    unsigned mode = *lcd_control & ~0b1110;
    *lcd_control = mode | 0b010000000100; // 4bpp + pixels within each byte read as big-endian
#else
    lcd_init(SCR_320x240_565);
#endif
}

void Screen::render() {
#ifdef MOCK_OLD_SCREEN_API
    memcpy(REAL_SCREEN_BASE_ADDRESS, buffer.data(), buffer.size());
#else
    lcd_blit(buffer.data(), SCR_320x240_565);
#endif
}

void Screen::drawPoint(uint32_t x, uint32_t y, uint16_t color) {
#ifdef MOCK_OLD_SCREEN_API
    auto originalColor = buffer[(x + WIDTH * y) / 2];
    buffer[(x + WIDTH * y) / 2] = (x % 2) ? ((originalColor & 0xf0u) | color) : ((originalColor & 0x0fu) | (color << 4u));
#else
    buffer[x + WIDTH * y] = color;
#endif
}

void Screen::drawGlyph(uint32_t x, uint32_t y, uint32_t width, const uint8_t bitmap[Font::GLYPH_SIZE]) {
    for (uint32_t i = 0; i < 16; i++) {
        auto byte = std::bitset<16>(width == 8 ? bitmap[i * 2] : bitmap[i * 2] * 256 + bitmap[i * 2 + 1]);
        for (uint32_t j = 0; j < width; j++) {
            drawPoint(x + width - 1 - j, y + i, byte[j] ? 0x0000 : 0xffff);
        }
    }
}

void Screen::drawArea(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t color) {
#ifdef MOCK_OLD_SCREEN_API
    for (auto x = x1; x <= x2; x++) {
        for (auto y = y1; y <= y2; y++) {
            drawPoint(x, y, color);
        }
    }
#else
    for (auto y = y1; y <= y2; y++) {
        std::fill(buffer.begin() + x1 + WIDTH * y, buffer.begin() + x2 + 1 + WIDTH * y, color);
    }
#endif
}

void Screen::invertPoint(uint32_t x, uint32_t y) {
#ifdef MOCK_OLD_SCREEN_API
    auto originalColor = buffer[(x + WIDTH * y) / 2];
    drawPoint(x, y, 0xf - ((x & 1) ? (originalColor & 0x0Fu) : (originalColor >> 4u)));
#else
    buffer[x + WIDTH * y] = ~buffer[x + WIDTH * y];
#endif
}

void Screen::invertArea(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    for (auto x = x1; x <= x2; x++) {
        for (auto y = y1; y <= y2; y++) {
            invertPoint(x, y);
        }
    }
}

void Screen::clear() {
    std::fill(buffer.begin(), buffer.end(), 0xffff);
}

Screen::~Screen() {
#ifndef MOCK_OLD_SCREEN_API
    lcd_init(SCR_TYPE_INVALID);
#endif
}
