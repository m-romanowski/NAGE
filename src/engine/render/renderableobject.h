#ifndef NAGE_ENGINE_RENDER_IOBJECT_H_
#define NAGE_ENGINE_RENDER_IOBJECT_H_

#include "vertex.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "common/macro.h"
#include "engine/core/iobject.h"
#include "engine/components/camera/camera.h"
#include "engine/world/light/ilight.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/util/objectloader.h"

#include <vector>
#include <string>
#include <cstddef>

namespace mr::nage
{
    class RenderableObject
        : public IObject
    {
    protected:
        RenderableObject();
        RenderableObject(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices);

    public:
        inline static constexpr const char TYPE[] = "RenderableObject";

        virtual ~RenderableObject();

        // Getters
        std::vector<Vertex> vertices() const;
        std::vector<GLuint> indices() const;
        unsigned int size() const;

        // Setters
        void setVertices(const std::vector<Vertex>& _vertices);
        void setIndices(const std::vector<GLuint>& _indices);

        void applyLights(Camera* _camera, const std::vector<ILight*> _lights);

        virtual Shader* shader() = 0;
        virtual Transform* transformation() = 0;
        virtual void useMaterials() = 0;
        virtual void bindTextures() = 0;
        virtual void unbindTextures() = 0;

        virtual void draw(Camera* _camera, const Vector4f _clipPlane);
        virtual bool isLightSource() const;
        virtual bool isWaterSource() const;
        virtual int depth() const;
        virtual std::string type() const override;
        bool isTransformable();

    protected:
        void setupBuffer();
        void clearBuffers();

        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;
        GLuint VAO_, VBO_, EBO_;
    };
}

#endif // NAGE_ENGINE_RENDER_IOBJECT_H_
