#ifndef NNOVEL_FONT
#define NNOVEL_FONT

#include <os.h>

class Font {
public:
    static constexpr uint32_t GLYPH_SIZE = 32;

    explicit Font(const char *path);

    ~Font();

    uint8_t *getGlyph(uint32_t unicode);

private:
    FILE *file;
    uint8_t glyph[GLYPH_SIZE] = {0};
};

#endif
