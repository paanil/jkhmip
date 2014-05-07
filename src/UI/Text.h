
#ifndef __TEXT_H__
#define __TEXT_H__

#include "Element.h"
#include "../Render/TextGeometry.h"
#include "../Math/Vector4.h"
#include "../Types.h"

class Font;

namespace UI
{

    class Text : public Element
    {
    public:
        Text();

        void SetFont(Font *font);
        Font *GetFont() const;

        void SetText(const String &text);
        const String &GetText() const;

        void SetColor(const Vector4 &color);
        Vector4 GetColor() const;

        const TextGeometry &GetGeometry() const;

    private:
        void UpdateGeometry();

    private:
        Font *font;
        String text;
        Vector4 color;
        TextGeometry geometry;
    };

} // UI

#endif // __TEXT_H__
