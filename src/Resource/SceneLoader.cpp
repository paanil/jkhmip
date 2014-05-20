
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

        if (as_node.type == 0) // DUMMY
        {
            node = scene.CreateDummy();
        }
        else if (as_node.type == 1) // OBJECT
        {
            f.read(mesh_name, name_size);

            Scene::Object *ob = scene.CreateObject();
            ob->SetModel(modelCache->Get(String(mesh_name) + ".obj"));

            node = ob;
        }
        else if (as_node.type == 2) // LIGHT
        {
            const uint light_size = 28;

            struct Light
            {
                uint type;
                float radius;
                float cutoff;
                float color[3];
                float energy;
            };

            assert(sizeof(Light) == light_size);

            union
            {
                char as_char[light_size];
                Light as_light;
            };

            f.read(as_char, light_size);

            Scene::Light *light = 0;

            if (as_light.type == 0) // DIRECTIONAL
                light = scene.CreateDirLight();
            else if (as_light.type == 1) // SPOT
                light = scene.CreateSpotLight();
            else if (as_light.type == 2) // POINT
                light = scene.CreatePointLight();
            else
            {
                LOG_ERROR("Invalid light type.");
                return false;
            }

            light->SetRadius(as_light.radius);
            light->SetCutoff(as_light.cutoff);
            light->SetColor(Vector3(as_light.color[0], as_light.color[1], as_light.color[2]));
            light->SetEnergy(as_light.energy);

            node = light;

            float m[3][3];
            for (int i = 0; i < 3; i++)
            {
                m[i][0] =  as_node.mat[i][0];
                m[i][1] =  as_node.mat[i][2];
                m[i][2] = -as_node.mat[i][1];
            }

            for (int i = 0; i < 3; i++)
            {
                as_node.mat[i][0] = m[i][0];
                as_node.mat[i][1] = m[i][1];
                as_node.mat[i][2] = m[i][2];
            }
        }
        else
        {
            LOG_ERROR("Invalid node type.");
            return false;
        }

        node_by_id[as_node.id] = node;
        if (as_node.parent)
            node->SetParent(node_by_id[as_node.parent]);

        Matrix3 rot;
        float (*m)[4] = as_node.mat;
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

    f.close();

    return true;
}
