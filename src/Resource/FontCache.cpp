
#include "FontCache.h"
#include "TextureCache.h"
#include "../Logger.h"

#include <fstream>

#define TEST(file) if (!file.good()) { LOG_ERROR("File not good."); return 0; }

FontCache::FontCache() :
    textureCache(0)
{
}

void FontCache::SetTextureCache(TextureCache &textureCache)
{
    this->textureCache = &textureCache;
}

Font *FontCache::Load(const String &filePath)
{
    LOG_INFO("Loading font '%'...", filePath);

    std::ifstream f(filePath.c_str(), std::ifstream::binary);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return 0;
    }

    Font font;

    union { char as_char[4]; uint as_uint; } version;
    union { char as_char[4]; uint size; } block;
    union { char as_char[8]; uint16 data[4]; } common;
    union { char as_char[20]; uint16 udata[10]; int16 sdata[10]; uint id; } chr;

    f.read(version.as_char, 4);
    if (version.as_uint != 0x03464d42)
    {
        LOG_ERROR("Invalid version.");
        return 0;
    }

    TEST(f)

    f.get();
    f.read(block.as_char, 4);
    f.seekg(block.size, std::ifstream::cur);

    TEST(f)

    f.get();
    f.read(block.as_char, 4);
    uint pos = f.tellg();
    f.read(common.as_char, 8);
    f.seekg(pos + block.size);

    font.lineH = common.data[0];
    font.base  = common.data[1];
    font.texW  = common.data[2];
    font.texH  = common.data[3];

    TEST(f)

    String texFile;

    f.get();
    f.read(block.as_char, 4);
    pos = f.tellg();
    for (char c = f.get(); c; c = f.get())
        texFile.push_back(c);
    f.seekg(pos + block.size);

    font.texture = textureCache->Get(texFile);

    TEST(f)

    f.get();
    f.read(block.as_char, 4);

    Font::Char *c = font.chars;
    int numChars = block.size / 20;

    for (int i = 0; i < numChars; i++)
    {
        f.read(chr.as_char, 20);
        if (chr.id < 256 && chr.as_char[18] == 0)
        {
            c[chr.id].x       = chr.udata[2];
            c[chr.id].y       = chr.udata[3];
            c[chr.id].w       = chr.udata[4];
            c[chr.id].h       = chr.udata[5];
            c[chr.id].xoffs   = chr.sdata[6];
            c[chr.id].yoffs   = chr.sdata[7];
            c[chr.id].advance = chr.sdata[8];
        }

        TEST(f)
    }

    return new Font(font);
}