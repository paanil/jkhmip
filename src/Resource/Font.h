
#ifndef __FONT_H__
#define __FONT_H__

class Texture;

class Font
{
public:
    struct Char
    {
        int x, y, w, h;
        int xoffs, yoffs;
        int advance;
        Char() : x(0), y(0), w(0), h(0), xoffs(0), yoffs(0), advance(0) {}
    };

    int lineH, base;
    int texW, texH;
    Char chars[256];
    Texture *texture;
};

#endif // __FONT_H__
