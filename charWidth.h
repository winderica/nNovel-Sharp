#include <algorithm>
#include <functional>

uint32_t arr[] = {
    0x0000, 0x0020, 0x007f, 0x00a0, 0x00ad, 0x00ae, 0x034f, 0x0350, 0x035c, 0x0363, 0x0378, 0x037a, 0x0380, 0x0384, 0x038b, 0x038c, 0x038d, 0x038e,
    0x03a2, 0x03a3, 0x0488, 0x048a, 0x052a, 0x052c, 0x0530, 0x0531, 0x0557, 0x0559, 0x058b, 0x058f, 0x0590, 0x0591, 0x05c8, 0x05d0, 0x05eb, 0x05ef,
    0x05f5, 0x0609, 0x060b, 0x060c, 0x060e, 0x0610, 0x0611, 0x0618, 0x061c, 0x061f, 0x0656, 0x0657, 0x06aa, 0x06ab, 0x06d6, 0x06db, 0x06dc, 0x06df,
    0x06e2, 0x06e4, 0x06e8, 0x06ee, 0x0700, 0x0750, 0x0790, 0x0791, 0x079d, 0x07a0, 0x07b2, 0x07c0, 0x07fb, 0x07fd, 0x0800, 0x08a0, 0x08b5, 0x08b6,
    0x08c8, 0x08d3, 0x08da, 0x08e0, 0x0900, 0x0e01, 0x0e3b, 0x0e3f, 0x0e5b, 0x0e81, 0x0e83, 0x0e84, 0x0e85, 0x0e86, 0x0e8b, 0x0e8c, 0x0ea4, 0x0ea5,
    0x0ea6, 0x0ea7, 0x0ebe, 0x0ec0, 0x0ec5, 0x0ec6, 0x0ec7, 0x0ec8, 0x0ece, 0x0ed0, 0x0eda, 0x0edc, 0x0ee0, 0x0f00, 0x0f02, 0x0f04, 0x0f16, 0x0f19,
    0x0f3a, 0x0f3c, 0x0f48, 0x0f49, 0x0f6d, 0x0f71, 0x0f88, 0x0f89, 0x0f98, 0x0f99, 0x0fbd, 0x0fbe, 0x0fc5, 0x0fce, 0x0fd0, 0x0fd1, 0x0fd5, 0x10a0,
    0x10c6, 0x10c7, 0x10c8, 0x10cd, 0x10ce, 0x10d0, 0x1100, 0x1343, 0x1344, 0x1361, 0x1362, 0x1390, 0x1395, 0x1396, 0x1397, 0x1399, 0x139a, 0x13a0,
    0x13f6, 0x13f8, 0x13fe, 0x1400, 0x1401, 0x141e, 0x142b, 0x1433, 0x143a, 0x1449, 0x144c, 0x1466, 0x1467, 0x146b, 0x14c0, 0x14d0, 0x14d3, 0x14ea,
    0x150c, 0x1525, 0x1542, 0x1548, 0x1553, 0x155d, 0x155e, 0x156a, 0x156b, 0x157b, 0x157e, 0x1586, 0x158a, 0x1597, 0x159b, 0x159f, 0x15a0, 0x15a6,
    0x15b8, 0x15ee, 0x15ef, 0x1601, 0x1604, 0x1646, 0x1648, 0x165a, 0x165b, 0x166d, 0x166f, 0x1677, 0x1680, 0x16a0, 0x16e0, 0x16e1, 0x16e2, 0x16e3,
    0x16f9, 0x1762, 0x1763, 0x17bb, 0x17bc, 0x17cb, 0x17cc, 0x17d6, 0x17d7, 0x17dc, 0x17dd, 0x17f0, 0x17fa, 0x18b4, 0x18b7, 0x18b8, 0x18bb, 0x18be,
    0x18c0, 0x18c3, 0x18c6, 0x18d4, 0x18e0, 0x18e9, 0x18ea, 0x18eb, 0x18ec, 0x18f3, 0x18f6, 0x1950, 0x196e, 0x1970, 0x1975, 0x1983, 0x1984, 0x198f,
    0x1990, 0x1991, 0x1992, 0x199a, 0x199b, 0x199e, 0x199f, 0x19a1, 0x19a2, 0x19a3, 0x19a5, 0x19a7, 0x19a8, 0x19b0, 0x19b4, 0x19b7, 0x19bb, 0x19c1,
    0x19c2, 0x19c6, 0x19c7, 0x19c8, 0x19ca, 0x19d0, 0x19d5, 0x19d6, 0x19d7, 0x19d8, 0x19da, 0x1ab0, 0x1ac1, 0x1c50, 0x1c89, 0x1c90, 0x1cbb, 0x1cbd,
    0x1cc0, 0x1d00, 0x1d7a, 0x1d7b, 0x1dcd, 0x1dce, 0x1dfa, 0x1dfb, 0x1dfc, 0x1dfd, 0x1f16, 0x1f18, 0x1f1e, 0x1f20, 0x1f46, 0x1f48, 0x1f4e, 0x1f50,
    0x1f58, 0x1f59, 0x1f5a, 0x1f5b, 0x1f5c, 0x1f5d, 0x1f5e, 0x1f5f, 0x1f7e, 0x1f80, 0x1fb5, 0x1fb6, 0x1fc5, 0x1fc6, 0x1fd4, 0x1fd6, 0x1fdc, 0x1fdd,
    0x1ff0, 0x1ff2, 0x1ff5, 0x1ff6, 0x1fff, 0x2000, 0x200b, 0x2010, 0x2028, 0x202f, 0x2057, 0x2058, 0x2060, 0x2070, 0x2072, 0x2074, 0x208f, 0x2090,
    0x209d, 0x20a0, 0x20b9, 0x20ba, 0x20c0, 0x20d0, 0x20dd, 0x20e1, 0x20e2, 0x20e5, 0x20e7, 0x20e8, 0x20ea, 0x20eb, 0x20f1, 0x2100, 0x210e, 0x2110,
    0x212e, 0x212f, 0x213a, 0x213e, 0x213f, 0x2141, 0x2145, 0x214a, 0x214c, 0x214d, 0x214f, 0x2150, 0x2182, 0x2183, 0x2188, 0x2189, 0x218c, 0x2190,
    0x219c, 0x219e, 0x21f4, 0x21f5, 0x21f9, 0x21fd, 0x21ff, 0x2200, 0x22b6, 0x22b9, 0x22d8, 0x22da, 0x22f2, 0x22f4, 0x22f5, 0x22f7, 0x22f9, 0x22fc,
    0x22fd, 0x22fe, 0x22ff, 0x2301, 0x2316, 0x2317, 0x2329, 0x232b, 0x232c, 0x2336, 0x237b, 0x237f, 0x2381, 0x2395, 0x2397, 0x239b, 0x23b2, 0x23b7,
    0x23c0, 0x23cb, 0x23cd, 0x23cf, 0x23d4, 0x23da, 0x23db, 0x23e8, 0x23e9, 0x2422, 0x2427, 0x2440, 0x244b, 0x2500, 0x25ef, 0x25f0, 0x2603, 0x2604,
    0x2610, 0x2613, 0x2615, 0x261a, 0x2622, 0x2625, 0x262b, 0x262d, 0x262f, 0x2638, 0x2672, 0x2690, 0x2692, 0x26a1, 0x26a2, 0x26a8, 0x26a9, 0x26aa,
    0x26ad, 0x26b2, 0x26b6, 0x26b7, 0x26bd, 0x26e2, 0x26e3, 0x2768, 0x2776, 0x27b0, 0x27b1, 0x27c0, 0x27c1, 0x27c2, 0x27c3, 0x27c5, 0x27c8, 0x27ca,
    0x27cb, 0x27d1, 0x27d2, 0x27d3, 0x27d5, 0x27df, 0x27e1, 0x27e6, 0x27f0, 0x2800, 0x2900, 0x2908, 0x290a, 0x2912, 0x2914, 0x2938, 0x293a, 0x2949,
    0x294a, 0x294c, 0x294e, 0x294f, 0x2950, 0x2951, 0x2952, 0x2954, 0x2956, 0x2958, 0x295a, 0x295c, 0x295e, 0x2960, 0x2962, 0x297c, 0x297e, 0x2980,
    0x2993, 0x2997, 0x299e, 0x299f, 0x29a8, 0x29d1, 0x29da, 0x29dc, 0x29df, 0x29e1, 0x29e2, 0x29eb, 0x29ec, 0x29ee, 0x29f4, 0x29f5, 0x29fe, 0x2a0b,
    0x2a0c, 0x2a0d, 0x2a1d, 0x2a1e, 0x2a20, 0x2a21, 0x2a2d, 0x2a2f, 0x2a33, 0x2a3c, 0x2a4e, 0x2a66, 0x2a68, 0x2a6a, 0x2a74, 0x2a77, 0x2a78, 0x2a8b,
    0x2a8d, 0x2a8f, 0x2a95, 0x2abf, 0x2acd, 0x2ad3, 0x2ad7, 0x2ade, 0x2adf, 0x2aee, 0x2af3, 0x2af6, 0x2af7, 0x2afe, 0x2b00, 0x2b06, 0x2b08, 0x2b0d,
    0x2b0e, 0x2b1d, 0x2b1f, 0x2b25, 0x2b2c, 0x2b2e, 0x2b30, 0x2b31, 0x2b32, 0x2b4e, 0x2b50, 0x2bc9, 0x2bca, 0x2bff, 0x2c0f, 0x2c10, 0x2c1f, 0x2c20,
    0x2c27, 0x2c2a, 0x2c2f, 0x2c30, 0x2c3f, 0x2c40, 0x2c4f, 0x2c50, 0x2c57, 0x2c5a, 0x2c5f, 0x2c60, 0x2ce7, 0x2ce8, 0x2cea, 0x2ceb, 0x2cef, 0x2cf0,
    0x2cf4, 0x2cf9, 0x2d05, 0x2d06, 0x2d07, 0x2d08, 0x2d0a, 0x2d0b, 0x2d0d, 0x2d0e, 0x2d10, 0x2d11, 0x2d13, 0x2d15, 0x2d1b, 0x2d1d, 0x2d20, 0x2d21,
    0x2d25, 0x2d27, 0x2d28, 0x2d2d, 0x2d2e, 0x2d30, 0x2d48, 0x2d49, 0x2d68, 0x2d6f, 0x2d71, 0x2d7f, 0x2d80, 0x2de0, 0x2e0e, 0x2e12, 0x2e13, 0x2e16,
    0x2e3a, 0x2e3c, 0x2e43, 0x2e44, 0x2e50, 0x2e52, 0x2e53, 0x303f, 0x3040, 0xa4d0, 0xa500, 0xa640, 0xa64c, 0xa64e, 0xa65e, 0xa65f, 0xa662, 0xa668,
    0xa66c, 0xa66f, 0xa670, 0xa671, 0xa672, 0xa673, 0xa684, 0xa686, 0xa698, 0xa69a, 0xa6f8, 0xa700, 0xa728, 0xa72a, 0xa732, 0xa73e, 0xa74e, 0xa750,
    0xa758, 0xa75a, 0xa771, 0xa778, 0xa7c0, 0xa7c4, 0xa7cb, 0xa7f5, 0xa7ff, 0xa828, 0xa82a, 0xab30, 0xab66, 0xab68, 0xab6c, 0xab70, 0xabc0, 0xfb00,
    0xfb07, 0xfb13, 0xfb18, 0xfb1d, 0xfb21, 0xfb29, 0xfb37, 0xfb38, 0xfb3d, 0xfb3e, 0xfb3f, 0xfb40, 0xfb42, 0xfb43, 0xfb45, 0xfb46, 0xfbc2, 0xfbd3,
    0xfc1f, 0xfc20, 0xfc21, 0xfc22, 0xfc25, 0xfc26, 0xfc3d, 0xfc3f, 0xfcad, 0xfcb0, 0xfcb1, 0xfcb8, 0xfce7, 0xfceb, 0xfcfb, 0xfcff, 0xfd17, 0xfd21,
    0xfd2d, 0xfd33, 0xfd34, 0xfd3a, 0xfd3e, 0xfe20, 0xfe30, 0xfe70, 0xfe75, 0xfe76, 0xfefd, 0xff61, 0xffbf, 0xffc2, 0xffc8, 0xffca, 0xffd0, 0xffd2,
    0xffd8, 0xffda, 0xffdd, 0xffe8, 0xffef, 0xfffd, 0xfffe
};

int getWidth(uint32_t value) {
    if (value == '\n' || value == '\r' || value == 0xfeff) {
        return 0;
    }
    auto index = std::distance(std::upper_bound(std::rbegin(arr), std::rend(arr), value, std::greater_equal<>()), std::rend(arr)) - 1;
    return index % 2 ? 8 : 16;
}
