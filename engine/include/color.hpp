#ifndef __ENGINE_COLOR__
#define __ENGINE_COLOR__

namespace engine {

struct Color {
    Color(unsigned char _r=0x00, unsigned char _g=0x00, unsigned char _b=0x00,
          unsigned char _a=0xff) : r(_r), g(_g), b(_b), a(_a) {}

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

}

#endif
