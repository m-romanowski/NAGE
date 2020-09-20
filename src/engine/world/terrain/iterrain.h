#ifndef NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_

#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/texture.h"
#include "engine/components/camera/camera.h"

#include <map>

namespace NAGE
{
    class ITerrain
    {
    public:
        ITerrain();
        virtual ~ITerrain();

        // Getters
        Shader* shader();
        Material* material();
        Transform* transform();
        unsigned int texturesCount() const;
        Texture* textureByKey(const std::string& _key);
        std::map<std::string, Texture*> textures() const;

        // Setters
        void setShader(Shader* _shader);
        void setMaterial(Material* _material);
        void setTransformation(Transform* _transform);
        void addTexture(const std::string& _shaderUniformName, Texture* _texture);
        void addTextures(const std::map<std::string, Texture*>& _textures);

        virtual void useMaterial();
        virtual void bindTextures();
        virtual void unbindTextures();
        virtual void render(Camera* _camera, Vector4f _clipPlane) = 0;

    protected:
        Shader* shader_;
        Material* material_;
        Transform* transform_;
        std::map<std::string, Texture*> textures_;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
