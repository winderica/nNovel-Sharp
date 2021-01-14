#include "font.h"

Font::Font(const std::string &filename) {
    auto path = "/documents/fonts/" + filename + ".nft.tns";
    file = fopen(path.c_str(), "r");
    if (!file) {
        show_msgbox("Fatal Error", "Cannot open font file");
        exit(0);
    }
}

uint8_t *Font::getGlyph(uint32_t unicode) {
    fseek(file, unicode * GLYPH_SIZE, SEEK_SET);
    fread(glyph, GLYPH_SIZE, 1, file);
    return glyph;
}

Font::~Font() {
    fclose(file);
}
