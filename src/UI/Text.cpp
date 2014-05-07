
#include "Text.h"
#include "../Resource/Font.h"

namespace UI
{

Text::Text() :
    font(0),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

void Text::SetFont(Font *font)
{
    this->font = font;
    UpdateGeometry();
}

Font *Text::GetFont() const
{
    return font;
}

void Text::SetText(const String &text)
{
    this->text = text;
    UpdateGeometry();
}

const String &Text::GetText() const
{
    return text;
}

void Text::SetColor(const Vector4 &color)
{
    this->color = color;
}

Vector4 Text::GetColor() const
{
    return color;
}

const TextGeometry &Text::GetGeometry() const
{
    return geometry;
}

void Text::UpdateGeometry()
{
    if (font)
    {
        font->BuildTextGeometry(text, geometry);
    }
}

} // UI
