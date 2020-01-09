#include "engine/render/glrenderengine.h"
#include "model.h"

namespace NAGE
{
    Model::Model()
        : mTransform(new Transform),
          mShader(nullptr)
    {

    }

    Model::Model(Primitive& _primitive)
    {
        mShader = _primitive.shader();
        mTransform = _primitive.transform();

        addMesh(_primitive.vertices(), _primitive.indices());
    }

    Model::~Model()
    {
        delete mTransform;
        delete mShader;

        // Clear meshes.
        for(auto& mesh : mMeshes)
            delete mesh;
    }

    std::vector<Mesh*> Model::meshes() const
    {
        return mMeshes;
    }

    Transform* Model::transformation()
    {
        return mTransform;
    }

    Shader* Model::shader()
    {
        return mShader;
    }

    void Model::addMesh(Mesh* _mesh)
    {
        mMeshes.push_back(_mesh);
    }

    void Model::addMesh(const std::string &_path)
    {
        mMeshes.push_back(new Mesh(_path));
    }

    void Model::addMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
    {
        mMeshes.push_back(new Mesh(_vertices, _indices));
    }

    void Model::setMeshes(const std::vector<Mesh*>& _meshes)
    {
        mMeshes = _meshes;
    }

    void Model::setTransformation(Transform* _transform)
    {
        mTransform = _transform;

        for(auto& mesh : mMeshes)
        {
            if(mesh)
                mesh->setTransformation(_transform);
        }
    }

    void Model::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void Model::loadModel(const std::string& _path)
    {

    }

    void Model::useMaterials()
    {
        if(mShader == nullptr)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        for(auto& mesh : mMeshes)
        {
            if(mesh->material())
                mesh->material()->use(mShader);
        }
    }

    void Model::bindTextures()
    {
        for(auto& mesh : mMeshes)
        {
            if(mesh)
                mesh->bindTextures();
        }
    }

    void Model::draw(Camera* _camera)
    {
        if(!mShader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Draw model meshes.
        for(auto& mesh : mMeshes)
            mesh->draw(_camera, mShader);
    }
}
