
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

bool SceneLoader::LoadScene(Scene &scene, const String &file)
{
    String filePath = directory + file;
    LOG_INFO("Loading scene '%'...", filePath);

    std::ifstream f(filePath.c_str(), std::ifstream::binary);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return false;
    }

    std::map<uint, SceneNode *> node_by_id;

    struct Node
    {
        uint type;
        uint id;
        uint parent;
        uint padd;
        float mat[4][4];
    };

    assert(sizeof(Node) == 80);

    union
    {
        char as_char[80];
        Node as_node;
    };

    char mesh_name[32];

    while (f.good())
    {
        f.read(as_char, 80);

        SceneNode *node = 0;

        if (as_node.type == 0)
            node = scene.CreateDummy();
        else if (as_node.type == 1)
        {
            f.read(mesh_name, 32);
            String model_name(mesh_name);
            SceneObject *ob = scene.CreateObject();
            ob->SetModel(modelCache->Get(model_name + ".obj"));
            node = ob;
        }

        node_by_id[as_node.id] = node;
        if (as_node.parent)
            node->SetParent(node_by_id[as_node.parent]);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                node->localTransform.mat[i][j] = as_node.mat[j][i];
        }

        node->worldDirty = true;
    }

    return true;
}
