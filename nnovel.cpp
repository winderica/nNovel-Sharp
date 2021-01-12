#include <os.h>
#include "charWidth.h"

const uint32_t WIDTH = 320;
const uint32_t HEIGHT = 240;
const uint32_t SCREEN_SIZE = WIDTH * HEIGHT;
const uint32_t GLYPH_SIZE = 32;
const uint32_t BUFFER_SIZE = SCREEN_SIZE / GLYPH_SIZE / 8 * 4;

std::pair<uint32_t, uint32_t> decodeUTF8(uint8_t *i) {
    if (*i < 0x80) {
        return {i[0], 1};
    }
    if (*i < 0xE0) {
        return {((i[0] & 0x1Fu) << 6u) | (i[1] & 0x3Fu), 2};
    }
    if (*i < 0xF0) {
        return {((i[0] & 0x0Fu) << 12u) | ((i[1] & 0x3Fu) << 6u) | (i[2] & 0x3Fu), 3};
    }
    if (*i < 0xF8) {
        return {((i[0] & 0x07u) << 18u) | ((i[1] & 0x3Fu) << 12u) | ((i[2] & 0x3Fu) << 6u) | (i[3] & 0x3Fu), 4};
    }
    return {0, 0};
}

void divide() {
    uint8_t buffer[BUFFER_SIZE];
    auto f = fopen("/documents/a.txt.tns", "r");
    auto div = fopen("/documents/a.div.tns", "w");
    uint32_t length = 0;
    fwrite(&length, sizeof(length), 1, div);
    while (true) {
        std::fill(std::begin(buffer), std::end(buffer), 0);
        fseek(f, length, SEEK_SET);
        fread(buffer, BUFFER_SIZE, 1, f);
        auto i = buffer;
        uint32_t x = 0;
        uint32_t y = 0;
        while (*i) {
            auto[c, s] = decodeUTF8(i);
            uint32_t width = getWidth(c);
            if (c == '\n' || x + width > WIDTH) {
                x = 0;
                y += 16;
                if (y >= HEIGHT) {
                    if (c == '\n') {
                        i += s;
                    }
                    break;
                }
            }
            x += width;
            i += s;
        }
        length += i - buffer;
        fwrite(&length, sizeof(length), 1, div);
        if (!*i) {
            break;
        }
    }
    fclose(f);
    fclose(div);
}

class Screen {
private:
    uint16_t buffer[SCREEN_SIZE] = {0};
public:
    Screen() {
        lcd_init(SCR_320x240_565);
    }

    ~Screen() {
        lcd_init(SCR_TYPE_INVALID);
    }

    void clear() {
        memset(buffer, 0xff, sizeof(buffer));
    }

    void draw(uint32_t x, uint32_t y, uint16_t color) {
        buffer[x + WIDTH * y] = color;
    }

    void render() {
        lcd_blit(buffer, SCR_320x240_565);
    }
};

class Font {
private:
    FILE *file;
    uint8_t bitmap[GLYPH_SIZE] = {0};
public:
    explicit Font(const char *filename) {
        file = fopen(filename, "r");
    }

    ~Font() {
        fclose(file);
    }

    void draw(uint32_t unicode, Screen screen, uint32_t x, uint32_t y, uint32_t width) {
        fseek(file, unicode * GLYPH_SIZE, SEEK_SET);
        fread(bitmap, GLYPH_SIZE, 1, file);
        for (uint8_t i = 0; i < 16; i++) {
            for (uint8_t j = 0; j < 8; j++) {
                if (width >= 8) {
                    screen.draw(x + 7 - j, y + i, ((bitmap[i * 2] >> j) % 2) ? 0x0000 : 0xffff);
                }
                if (width >= 16) {
                    screen.draw(x + 15 - j, y + i, ((bitmap[i * 2 + 1] >> j) % 2) ? 0x0000 : 0xffff);
                }
            }
        }
    }
};

int main() {
    divide();
    auto screen = Screen();
    uint8_t buffer[BUFFER_SIZE];
    auto font = Font("/documents/a.tns");
    auto f = fopen("/documents/a.txt.tns", "r");
    auto div = fopen("/documents/a.div.tns", "r");
    uint32_t page = 0;
    fseek(div, 0, SEEK_END);
    uint32_t totalPages = ftell(div) / sizeof(uint32_t);
    while (true) {
        std::fill(std::begin(buffer), std::end(buffer), 0);
        screen.clear();

        fseek(div, page * sizeof(uint32_t), SEEK_SET);
        uint32_t start;
        fread(&start, sizeof(uint32_t), 1, div);
        uint32_t end;
        fread(&end, sizeof(uint32_t), 1, div);

        fseek(f, start, SEEK_SET);
        fread(buffer, end - start, 1, f);

        auto i = buffer;
        uint32_t x = 0;
        uint32_t y = 0;
        while (*i) {
            auto[c, s] = decodeUTF8(i);
            uint32_t width = getWidth(c);
            if (c == '\n' || x + width > WIDTH) {
                x = 0;
                y += 16;
                if (y >= HEIGHT) {
                    break;
                }
            }
            font.draw(c, screen, x, y, width);
            x += width;
            i += s;
        }
        screen.render();
        wait_key_pressed();
        if (isKeyPressed(KEY_NSPIRE_ESC)) {
            fclose(f);
            fclose(div);
            return 0;
        } else if (page != 0 && isKeyPressed(KEY_NSPIRE_UP)) {
            page--;
        } else if (page != totalPages && isKeyPressed(KEY_NSPIRE_DOWN)) {
            page++;
        }
    }
}