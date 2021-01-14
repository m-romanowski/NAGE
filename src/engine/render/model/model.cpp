#include "engine/render/glrenderengine.h"
#include "model.h"

namespace mr::nage
{
    Model::Model(const std::string& _id)
        : id_(_id),
          transform_(new Transform),
          shader_(nullptr)
    {

    }

    Model::Model(Primitive& _primitive)
        : id_(_primitive.id())
    {
        shader_ = _primitive.shader();
        transform_ = _primitive.transformation();

        addMesh(_primitive.vertices(), _primitive.indices());
    }

    Model::~Model()
    {
        delete transform_;
        delete shader_;

        // Clear meshes.
        for(auto& mesh : meshes_)
        {
            if(mesh->isChild(this))
                delete mesh;
        }
    }

    std::string Model::id() const
    {
        return id_;
    }

    std::vector<Mesh*> Model::meshes() const
    {
        return meshes_;
    }

    Transform* Model::transformation()
    {
        return transform_;
    }

    Shader* Model::shader()
    {
        return shader_;
    }

    void Model::addMesh(Mesh* _mesh)
    {
        _mesh->setParent(this);
        meshes_.push_back(_mesh);
    }

    void Model::addMesh(const std::string &_path)
    {
        meshes_.push_back(new Mesh(_path, this));
    }

    void Model::addMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
    {
        meshes_.push_back(new Mesh(id().append("-mesh-").append(std::to_string(meshes_.size())), _vertices, _indices, this));
    }

    void Model::setMeshes(const std::vector<Mesh*>& _meshes)
    {
        meshes_ = _meshes;
    }

    void Model::setTransformation(Transform* _transform)
    {
        transform_ = _transform;

        for(auto& mesh : meshes_)
        {
            if(mesh)
                mesh->setTransformation(_transform);
        }
    }

    void Model::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void Model::loadModel(const std::string& _path)
    {
        NAGE_UNUSED(_path);
        // TODO: load mesh from the file.
    }

    void Model::useMaterials()
    {
        if(shader_ == nullptr)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        for(auto& mesh : meshes_)
        {
            if(mesh->material())
                mesh->material()->use(shader_);
        }
    }

    void Model::bindTextures()
    {
        for(auto& mesh : meshes_)
        {
            if(mesh)
                mesh->bindTextures();
        }
    }

    void Model::unbindTextures()
    {
        for(auto& mesh : meshes_)
        {
            if(mesh)
                mesh->unbindTextures();
        }
    }

    void Model::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Draw model meshes.
        for(auto& mesh : meshes_)
            mesh->draw(_camera, _clipPlane);
    }
}
