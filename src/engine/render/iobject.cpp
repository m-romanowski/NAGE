#include "iobject.h"

namespace NAGE
{
    IObject::IObject()
    {

    }

    IObject::IObject(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
        : mVertices(_vertices),
          mIndices(_indices)
    {

    }

    IObject::~IObject()
    {
        // Clear vertex buffers.
        clearBuffers();

        // Clear vertex data
        mVertices.clear();
        mIndices.clear();
    }

    std::vector<Vertex> IObject::vertices()
    {
        return mVertices;
    }

    std::vector<GLuint> IObject::indices()
    {
        return mIndices;
    }

    void IObject::setVertices(const std::vector<Vertex>& _vertices)
    {
        mVertices = _vertices;
    }

    void IObject::setIndices(const std::vector<GLuint>& _indices)
    {
        mIndices = _indices;
    }

    void IObject::setupBuffer()
    {
        // Create buffers.
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);

        glBindVertexArray(mVAO);

        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        NAGE::nage_glBufferData(GL_ARRAY_BUFFER, mVertices, GL_STATIC_DRAW);

        // Load data (mesh indices) into element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        NAGE::nage_glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices, GL_STATIC_DRAW);

        // Position vector attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, position)));

        // Normal vector attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, normal)));

        // Texture coordinates attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, textureCoords)));

        // Color attribute
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, color)));
    }

    void IObject::clearBuffers()
    {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
    }
}
