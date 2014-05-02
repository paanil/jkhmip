
#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "../Math/Vector2.h"

#include <vector>

class Shader;

namespace UI
{

    class Element
    {
    public:
        Element();
        virtual ~Element();

        void SetParent(Element *elem);
        Element *GetParent() const;

        void AddChild(Element *elem);
        void RemoveChild(Element *elem);

        void SetRelativePosition(const Vector2 &pos);
        Vector2 GetRelativePosition() const;

        Vector2 GetAbsolutePosition();

        virtual void Render(Shader *shader) {}

    private:
        void SetDirty();

        void RenderChildren(Shader *shader);

    private:
        typedef std::vector<Element *> ElementList;

        Element *parent;
        ElementList children;

        Vector2 relativePosition;
        Vector2 absolutePosition;
        bool absoluteDirty;
    };

} // UI

#endif // __ELEMENT_H__
