#include "engine/render/glrenderengine.h"
#include "icdlodobject.h"

namespace NAGE
{
    ICDLODObject::ICDLODObject(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : mLodLevel(_lodLevel),
          mMaxHeight(150.0f),
          mLOD(new CDLOD(_settings)),
          mFrustum(new FrustumCulling(true)),
          mHeightMap(_heightmap)
    {
        // Create terrain chunks.
        int dimension = 2;
        for(int i = 0; i < mLOD->settings().gridMeshesCount; i++)
        {
            mTerrainChunks.insert(std::make_pair(dimension, new CDLODObjectChunk(dimension)));
            dimension *= 2;
        }

        mLOD->createQuadTree(_heightmap, _lodLevel);
    }

    ICDLODObject::~ICDLODObject()
    {
        // Clear all terrain chunks.
        for (auto it = mTerrainChunks.begin(); it != mTerrainChunks.end();)
        {
            delete it->second;
            it = mTerrainChunks.erase(it);
        }

        delete mFrustum;
        delete mLOD;
    }

    CDLOD* ICDLODObject::lod()
    {
        return mLOD;
    }

    std::map<int, CDLODObjectChunk*> ICDLODObject::chunks() const
    {
        return mTerrainChunks;
    }

    CDLODObjectChunk* ICDLODObject::chunk(int _dimension)
    {
        auto pos = mTerrainChunks.find(_dimension);

        if(pos == mTerrainChunks.end())
            throw std::out_of_range("Not found given element");

        return pos->second;
    }

    unsigned int ICDLODObject::chunkCount() const
    {
        return mTerrainChunks.size();
    }

    float ICDLODObject::maxHeight() const
    {
        return mMaxHeight;
    }

    HeightMap* ICDLODObject::heightMap()
    {
        return mHeightMap;
    }

    void ICDLODObject::setMaxHeight(float _height)
    {
        mMaxHeight = _height;
    }

    void ICDLODObject::useHeightMapTexture(Shader* _shader)
    {
        if(!_shader)
            return;

        _shader->use();
        _shader->setInt("heightMapTexture", 0);
        _shader->setVec2("heightMapSize", mHeightMap->width(), mHeightMap->height());
        _shader->setFloat("maxHeight", mMaxHeight);
    }

    void ICDLODObject::renderCDLOD(Camera *_camera, Shader* _shader, Transform* _transform)
    {
        if(!_shader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Frustum culling (transpose matrix -> see below).
        Matrix4f vp = _camera->view().transpose() *
            GLRenderEngine::projection().perspective().transpose();
        mFrustum->update(vp);

        // We need transpose matrix for OpenGL (matrix column major).
        _shader->use();
        _shader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        _shader->setMat4("view", _camera->view().transpose());
        _shader->setMat4("model", _transform->model().transpose());
        _shader->setVec3("cameraPosition", _camera->translation());

        // Get chunk mesh by settings dimension (leafNodeSie * gridResolution).
        CDLODObjectChunk* chunkMesh = chunk(mLOD->settings().dimension());
        _shader->setVec2("cdlod.gridDimension", mLOD->settings().dimension(), mLOD->settings().dimension());
        _shader->setVec2("cdlod.morphValue", mLOD->settings().morphStartValue, mLOD->settings().morphEndValue);

        // Heightmap
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mHeightMap->textureId());

        // Render selected nodes.
        mLOD->createSelectedList(mLodLevel, mFrustum, _camera->translation());
        for(auto& node : mLOD->selectedNodes())
        {
            bool renderFullQuad = node->topLeft() && node->topRight() &&
                node->bottomLeft() && node->bottomRight();

            _shader->setFloat("cdlod.scale", node->dimension());
            _shader->setVec3("cdlod.vecOffset", node->x(), 0.0f, node->z());

            // Draw full grid mesh
            if(renderFullQuad)
            {
                chunkMesh->drawChunk(chunkMesh->indices().size(), 0);
            }
            // Draw some quads of mesh.
            else
            {
                chunkMesh->drawChunk(chunkMesh->indices().size(), 0);
            }
        }

        mLOD->clearSelectedNodes();
    }
}
