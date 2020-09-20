#include "engine/render/glrenderengine.h"
#include "icdlodobject.h"

namespace NAGE
{
    ICDLODObject::ICDLODObject(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : lodLevel_(_lodLevel),
          maxHeight_(150.0f),
          lod_(new CDLOD(_settings)),
          frustum_(new FrustumCulling(true)),
          heightMap_(_heightmap)
    {
        // Create terrain chunks.
        int dimension = 2;
        for(int i = 0; i < lod_->settings().gridMeshesCount_; i++)
        {
            chunks_.insert(std::make_pair(dimension, new CDLODObjectChunk(dimension)));
            dimension *= 2;
        }

        lod_->createQuadTree(_heightmap, _lodLevel);
    }

    ICDLODObject::~ICDLODObject()
    {
        // Clear all terrain chunks.
        for (auto it = chunks_.begin(); it != chunks_.end();)
        {
            delete it->second;
            it = chunks_.erase(it);
        }

        delete frustum_;
        delete lod_;
    }

    CDLOD* ICDLODObject::lod()
    {
        return lod_;
    }

    std::map<int, CDLODObjectChunk*> ICDLODObject::chunks() const
    {
        return chunks_;
    }

    CDLODObjectChunk* ICDLODObject::chunk(int _dimension)
    {
        auto pos = chunks_.find(_dimension);

        if(pos == chunks_.end())
            throw std::out_of_range("Not found given element");

        return pos->second;
    }

    unsigned int ICDLODObject::chunkCount() const
    {
        return chunks_.size();
    }

    float ICDLODObject::maxHeight() const
    {
        return maxHeight_;
    }

    HeightMap* ICDLODObject::heightMap()
    {
        return heightMap_;
    }

    void ICDLODObject::setMaxHeight(float _height)
    {
        maxHeight_ = _height;
    }

    void ICDLODObject::setHeightMapProperties(Shader* _shader)
    {
        if(!_shader)
            return;

        _shader->use();
        _shader->setVec2("heightMapSize", heightMap_->width(), heightMap_->height());
        _shader->setFloat("maxHeight", maxHeight_);
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
        Matrix4f vp = _camera->view().transpose() * GLRenderEngine::projection().perspective().transpose();
        frustum_->update(vp);

        // We need transpose matrix for OpenGL (matrix column major).
        _shader->use();
        _shader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        _shader->setMat4("view", _camera->view().transpose());
        _shader->setMat4("model", _transform->model().transpose());
        _shader->setVec3("cameraPosition", _camera->translation());
        _shader->setInt("heightMapTexture", 0);

        // Get chunk mesh by settings dimension (leafNodeSie * gridResolution).
        CDLODObjectChunk* chunkMesh = chunk(lod_->settings().dimension());
        _shader->setVec2("cdlod.gridDimension", lod_->settings().dimension(), lod_->settings().dimension());
        _shader->setVec2("cdlod.morphValue", lod_->settings().morphStartValue_, lod_->settings().morphEndValue_);

        // Render selected nodes.
        lod_->createSelectedList(lodLevel_, frustum_, _camera->translation());
        for(auto& node : lod_->selectedNodes())
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

        lod_->clearSelectedNodes();
    }
}
