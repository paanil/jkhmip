
#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"

#include <vector>

/// Base class for all scene nodes.
///
class SceneNode
{
public:
    SceneNode();
    virtual ~SceneNode();

    void SetParent(SceneNode *node);
    SceneNode *GetParent() const;

    void AddChild(SceneNode *node);
    void RemoveChild(SceneNode *node);

    void SetPosition(const Vector3 &pos);
    Vector3 GetPosition() const;

    void SetRotation(const Matrix3 &rot);
    Matrix3 GetRotation() const;

    void GetBasisVectors(Vector3 &right, Vector3 &up, Vector3 &look) const;

    const Matrix4 &GetLocalTransform() const;
    const Matrix4 &GetWorldTransform();
    Matrix4 GetInverseWorldTransform();

private:
    void SetDirty();

private:
    typedef std::vector<SceneNode *> NodeList;

    SceneNode *parent;
    NodeList children;

    Matrix4 localTransform;
    Matrix4 worldTransform;
    bool worldDirty;
};

#endif // __SCENENODE_H__
