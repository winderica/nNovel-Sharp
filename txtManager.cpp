#include "txtManager.h"

uint32_t TxtManager::fileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

TxtManager::TxtManager(const std::string &filename) {
    auto txtPath = "/documents/" + filename + ".txt.tns";
    txt = fopen(txtPath.c_str(), "r");
    auto divPath = "/documents/" + filename + ".div.tns";
    if (access(divPath.c_str(), F_OK) != 0) {
        auto div = fopen(divPath.c_str(), "w");
        uint8_t buffer[BUFFER_SIZE];
        uint32_t length = 0;
        fwrite(&length, sizeof(length), 1, div);
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            fseek(txt, length, SEEK_SET);
            fread(buffer, BUFFER_SIZE, 1, txt);
            auto i = buffer;
            uint32_t x = 0;
            uint32_t y = 0;
            while (*i) {
                auto t = i;
                auto c = decodeUTF8(t);
                auto width = getWidth(c);
                if (c == '\n' || x + width > Screen::WIDTH) {
                    x = 0;
                    y += 16;
                    if (y >= Screen::HEIGHT) {
                        if (c == '\n') {
                            i = t;
                        }
                        break;
                    }
                }
                x += width;
                i = t;
            }
            length += i - buffer;
            fwrite(&length, sizeof(length), 1, div);
            if (!*i) {
                break;
            }
        }
        fclose(div);
    }
    auto div = fopen(divPath.c_str(), "r");
    auto divSize = fileSize(div);
    pages = std::vector<uint32_t>(divSize / sizeof(uint32_t));
    fread(pages.data(), divSize, 1, div);
    fclose(div);
}

uint32_t TxtManager::offset(uint32_t page) {
    return pages[page];
}

uint32_t TxtManager::size(uint32_t page) {
    return offset(page + 1) - offset(page);
}

uint32_t TxtManager::total() {
    return pages.size() - 1;
}

uint8_t *TxtManager::getData(uint32_t page) {
    memset(buffer, 0, BUFFER_SIZE);
    fseek(txt, offset(page), SEEK_SET);
    fread(buffer, size(page), 1, txt);
    return buffer;
}

TxtManager::~TxtManager() {
    fclose(txt);
}
