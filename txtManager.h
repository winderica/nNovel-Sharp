#ifndef NNOVEL_TXT_MANAGER
#define NNOVEL_TXT_MANAGER

#include <string>
#include "screen.h"
#include "char.h"

class TxtManager {
public:
    static constexpr uint32_t BUFFER_SIZE = Screen::SIZE / Font::GLYPH_SIZE / 8 * 4;

    static uint32_t fileSize(FILE *file);

    explicit TxtManager(const std::string &filename);

    uint32_t total();

    uint8_t *getData(uint32_t page);

    ~TxtManager();

private:
    FILE *txt;
    std::vector<uint32_t> pages;
    uint8_t buffer[BUFFER_SIZE] = {0};

    uint32_t offset(uint32_t page);

    uint32_t size(uint32_t page);
};

#endif
