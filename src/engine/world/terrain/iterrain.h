#ifndef NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_

#include "engine/render/renderableobject.h"
#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/texture.h"
#include "engine/components/camera/camera.h"

#include <map>

namespace mr::nage
{
    class ITerrain
        : public RenderableObject
    {
    public:
        ITerrain(const std::string& _id);
        virtual ~ITerrain();

        // Getters
        Material* material();
        // unsigned int texturesCount() const;
        // Texture* textureByKey(const std::string& _key);
        // std::map<std::string, Texture*> textures() const;
        Shader* shader() override;
        Transform* transformation() override;
        Resource* resource() override;

        // Setters
        void setShader(Shader* _shader);
        void setMaterial(Material* _material);
        void setTransformation(Transform* _transform);
        void addTexture(const std::string& _shaderUniformName, Texture* _texture);
        // void addTextures(const std::map<std::string, Texture*>& _textures);

        std::string id() const override;
        virtual void useMaterials() override;
        virtual void bindTextures() override;
        virtual void unbindTextures() override;

    protected:
        std::string id_;
        Material* material_;
        Transform* transform_;
        Resource* resource_;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
