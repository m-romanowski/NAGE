#ifndef NAGE_ENGINE_RENDER_IOBJECT_H_
#define NAGE_ENGINE_RENDER_IOBJECT_H_

#include "vertex.h"
#include "shader.h"
#include "transform.h"
#include "common/macro.h"
#include "texture.h"
#include "engine/components/camera/camera.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/util/objectloader.h"

#include <vector>
#include <string>
#include <cstddef>

namespace mr::nage
{
    class IObject
    {
    protected:
        IObject();
        IObject(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices);
        virtual ~IObject();

    public:
        // Getters
        std::vector<Vertex> vertices();
        std::vector<GLuint> indices();
        unsigned int size() const;

        // Setters
        void setVertices(const std::vector<Vertex>& _vertices);
        void setIndices(const std::vector<GLuint>& _indices);

        virtual void draw() {}

        virtual void draw(Camera* _camera)
        {
            NAGE_UNUSED(_camera);
        }

        virtual void draw(Camera* _camera, Vector4f _clipPlane)
        {
            NAGE_UNUSED(_camera);
            NAGE_UNUSED(_clipPlane);
        }

        virtual void draw(Camera* _camera, Shader* _shader)
        {
            NAGE_UNUSED(_camera);
            NAGE_UNUSED(_shader);
        }

        virtual void draw(Camera* _camera, Shader* _shader, Vector4f _clipPlane)
        {
            NAGE_UNUSED(_camera);
            NAGE_UNUSED(_shader);
            NAGE_UNUSED(_clipPlane);
        }

    protected:
        void setupBuffer();
        void clearBuffers();

        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;

        GLuint VAO_, VBO_, EBO_;
    };
}

#endif // NAGE_ENGINE_RENDER_IOBJECT_H_
