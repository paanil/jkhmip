
#include "SceneLoader.h"
#include "ModelCache.h"
#include "../Scene/Scene.h"
#include "../Logic/Logic.h"
#include "../Logic/Rotator.h"
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

bool SceneLoader::Load(Scene::Scene &scene, Logic &logic, const String &file)
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

    struct Node
    {
        uint type;
        uint id;
        uint parent;
        float mat[3][4];
    };

    const uint node_size = 60;
    assert(sizeof(Node) == node_size);

    struct Object
    {
        uint cast_shadows;
        char mesh_name[32];
    };

    const uint object_size = 36;
    assert(sizeof(Object) == object_size);

    struct Light
    {
        uint type;
        float radius;
        float cutoff;
        float color[3];
        float energy;
    };

    const uint light_size = 28;
    assert(sizeof(Light) == light_size);

    union
    {
        char as_char[4];
        uint count;
    };

    f.read(as_char, 4);

    for (uint i = 0; i < count; i++)
    {
        union
        {
            char as_char[node_size];
            Node as_node;
        };

        Scene::Node *node = 0;
        f.read(as_char, node_size);

        if (as_node.type == 0) // DUMMY
        {
            node = scene.CreateDummy();
        }
        else if (as_node.type == 1 || as_node.type == 3) // OBJECT or SKY
        {
            union
            {
                char as_char[object_size];
                Object as_object;
            };

            Scene::Object *ob = 0;
            f.read(as_char, object_size);

            if (as_node.type == 1)
                ob = scene.CreateObject();
            else
                ob = scene.CreateSky();

            ob->SetCastShadows(as_object.cast_shadows);
            ob->SetModel(modelCache->Get(String(as_object.mesh_name) + ".obj"));

            node = ob;
        }
        else if (as_node.type == 2) // LIGHT
        {
            union
            {
                char as_char[light_size];
                Light as_light;
            };

            Scene::Light *light = 0;
            f.read(as_char, light_size);

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

        float (*m)[4] = as_node.mat;

        float scale_x = Vector3(m[0][0], m[1][0], m[2][0]).Length();
        float scale_y = Vector3(m[0][1], m[1][1], m[2][1]).Length();
        float scale_z = Vector3(m[0][2], m[1][2], m[2][2]).Length();

        Matrix3 rot;
        for (int i = 0; i < 3; i++)
        {
            rot.mat[0][i] = m[i][0] / scale_x;
            rot.mat[1][i] = m[i][1] / scale_y;
            rot.mat[2][i] = m[i][2] / scale_z;
        }

        node->SetPosition(Vector3(m[0][3], m[1][3], m[2][3]));
        node->SetRotation(rot);
        node->SetScale(Vector3(scale_x, scale_y, scale_z));
    }

    struct Prop
    {
        uint node;
        uint type;
        float value;
    };

    const uint prop_size = 12;
    assert(sizeof(Prop) == prop_size);

    f.read(as_char, 4);

    for (uint i = 0; i < count; i++)
    {
        union
        {
            char as_char[prop_size];
            Prop prop;
        };

        f.read(as_char, prop_size);

        Scene::Node *node = node_by_id[prop.node];

        if (prop.type == 0)
        {
            Rotator *rot = logic.CreateRotator();
            rot->SetNode(node);
            rot->SetAxis(Vector3(1.0f, 0.0f, 0.0f));
            rot->SetAngularVelocity(prop.value);
        }
        else if (prop.type == 1)
        {
            Rotator *rot = logic.CreateRotator();
            rot->SetNode(node);
            rot->SetAxis(Vector3(0.0f, 1.0f, 0.0f));
            rot->SetAngularVelocity(prop.value);
        }
        else if (prop.type == 2)
        {
            Rotator *rot = logic.CreateRotator();
            rot->SetNode(node);
            rot->SetAxis(Vector3(0.0f, 0.0f, 1.0f));
            rot->SetAngularVelocity(prop.value);
        }
    }

    f.close();

    return true;
}
