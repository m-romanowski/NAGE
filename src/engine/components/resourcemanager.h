#ifndef NAGE_ENGINE_COMPONENTS_RESOURCEMANAGER_H_
#define NAGE_ENGINE_COMPONENTS_RESOURCEMANAGER_H_

#include "engine/render/texture.h"
#include "engine/render/model/model.h"

#include <map>
#include <memory>

namespace NAGE
{
    class ResourceManager
    {
        typedef std::shared_ptr<Texture> texture_ptr;
        typedef std::shared_ptr<Model> model_ptr;

    public:
        ~ResourceManager();

        std::size_t addTexture(texture_ptr _texture);
        GLuint getTexture(const std::size_t _id);
        void removeTexture(const std::size_t _id);
        std::size_t addModel(model_ptr _model);
        model_ptr getModel(const std::size_t _id);
        void removeModel(const std::size_t _id);

    private:
        std::map<std::size_t, texture_ptr> textures_;
        std::map<std::size_t, model_ptr> models_;
    };
}

#endif // NAGE_ENGINE_COMPONENTS_RESOURCEMANAGER_H_
