#include "engine/render/glrenderengine.h"
#include "model.h"
#include "mesh.h"

namespace mr::nage
{
    Mesh::Mesh(const std::string& _id, Model* _parent)
        : id_(_id),
          material_(nullptr),
          transform_(new Transform),
          parent_(_parent)
    {

    }

    Mesh::Mesh(const std::string& _id, const std::string& _path, Model* _parent)
        : id_(_id),
          material_(nullptr),
          transform_(new Transform),
          parent_(_parent)
    {
        loadMesh(_path);
        setupBuffer(); // Create buffers (VAO, VBO).
    }

    Mesh::Mesh(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices, Model* _parent)
        : RenderableObject(_vertices, _indices),
          id_(_id),
          material_(nullptr),
          transform_(new Transform),
          parent_(_parent)
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

    std::string Mesh::id() const
    {
        return id_;
    }

    Material* Mesh::material()
    {
        return material_;
    }

    Transform* Mesh::transformation()
    {
        return transform_;
    }

    std::vector<Texture*> Mesh::textures() const
    {
        return textures_;
    }

    bool Mesh::isChild(Model* _model)
    {
        return parent_ == _model;
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

    void Mesh::setParent(Model* _parent)
    {
        parent_ = _parent;
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

    void Mesh::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        Shader* shaderPtr = parent_->shader();
        if(!shaderPtr)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        shaderPtr->use();
        shaderPtr->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        shaderPtr->setMat4("view", _camera->view().transpose());
        shaderPtr->setMat4("model", transform_->model().transpose());

        // Set clip plane (water rendering).
        shaderPtr->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
