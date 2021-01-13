#include <os.h>

#include "screen.h"
#include "menu.h"
#include "txtManager.h"

int main() {
    auto screen = Screen();
    auto font = Font("/documents/a.tns");
    auto manager = TxtManager("a");
    uint32_t page = 0;
    while (true) {
        screen.clear();
        auto i = manager.getData(page);
        uint32_t x = 0;
        uint32_t y = 0;
        while (*i) {
            auto c = decodeUTF8(i);
            auto width = getWidth(c);
            if (c == '\n' || x + width > Screen::WIDTH) {
                x = 0;
                y += 16;
                if (y >= Screen::HEIGHT) {
                    break;
                }
            }
            screen.drawGlyph(x, y, width, font.getGlyph(c));
            x += width;
        }
        screen.render();
        wait_key_pressed();
        if (isKeyPressed(KEY_NSPIRE_ESC)) {
            return 0;
        } else if (page != 0 && isKeyPressed(KEY_NSPIRE_UP)) {
            page--;
        } else if (page != manager.total() - 1 && isKeyPressed(KEY_NSPIRE_DOWN)) {
            page++;
        } else if (isKeyPressed(KEY_NSPIRE_MENU)) {
            menu(screen, font, {"test", "测试", "test测试テストтест"});
        }
    }
}