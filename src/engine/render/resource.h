#ifndef NAGE_ENGINE_RENDER_RESOURCE_H_
#define NAGE_ENGINE_RENDER_RESOURCE_H_

#include <memory>
#include <map>

#include "texture.h"
#include "shader.h"

namespace mr::nage
{
    class Resource
    {
        // TODO: change to c++11 smart pointers (whole project migration process)
        typedef Shader* shader_ptr_t;
        typedef Texture* texture_ptr_t;

    public:
        explicit Resource(const std::string _sourceId);

        shader_ptr_t shader() const;
        std::vector<texture_ptr_t> textures() const;

        void setShader(shader_ptr_t _shader);
        void mapTexture(const std::string _materialName, texture_ptr_t _texture);

    private:
        const std::string sourceId_;
        shader_ptr_t shader_;
        std::map<std::string, texture_ptr_t> textures_;
    };
}

#endif // NAGE_ENGINE_RENDER_RESOURCE_H_
