#ifndef NNOVEL_SCREEN
#define NNOVEL_SCREEN

//#define MOCK_OLD_SCREEN_API

#include <vector>

#include "font.h"

class Screen {
public:
    static const uint32_t WIDTH = 320;
    static const uint32_t HEIGHT = 240;
#ifdef MOCK_OLD_SCREEN_API
    static constexpr uint32_t SIZE = WIDTH * HEIGHT / 2;
#else
    static constexpr uint32_t SIZE = WIDTH * HEIGHT;
#endif

    Screen();

    ~Screen();

    void clear();

    void drawPoint(uint32_t x, uint32_t y, uint16_t color);

    void drawGlyph(uint32_t x, uint32_t y, uint32_t width, const uint8_t bitmap[Font::GLYPH_SIZE]);

    void drawArea(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t color);

    void invertPoint(uint32_t x, uint32_t y);

    void invertArea(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

    void render();

private:
#ifdef MOCK_OLD_SCREEN_API
    std::vector<uint8_t> buffer;
#else
    std::vector<uint16_t> buffer;
#endif
};

#endif
