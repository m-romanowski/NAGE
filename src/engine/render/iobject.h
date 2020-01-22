#ifndef NAGE_ENGINE_RENDER_IOBJECT_H_
#define NAGE_ENGINE_RENDER_IOBJECT_H_

#include "vertex.h"
#include "shader.h"
#include "transform.h"
#include "common/macro.h"
#include "model/texture.h"
#include "engine/components/camera/camera.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/util/objectloader.h"

#include <vector>
#include <string>
#include <cstddef>

namespace NAGE
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
        virtual void draw(Camera* _camera) { NAGE_UNUSED(_camera); }
        virtual void draw(Camera* _camera, Shader* _shader) { NAGE_UNUSED(_camera); NAGE_UNUSED(_shader); }

    protected:
        void setupBuffer();
        void clearBuffers();

        std::vector<Vertex> mVertices;
        std::vector<GLuint> mIndices;

        GLuint mVAO, mVBO, mEBO;
    };
}

#endif // NAGE_ENGINE_RENDER_IOBJECT_H_
