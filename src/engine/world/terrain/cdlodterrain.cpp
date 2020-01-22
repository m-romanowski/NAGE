#include "engine/render/glrenderengine.h"
#include "cdlodterrain.h"
#include <QDebug>

namespace NAGE
{
    CDLODTerrain::CDLODTerrain(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : mLodLevel(_lodLevel),
          mMaxHeight(100.0f),
          mLOD(new CDLOD(_settings)),
          mFrustum(new FrustumCulling(true)),
          mHeightMap(_heightmap)
    {
        // Create terrain chunks.
        int dimension = 2;
        for(int i = 0; i < mLOD->settings().gridMeshesCount; i++)
        {
            mTerrainChunks.insert(std::make_pair(dimension, new CDLODTerrainChunk(dimension)));
            dimension *= 2;
        }

        mLOD->createQuadTree(_heightmap, _lodLevel);
    }

    CDLODTerrain::~CDLODTerrain()
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

    CDLOD* CDLODTerrain::lod()
    {
        return mLOD;
    }

    std::map<int, CDLODTerrainChunk*> CDLODTerrain::chunks() const
    {
        return mTerrainChunks;
    }

    CDLODTerrainChunk* CDLODTerrain::chunk(int _dimension)
    {
        auto pos = mTerrainChunks.find(_dimension);

        if(pos == mTerrainChunks.end())
            throw std::out_of_range("Not found given element");

        return pos->second;
    }

    unsigned int CDLODTerrain::chunkCount() const
    {
        return mTerrainChunks.size();
    }

    float CDLODTerrain::maxHeight() const
    {
        return mMaxHeight;
    }

    HeightMap* CDLODTerrain::heightMap()
    {
        return mHeightMap;
    }

    void CDLODTerrain::setMaxHeight(float _height)
    {
        mMaxHeight = _height;
    }

    void CDLODTerrain::bindTextures()
    {
        GLuint i = 0;

        for(i = 0; i < mTextures.size(); i++)
        {
            if(mTextures[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
            }
        }

        // Heightmap
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mHeightMap->textureId());
    }

    void CDLODTerrain::useHeightMapTexture()
    {
        if(!mShader)
            return;

        mShader->setInt("heightMapTexture", 1);
        mShader->setVec2("heightMapSize", mHeightMap->width(), mHeightMap->height());
        mShader->setFloat("maxHeight", mMaxHeight);
    }

    void CDLODTerrain::render(Camera *_camera)
    {
        if(!mShader)
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
        mShader->use();
        mShader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        mShader->setMat4("view", _camera->view().transpose());
        mShader->setMat4("model", mTransform->model().transpose());
        mShader->setVec3("cameraPosition", _camera->translation());

        // Get chunk mesh by settings dimension (leafNodeSie * gridResolution).
        CDLODTerrainChunk* chunkMesh = chunk(mLOD->settings().dimension());
        mShader->setVec2("cdlod.gridDimension", mLOD->settings().dimension(), mLOD->settings().dimension());
        mShader->setVec2("cdlod.morphValue", mLOD->settings().morphStartValue, mLOD->settings().morphStopValue);

        // Render selected nodes.
        mLOD->createSelectedList(mLodLevel, mFrustum, _camera->translation());
        for(auto& node : mLOD->selectedNodes())
        {
            bool renderFullQuad = node->topLeft() && node->topRight() &&
                node->bottomLeft() && node->bottomRight();

            mShader->setFloat("cdlod.scale", node->dimension());
            mShader->setVec3("cdlod.vecOffset", node->x(), 0.0f, node->z());

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
