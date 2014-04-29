
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Shader;
class Texture;

class Material
{
public:
    Material();

    void SetShader(Shader *shader);
    Shader *GetShader();

    void SetTexture(Texture *texture);
    Texture *GetTexture();

private:
    Shader *shader;
    Texture *texture;
};

#endif // __MATERIAL_H__
