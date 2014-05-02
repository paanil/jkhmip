
#include "Text.h"
#include "../Render/Shader.h"
#include "../Render/TextGeometry.h"
#include "../Resource/Font.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

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

void Text::Render(Shader *shader)
{
    Vector2 pos = GetAbsolutePosition();
    shader->SetTranslation(Vector3(pos.x, pos.y, 0.0f));
    shader->SetColor(color);
    geometry.Render();
}

void Text::UpdateGeometry()
{
    if (font)
    {
        font->BuildTextGeometry(text, geometry);
    }
}

} // UI
