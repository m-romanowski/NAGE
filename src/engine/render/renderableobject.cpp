#include "renderableobject.h"

namespace mr::nage
{
    RenderableObject::RenderableObject()
    {

    }

    RenderableObject::RenderableObject(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
        : vertices_(_vertices),
          indices_(_indices)
    {

    }

    RenderableObject::~RenderableObject()
    {
        // Clear vertex buffers.
        clearBuffers();
    }

    std::vector<Vertex> RenderableObject::vertices() const
    {
        return vertices_;
    }

    std::vector<GLuint> RenderableObject::indices() const
    {
        return indices_;
    }

    unsigned int RenderableObject::size() const
    {
        return indices_.size();
    }

    void RenderableObject::setVertices(const std::vector<Vertex>& _vertices)
    {
        vertices_ = _vertices;
    }

    void RenderableObject::setIndices(const std::vector<GLuint>& _indices)
    {
        indices_ = _indices;
    }

    void RenderableObject::setupBuffer()
    {
        // Create buffers.
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);
        glGenBuffers(1, &EBO_);

        glBindVertexArray(VAO_);

        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        mr::nage::nage_glBufferData(GL_ARRAY_BUFFER, vertices_, GL_STATIC_DRAW);

        // Load data (mesh indices) into element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
        mr::nage::nage_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_, GL_STATIC_DRAW);

        // Position vector attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, position_)));

        // Normal vector attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, normal_)));

        // Texture coordinates attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, textureCoords_)));

        // Color attribute
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, color_)));
    }

    void RenderableObject::clearBuffers()
    {
        // Clear vertex data
        vertices_.clear();
        indices_.clear();

        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);
        glDeleteBuffers(1, &EBO_);
    }

    void RenderableObject::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_camera);
        NAGE_UNUSED(_clipPlane);
    }

    bool RenderableObject::isLightSource() const
    {
        return false;
    }

    int RenderableObject::depth() const
    {
        return 0;
    }

    bool RenderableObject::isTransformable()
    {
        return transformation() != nullptr;
    }

    bool RenderableObject::isWaterSource() const
    {
        return false;
    }

    std::string RenderableObject::type() const
    {
        return TYPE;
    }

    void RenderableObject::applyLights(Camera* _camera, const std::vector<ILight*> _lights)
    {
        for(auto light : _lights)
            light->use(_camera, shader());
    }
}
