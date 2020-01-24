#ifndef NAGE_ENGINE_WORLD_WATER_IWATER_H_
#define NAGE_ENGINE_WORLD_WATER_IWATER_H_

#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/model/texture.h"
#include "engine/components/camera/camera.h"

#include <map>

namespace NAGE
{
    class IWater
    {
    public:
        IWater();
        virtual ~IWater();

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
        virtual void render(Camera* _camera) = 0;

    protected:
        Shader* mShader;
        Material* mMaterial;
        Transform* mTransform;
        std::map<std::string, Texture*> mTextures;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_IWATER_H_
