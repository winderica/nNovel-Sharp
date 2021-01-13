#include "menu.h"
#include "char.h"

int menu(Screen &screen, Font &font, const std::vector<std::string> &options) {
    int number_of_item = options.size(), selected_item = 0;
    screen.drawArea(9, 10, 211, 10 + 20 * number_of_item, 0);
    screen.drawArea(11, 12, 213, 12 + 20 * number_of_item, 0);
    screen.drawPoint(10, 11 + 20 * number_of_item, 0);
    screen.drawPoint(212, 11, 0);
    screen.drawArea(10, 10, 210, 10 + 20 * number_of_item, 0xffff);
    screen.drawArea(10, 10 + 20 * number_of_item, 210, 10 + 20 * number_of_item, 0);
    for (int i = 0; i < number_of_item; i++) {
        auto option = options[i];
        auto p = option.begin();
        uint32_t x = 12;
        while (p != option.end()) {
            auto c = decodeUTF8(p);
            auto width = getWidth(c);
            screen.drawGlyph(x, 12 + 20 * i, width, font.getGlyph(c));
            x += width;
        }
        screen.drawArea(10, 10 + 20 * i, 210, 10 + 20 * i, 0);
    }
    screen.invertArea(10, 11 + 20 * selected_item, 210, 9 + 20 * (selected_item + 1));
    screen.render();
    while (true) {
        wait_key_pressed();
        if (selected_item != 0 && isKeyPressed(KEY_NSPIRE_UP)) {
            screen.invertArea(10, 11 + 20 * selected_item, 210, 9 + 20 * (selected_item + 1));
            for (int j = 0; j < 20; j++) {
                screen.invertArea(10, 11 + 20 * selected_item - j, 210, 9 + 20 * (selected_item + 1) - j);
                screen.render();
                msleep(1);
                screen.invertArea(10, 11 + 20 * selected_item - j, 210, 9 + 20 * (selected_item + 1) - j);
            }
            selected_item--;
            screen.invertArea(10, 11 + 20 * selected_item, 210, 9 + 20 * (selected_item + 1));
        }
        if (selected_item != number_of_item - 1 && isKeyPressed(KEY_NSPIRE_DOWN)) {
            screen.invertArea(10, 11 + 20 * selected_item, 210, 9 + 20 * (selected_item + 1));
            for (int j = 0; j < 20; j++) {
                screen.invertArea(10, 11 + 20 * selected_item + j, 210, 9 + 20 * (selected_item + 1) + j);
                screen.render();
                msleep(1);
                screen.invertArea(10, 11 + 20 * selected_item + j, 210, 9 + 20 * (selected_item + 1) + j);
            }
            selected_item++;
            screen.invertArea(10, 11 + 20 * selected_item, 210, 9 + 20 * (selected_item + 1));
        }

        screen.render();

        if (isKeyPressed(KEY_NSPIRE_ESC)) {
            selected_item = 0;
            break;
        }
        if (isKeyPressed(KEY_NSPIRE_ENTER) || isKeyPressed(KEY_NSPIRE_CLICK))
            break;
    }
    wait_no_key_pressed();
    return selected_item;
}
//
//int num_input(char *_VRAM, int x, int y, char *msg) {
//    char *VRAM = init_VRAM();
//    memcpy(VRAM, _VRAM, SCREEN_BYTES_SIZE);
//
//    int ap_value[5] = {0, 0, 0, 0, 0};
//    int i, j;
//    int right_key_pressed = 0;
//    uint8_t UP_SELECT[] = {0x0, 0x0, 0x4, 0x0, 0xE, 0x0, 0x1F, 0x0, 0x3F, 0x80, 0x7F, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x0, 0x0};
//    uint8_t UP[] = {0x0, 0x0, 0x4, 0x0, 0xA, 0x0, 0x11, 0x0, 0x20, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0xC0, 0x0, 0x0};
//    uint8_t DOWN_SELECT[] = {0x0, 0x0, 0x7F, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x3F, 0x80, 0x1F, 0x0, 0xE, 0x0, 0x4, 0x0, 0x0, 0x0};
//    uint8_t DOWN[] = {0x0, 0x0, 0x7F, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20, 0x80, 0x11, 0x0, 0xA, 0x0, 0x4, 0x0, 0x0, 0x0};
//
//
//    AreaClr_VRAM(VRAM, x, y, x + 152, y + 82);
//    Draw_Rect_VRAM(VRAM, x, y, x + 150, y + 80, 0);
//    Draw_Line_VRAM(VRAM, x + 1, y + 81, x + 151, y + 81, 0);
//    Draw_Line_VRAM(VRAM, x + 2, y + 82, x + 152, y + 82, 0);
//    Draw_Line_VRAM(VRAM, x + 151, y + 1, x + 151, y + 81, 0);
//    Draw_Line_VRAM(VRAM, x + 152, y + 2, x + 152, y + 82, 0);
//    PrintChStr(VRAM, x + 10, y + 4, msg, 0, 15);
//    for (i = 0; i < 5; i++) {
//        DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 30, 11, 10, UP, 0, 15);
//        DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 56, 11, 10, DOWN, 0, 15);
//        DrawAsciiChar_VRAM(VRAM, x + 30 + 20 * i, y + 43, ap_value[i] + '0', 0, 15);
//    }
//    i = 0;
//    while (1) {
//        for (j = 0; j < 5; j++) {
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * j, y + 30, 11, 10, UP, 0, 15);
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * j, y + 56, 11, 10, DOWN, 0, 15);
//            DrawAsciiChar_VRAM(VRAM, x + 30 + 20 * j, y + 43, ap_value[j] + '0', 0, 15);
//        }
//        if (ap_value[i] == -1)
//            ap_value[i] = 9;
//        DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 30, 11, 10, UP_SELECT, 0, 15);
//        DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 56, 11, 10, DOWN_SELECT, 0, 15);
//        DrawAsciiChar_VRAM(VRAM, x + 30 + 20 * i, y + 43, ap_value[i] + '0', 0, 15);
//        PutDisp_DDVRAM(VRAM);
//        right_key_pressed = 0;
//        wait_key_pressed();
//        if (isKeyPressed(KEY_NSPIRE_UP)) {
//            ap_value[i]++;
//            if (ap_value[i] == 10)
//                ap_value[i] = 0;
//        }
//        if (isKeyPressed(KEY_NSPIRE_DOWN)) {
//            ap_value[i]--;
//        }
//        if (isKeyPressed(KEY_NSPIRE_1)) {
//            ap_value[i] = 1;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_2)) {
//            ap_value[i] = 2;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_3)) {
//            ap_value[i] = 3;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_4)) {
//            ap_value[i] = 4;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_5)) {
//            ap_value[i] = 5;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_6)) {
//            ap_value[i] = 6;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_7)) {
//            ap_value[i] = 7;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_8)) {
//            ap_value[i] = 8;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_9)) {
//            ap_value[i] = 9;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_0)) {
//            ap_value[i] = 0;
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_RIGHT)) {
//            right_key_pressed = 1;
//        }
//        if (isKeyPressed(KEY_NSPIRE_LEFT)) {
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 30, 11, 10, UP, 0, 15);
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 56, 11, 10, DOWN, 0, 15);
//            i--;
//            if (i == -1)
//                i = 4;
//        }
//        if (right_key_pressed == 1) {
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 30, 11, 10, UP, 0, 15);
//            DrawGraph_VRAM(VRAM, x + 28 + 20 * i, y + 56, 11, 10, DOWN, 0, 15);
//            i++;
//            if (i == 5)
//                i = 0;
//
//        }
//        if (isKeyPressed(KEY_NSPIRE_ENTER))
//            return ap_value[0] * 10000 + ap_value[1] * 1000 + ap_value[2] * 100 + ap_value[3] * 10 + ap_value[4];
//        if (isKeyPressed(KEY_NSPIRE_ESC))
//            return -1;
//    }
//}
