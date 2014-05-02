
#include "Element.h"
#include "../Logger.h"

#include <algorithm>

namespace UI
{

Element::Element() :
    parent(0),
    relativePosition(0.0f, 0.0f),
    absoluteDirty(true)
{
}

Element::~Element()
{
}

void Element::SetParent(Element *elem)
{
    if (parent)
        parent->RemoveChild(this);

    parent = elem;

    if (parent)
        parent->AddChild(this);

    SetDirty();
}

Element *Element::GetParent() const
{
    return parent;
}

void Element::AddChild(Element *elem)
{
    children.push_back(elem);
}

void Element::RemoveChild(Element *elem)
{
    auto it = std::find(children.begin(), children.end(), elem);
    if (it == children.end())
    {
        LOG_WARNING("UI Element: Trying to remove child not in children.");
        return;
    }
    children.erase(it);
}

void Element::SetRelativePosition(const Vector2 &pos)
{
    relativePosition = pos;
    SetDirty();
}

Vector2 Element::GetRelativePosition() const
{
    return relativePosition;
}

Vector2 Element::GetAbsolutePosition()
{
    if (absoluteDirty)
    {
        if (parent)
            absolutePosition = parent->GetAbsolutePosition() + GetRelativePosition();
        else
            absolutePosition = GetRelativePosition();

        absoluteDirty = false;
    }

    return absolutePosition;
}

void Element::SetDirty()
{
    if (!absoluteDirty)
    {
        absoluteDirty = true;
        for (Element *e : children)
        {
            e->SetDirty();
        }
    }
}

void Element::RenderChildren(Shader *shader)
{
    for (Element *e : children)
    {
        e->Render(shader);
    }
}

} // UI
