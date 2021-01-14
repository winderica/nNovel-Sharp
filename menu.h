#ifndef NNOVEL_MENU
#define NNOVEL_MENU

#include "screen.h"
#include <string>
#include <functional>

class Menu {
public:
    static constexpr uint32_t H = 20;
    static constexpr uint32_t W = 50;

    Menu(Screen &screen, Font &font);

    void showOptions(
        const std::vector<std::string> &options,
        const std::vector<std::function<void(void)>> &actions,
        uint32_t x1 = 10,
        uint32_t y1 = 10
    );

    // https://en.wikipedia.org/wiki/Spinner_(computing)
    int32_t showSpinners(const std::string &title, uint32_t x1, uint32_t y1);

private:
    Screen &screen;
    Font &font;

    void drawBoxWithShadow(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
};

#endif
