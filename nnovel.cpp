#include <os.h>

#include "screen.h"
#include "menu.h"
#include "txtManager.h"

int main(int argc, char *argv[]) {
    auto screen = Screen();
    auto font = Font("unifont");
    auto manager = TxtManager(argc == 1 ? "/documents/a.txt.tns" : argv[1]);
    auto menu = Menu(screen, font);
    uint32_t page = 0;
    auto shouldExit = false;
    auto isNightMode = false;

    auto jumpTo = [&page, &manager, &menu]() {
        auto result = menu.showSpinners("输入页码", 30, 30);
        if (result == 0) {
            page = 0;
        } else if (result > 0) {
            page = result - 1;
            if (page > manager.total() - 1) {
                page = manager.total() - 1;
            }
        }
    };
    auto setAutoScroll = [&menu]() {
        auto result = menu.showSpinners("输入秒数", 30, 30);
        if (result < 0) {
            return;
        }
        // TODO
    };
    auto loadBookmark = []() {
        // TODO
    };
    auto saveBookmark = []() {
        // TODO
    };
    auto toggleSettings = []() {
        // TODO
    };
    auto toggleNightMode = [&isNightMode]() {
        isNightMode = !isNightMode;
    };
    auto clearAndExit = [&shouldExit]() {
        // TODO
        shouldExit = true;
    };
    auto exit = [&shouldExit]() {
        shouldExit = true;
    };
    while (!shouldExit) {
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
        if (isNightMode) {
            screen.invertArea(0, 0, Screen::WIDTH, Screen::HEIGHT);
        }
        screen.render();
        wait_key_pressed();
        if (isKeyPressed(KEY_NSPIRE_MENU)) {
            menu.showOptions(
                {"页码跳转(tab)", "自动翻页(scratchpad)", "读取书签(L)", "保存书签(S)", "设置(ctrl)", "夜间模式(shift)", "清空分页文件并退出", "退出(esc)"},
                {jumpTo, setAutoScroll, loadBookmark, saveBookmark, toggleSettings, toggleNightMode, clearAndExit, exit}
            );
        } else if (page != 0 && isKeyPressed(KEY_NSPIRE_UP)) {
            page--;
        } else if (page != manager.total() - 1 && isKeyPressed(KEY_NSPIRE_DOWN)) {
            page++;
        } else if (isKeyPressed(KEY_NSPIRE_TAB)) {
            jumpTo();
        } else if (isKeyPressed(KEY_NSPIRE_SCRATCHPAD)) {
            setAutoScroll();
        } else if (isKeyPressed(KEY_NSPIRE_L)) {
            loadBookmark();
        } else if (isKeyPressed(KEY_NSPIRE_S)) {
            saveBookmark();
        } else if (isKeyPressed(KEY_NSPIRE_CTRL)) {
            toggleSettings();
        } else if (isKeyPressed(KEY_NSPIRE_SHIFT)) {
            toggleNightMode();
        } else if (isKeyPressed(KEY_NSPIRE_ESC)) {
            exit();
        }
    }
    return 0;
}