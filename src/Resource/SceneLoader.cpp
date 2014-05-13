
#include "SceneLoader.h"
#include "ModelCache.h"
#include "../Scene/Scene.h"
#include "../Logger.h"

#include <fstream>
#include <map>
#include <cassert>

SceneLoader::SceneLoader() :
    modelCache(0)
{
}

void SceneLoader::SetDirectory(const String &dir)
{
    directory = dir;
}

void SceneLoader::SetModelCache(ModelCache &modelCache)
{
    this->modelCache = &modelCache;
}

bool SceneLoader::Load(Scene::Scene &scene, const String &file)
{
    String filePath = directory + file;
    LOG_INFO("Loading scene '%'...", filePath);

    std::ifstream f(filePath.c_str(), std::ifstream::binary);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return false;
    }

    std::map<uint, Scene::Node *> node_by_id;

    const uint node_size = 60;
    const uint name_size = 32;

    struct Node
    {
        uint type;
        uint id;
        uint parent;
        float mat[3][4];
    };

    assert(sizeof(Node) == node_size);

    union
    {
        char as_char[node_size];
        Node as_node;
    };

    char mesh_name[name_size];

    while (f.good())
    {
        f.read(as_char, node_size);

        if (f.eof())
            break;

        Scene::Node *node = 0;

        if (as_node.type == 0)
            node = scene.CreateDummy();
        else if (as_node.type == 1)
        {
            f.read(mesh_name, name_size);
            String model_name(mesh_name);
            Scene::Object *ob = scene.CreateObject();
            ob->SetModel(modelCache->Get(model_name + ".obj"));
            node = ob;
        }
        else if (as_node.type == 2)
        {
            float radius;
            Vector4 color;
            f.read((char *)&radius, sizeof(float));
            f.read((char *)&color.x, sizeof(Vector4));
            Scene::Light *light = scene.CreateLight();
            light->SetRadius(radius);
            light->SetColor(color);
            node = light;
        }
        else
        {
            LOG_ERROR("Invalid node type.");
            return false;
        }

        node_by_id[as_node.id] = node;
        if (as_node.parent)
            node->SetParent(node_by_id[as_node.parent]);

        float (*m)[4] = as_node.mat;
        Matrix3 rot;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                rot.mat[i][j] = m[j][i];
        }
        float scale_x = Vector3(m[0][0], m[1][0], m[2][0]).Length();
        float scale_y = Vector3(m[0][1], m[1][1], m[2][1]).Length();
        float scale_z = Vector3(m[0][2], m[1][2], m[2][2]).Length();
        node->SetPosition(Vector3(m[0][3], m[1][3], m[2][3]));
        node->SetRotation(rot);
        node->SetScale(Vector3(scale_x, scale_y, scale_z));
    }

    return true;
}
