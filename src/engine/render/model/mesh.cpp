#include "engine/render/glrenderengine.h"
#include "mesh.h"

namespace NAGE
{
    Mesh::Mesh()
        : mMaterial(nullptr),
          mTransform(new Transform)
    {

    }

    Mesh::Mesh(const std::string& _path)
        : mMaterial(nullptr),
          mTransform(new Transform)
    {
        loadMesh(_path);
        setupBuffer(); // Create buffers (VAO, VBO).
    }

    Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
        : IObject(_vertices, _indices),
          mMaterial(nullptr),
          mTransform(new Transform)
    {
        setupBuffer(); // Create buffers (VAO, VBO).
    }

    Mesh::~Mesh()
    {
        delete mMaterial;
        delete mTransform;

        // Clear textures.
        for(auto& texture : mTextures)
            delete texture;
    }

    Material* Mesh::material()
    {
        return mMaterial;
    }

    Transform* Mesh::transform()
    {
        return mTransform;
    }

    std::vector<Texture*> Mesh::textures() const
    {
        return mTextures;
    }

    void Mesh::setMaterial(Material* _material)
    {
        mMaterial = _material;
    }

    void Mesh::addTexture(Texture* _texture)
    {
        mTextures.push_back(_texture);
    }

    void Mesh::setTextures(const std::vector<Texture*>& _textures)
    {
        mTextures = _textures;
    }

    void Mesh::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void Mesh::loadMesh(const std::string& _path)
    {
        ObjectLoader loader(_path);

        for(unsigned int i = 0; i < loader.data().position.size(); i++)
        {
            mVertices.push_back(Vertex(loader.data().position[i], loader.data().uv[i],
                loader.data().normal[i]));
        }

        mIndices = loader.data().indices;
    }

    void Mesh::loadMesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
    {
        mVertices = _vertices;
        mIndices = _indices;
    }

    void Mesh::bindTextures()
    {
        for(GLuint i = 0; i < mTextures.size(); i++)
        {
            if(mTextures[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
            }
        }
    }

    void Mesh::unbindTextures()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::draw(Camera* _camera, Shader* _shader, Vector4f _clipPlane)
    {
        if(!_shader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        _shader->use();
        _shader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        _shader->setMat4("view", _camera->view().transpose());
        _shader->setMat4("model", mTransform->model().transpose());

        // Set clip plane (water rendering).
        _shader->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
