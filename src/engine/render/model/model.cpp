#include "engine/render/glrenderengine.h"
#include "model.h"

namespace mr::nage
{
    Model::Model()
        : transform_(new Transform),
          shader_(nullptr)
    {

    }

    Model::Model(Primitive& _primitive)
    {
        shader_ = _primitive.shader();
        transform_ = _primitive.transform();

        addMesh(_primitive.vertices(), _primitive.indices());
    }

    Model::~Model()
    {
        delete transform_;
        delete shader_;

        // Clear meshes.
        for(auto& mesh : meshes_)
            delete mesh;
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
        meshes_.push_back(_mesh);
    }

    void Model::addMesh(const std::string &_path)
    {
        meshes_.push_back(new Mesh(_path));
    }

    void Model::addMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
    {
        meshes_.push_back(new Mesh(_vertices, _indices));
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

    void Model::draw(Camera* _camera, Vector4f _clipPlane)
    {
        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Draw model meshes.
        for(auto& mesh : meshes_)
            mesh->draw(_camera, shader_, _clipPlane);
    }
}
