#include "menu.h"
#include "char.h"

Menu::Menu(Screen &screen, Font &font) : screen(screen), font(font) {}

void Menu::showOptions(
    const std::vector<std::string> &options,
    const std::vector<std::function<void(void)>> &actions,
    uint32_t x1,
    uint32_t y1
) {
    uint32_t total = H * options.size(), current = 0;
    auto x2 = x1 + W * 4, y2 = y1 + total;
    drawBoxWithShadow(x1, y1, x2, y2);

    auto y = y1;
    for (auto option: options) {
        auto p = option.begin();
        auto x = x1 + 2;
        while (p != option.end()) {
            auto c = decodeUTF8(p);
            auto width = getWidth(c);
            screen.drawGlyph(x, y + 2, width, font.getGlyph(c));
            x += width;
        }
        screen.drawArea(x1, y, x2, y, 0);
        y += H;
    }
    screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
    screen.render();
    while (true) {
        wait_key_pressed();
        if (current != 0 && isKeyPressed(KEY_NSPIRE_UP)) {
            screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
            for (auto i = 0; i < 20; i++) {
                screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
                screen.render();
                msleep(1);
                screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
                current--;
            }
            screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
        }
        if (current != total - H && isKeyPressed(KEY_NSPIRE_DOWN)) {
            screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
            for (auto i = 0; i < 20; i++) {
                screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
                screen.render();
                msleep(1);
                screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
                current++;
            }
            screen.invertArea(x1, y1 + 1 + current, x2, y1 - 1 + current + H);
        }

        screen.render();

        if (isKeyPressed(KEY_NSPIRE_ESC)) {
            wait_no_key_pressed();
            break;
        }
        if (isKeyPressed(KEY_NSPIRE_ENTER) || isKeyPressed(KEY_NSPIRE_CLICK)) {
            wait_no_key_pressed();
            actions[current / 20]();
            break;
        }
    }
}

int32_t Menu::showSpinners(const std::string &title, uint32_t x1, uint32_t y1) {
    uint32_t value[5] = {0, 0, 0, 0, 0};

    auto x2 = x1 + 3 * W, y2 = y1 + 4 * H;
    drawBoxWithShadow(x1, y1, x2, y2);

    auto p = title.begin();
    auto x = x1 + 10;
    while (p != title.end()) {
        auto c = decodeUTF8(p);
        auto width = getWidth(c);
        screen.drawGlyph(x, y1 + 4, width, font.getGlyph(c));
        x += width;
    }

    int current = 0;
    while (true) {
        for (auto i = 0; i < 5; i++) {
            screen.drawGlyph(x1 + 30 + 20 * i, y1 + 30, 8, font.getGlyph(0x25b3));
            screen.drawGlyph(x1 + 30 + 20 * i, y1 + 56, 8, font.getGlyph(0x25bd));
            screen.drawGlyph(x1 + 30 + 20 * i, y1 + 42, 8, font.getGlyph(value[i] + '0'));
        }
        screen.drawGlyph(x1 + 30 + 20 * current, y1 + 30, 8, font.getGlyph(0x25b2));
        screen.drawGlyph(x1 + 30 + 20 * current, y1 + 56, 8, font.getGlyph(0x25bc));
        screen.render();
        wait_key_pressed();
        if (isKeyPressed(KEY_NSPIRE_ENTER)) {
            return value[0] * 10000 + value[1] * 1000 + value[2] * 100 + value[3] * 10 + value[4];
        } else if (isKeyPressed(KEY_NSPIRE_ESC)) {
            return -1;
        } else if (isKeyPressed(KEY_NSPIRE_UP)) {
            value[current] = value[current] == 9 ? 0 : value[current] + 1;
        } else if (isKeyPressed(KEY_NSPIRE_DOWN)) {
            value[current] = value[current] == 0 ? 9 : value[current] - 1;
        } else if (isKeyPressed(KEY_NSPIRE_1)) {
            value[current++] = 1;
        } else if (isKeyPressed(KEY_NSPIRE_2)) {
            value[current++] = 2;
        } else if (isKeyPressed(KEY_NSPIRE_3)) {
            value[current++] = 3;
        } else if (isKeyPressed(KEY_NSPIRE_4)) {
            value[current++] = 4;
        } else if (isKeyPressed(KEY_NSPIRE_5)) {
            value[current++] = 5;
        } else if (isKeyPressed(KEY_NSPIRE_6)) {
            value[current++] = 6;
        } else if (isKeyPressed(KEY_NSPIRE_7)) {
            value[current++] = 7;
        } else if (isKeyPressed(KEY_NSPIRE_8)) {
            value[current++] = 8;
        } else if (isKeyPressed(KEY_NSPIRE_9)) {
            value[current++] = 9;
        } else if (isKeyPressed(KEY_NSPIRE_0)) {
            value[current++] = 0;
        } else if (isKeyPressed(KEY_NSPIRE_RIGHT)) {
            current++;
        } else if (isKeyPressed(KEY_NSPIRE_LEFT)) {
            current--;
        }
        if (current == 5) {
            current = 0;
        } else if (current == -1) {
            current = 4;
        }
    }
}

void Menu::drawBoxWithShadow(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    screen.drawArea(x1 - 1, y1, x2 + 1, y2, 0);
    screen.drawArea(x1 + 1, y1 + 2, x2 + 3, y2 + 2, 0);
    screen.drawPoint(x1, y2 + 1, 0);
    screen.drawPoint(x2 + 2, y1 + 1, 0);
    screen.drawArea(x1, y1 + 1, x2, y2 - 1, 0xffff);
}
