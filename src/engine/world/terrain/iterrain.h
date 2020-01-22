#ifndef NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_

#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/model/texture.h"
#include "engine/components/camera/camera.h"

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
        std::vector<Texture*> textures() const;

        // Setters
        void setShader(Shader* _shader);
        void setMaterial(Material* _material);
        void addTexture(Texture* _texture);
        void addTextures(const std::vector<Texture*>& _textures);

        virtual void useMaterial();
        virtual void bindTextures();
        virtual void render(Camera* _camera) = 0;

    protected:
        Shader* mShader;
        Material* mMaterial;
        Transform* mTransform;
        std::vector<Texture*> mTextures;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_ITERRAIN_H_
