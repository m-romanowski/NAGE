#include "engine/render/glrenderengine.h"
#include "mesh.h"

namespace NAGE
{
    Mesh::Mesh()
        : material_(nullptr),
          transform_(new Transform)
    {

    }

    Mesh::Mesh(const std::string& _path)
        : material_(nullptr),
          transform_(new Transform)
    {
        loadMesh(_path);
        setupBuffer(); // Create buffers (VAO, VBO).
    }

    Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
        : IObject(_vertices, _indices),
          material_(nullptr),
          transform_(new Transform)
    {
        setupBuffer(); // Create buffers (VAO, VBO).
    }

    Mesh::~Mesh()
    {
        delete material_;
        delete transform_;

        // Clear textures.
        for(auto& texture : textures_)
            delete texture;
    }

    Material* Mesh::material()
    {
        return material_;
    }

    Transform* Mesh::transform()
    {
        return transform_;
    }

    std::vector<Texture*> Mesh::textures() const
    {
        return textures_;
    }

    void Mesh::setMaterial(Material* _material)
    {
        material_ = _material;
    }

    void Mesh::addTexture(Texture* _texture)
    {
        textures_.push_back(_texture);
    }

    void Mesh::setTextures(const std::vector<Texture*>& _textures)
    {
        textures_ = _textures;
    }

    void Mesh::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void Mesh::loadMesh(const std::string& _path)
    {
        ObjectLoader loader(_path);

        for(unsigned int i = 0; i < loader.data().position_.size(); i++)
        {
            vertices_.push_back(Vertex(loader.data().position_[i], loader.data().uv_[i],
                loader.data().normal_[i]));
        }

        indices_ = loader.data().indices_;
    }

    void Mesh::loadMesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices)
    {
        vertices_ = _vertices;
        indices_ = _indices;
    }

    void Mesh::bindTextures()
    {
        for(GLuint i = 0; i < textures_.size(); i++)
        {
            if(textures_[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, textures_[i]->id());
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
        _shader->setMat4("model", transform_->model().transpose());

        // Set clip plane (water rendering).
        _shader->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
