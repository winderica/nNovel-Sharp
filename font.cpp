#include "font.h"

Font::Font(const char *path) : file(fopen(path, "r")) {
}

uint8_t *Font::getGlyph(uint32_t unicode) {
    fseek(file, unicode * GLYPH_SIZE, SEEK_SET);
    fread(glyph, GLYPH_SIZE, 1, file);
    return glyph;
}

Font::~Font() {
    fclose(file);
}
