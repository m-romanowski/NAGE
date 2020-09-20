#include "iobject.h"

namespace NAGE
{
    IObject::IObject()
    {

    }

    IObject::IObject(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
        : vertices_(_vertices),
          indices_(_indices)
    {

    }

    IObject::~IObject()
    {
        // Clear vertex buffers.
        clearBuffers();
    }

    std::vector<Vertex> IObject::vertices()
    {
        return vertices_;
    }

    std::vector<GLuint> IObject::indices()
    {
        return indices_;
    }

    unsigned int IObject::size() const
    {
        return indices_.size();
    }

    void IObject::setVertices(const std::vector<Vertex>& _vertices)
    {
        vertices_ = _vertices;
    }

    void IObject::setIndices(const std::vector<GLuint>& _indices)
    {
        indices_ = _indices;
    }

    void IObject::setupBuffer()
    {
        // Create buffers.
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);
        glGenBuffers(1, &EBO_);

        glBindVertexArray(VAO_);

        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        NAGE::nage_glBufferData(GL_ARRAY_BUFFER, vertices_, GL_STATIC_DRAW);

        // Load data (mesh indices) into element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
        NAGE::nage_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_, GL_STATIC_DRAW);

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

    void IObject::clearBuffers()
    {
        // Clear vertex data
        vertices_.clear();
        indices_.clear();

        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);
        glDeleteBuffers(1, &EBO_);
    }
}
