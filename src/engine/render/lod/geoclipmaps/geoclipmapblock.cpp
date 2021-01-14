#include "engine/render/vertexhelper.h"
#include "geoclipmapblock.h"

namespace mr::nage
{
    GeoClipMapBlock::GeoClipMapBlock(const unsigned int n, const float _gridSpacing, const Vector2f _gridOffset, const Vector2f _blockPosition,
            const Size<float> _elevationTextureSize)
        : gridSpacing_(_gridSpacing),
          blockPosition_(_blockPosition),
          gridOffset_(_gridOffset)
    {
        create(n);

        // x, y - 1 / (w, h) of elevation texture
        // z, w - origin of block in texture
        fineBlockOrigin_ = Vector4f(1.0f / _elevationTextureSize.width(), 1.0f / _elevationTextureSize.height(),
            _gridOffset.x() / _elevationTextureSize.width(), _gridOffset.y() / _elevationTextureSize.height());
    }

    void GeoClipMapBlock::create(unsigned int _n)
    {
        setupVertices(_n);
        setupIndices(_n);
        VertexHelper::calculateNormals(vertices_, indices_);
        setupBuffer();
    }

    void GeoClipMapBlock::setupVertices(unsigned int _n)
    {
        for(unsigned int z = 0; z < _n; z++)
        {
            for(unsigned int x = 0; x < _n; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }
    }

    void GeoClipMapBlock::setupIndices(unsigned int _n)
    {
        unsigned int index = 0;
        indices_.resize(_n * _n * 6);

        for(unsigned int z = 0; z < _n - 1; z++)
        {
            for(unsigned int x = 0; x < _n - 1; x++)
            {
                unsigned int offset = z * _n + x;

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _n;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _n + 1;
                indices_[index + 5] = offset + _n;

                index += 6;
            }
        }
    }

    void GeoClipMapBlock::drawChunk(Shader* _shader, const Vector2f _levelPosition)
    {
        Vector2f worldPosition = blockPosition_ + _levelPosition;
        Vector4f scaleFactor = Vector4f(gridSpacing_, gridSpacing_, worldPosition.x(), worldPosition.y());

        _shader->use();
        _shader->setVec4("gmapping.scaleFactor", scaleFactor.x(), scaleFactor.y(), scaleFactor.z(), scaleFactor.w());
        _shader->setVec4("gmapping.fineBlockOrigin", fineBlockOrigin_.x(), fineBlockOrigin_.y(), fineBlockOrigin_.z(), fineBlockOrigin_.w());
        _shader->setVec3("inColor", Vector3f(color.red(), color.green(), color.blue()));

        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
