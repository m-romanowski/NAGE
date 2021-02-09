#include "geoclipmaplevel.h"

namespace mr::nage
{
    GeoClipMapLevel::GeoClipMapLevel(unsigned int _gridSize, unsigned int _gridSpacing, HeightMap* _heightMap, const float _maxHeight)
        : gridSize_(_gridSize),
          gridSpacing_(std::pow(2, _gridSpacing)), // 2 ^ n
          heightMap_(_heightMap),
          maxHeight_(_maxHeight)
    {

    }

    GeoClipMapLevel::~GeoClipMapLevel()
    {
        for(auto block : blocks_)
            delete block;

        blocks_.clear();

        for(auto block : centerBlocks_)
            delete block;

        centerBlocks_.clear();

        delete ringFixUp_;

        for(auto trim : interiorTrim_)
            delete trim;

        interiorTrim_.clear();

        delete degenerateTriangle_;
    }

    void GeoClipMapLevel::create(GeoClipMapLevel* _parentLevel, GeoClipMapLevel* _childLevel)
    {
        this->parentLevel_ = _parentLevel;
        this->childLevel_ = _childLevel;

        setupBlocks();
        setupRingFixUp();
        setupInteriorTrim();
        setupDegenerateTriangle();
    }

    void GeoClipMapLevel::setupBlocks()
    {
        unsigned int blockSize = (gridSize_ + 1) / 4;

        // TODO: Block positions
        createBlock(Vector2f(0.0f, 0.0f)); // 1
        createBlock(Vector2f(0.0f, (blockSize - 1.0f))); // 2
        createBlock(Vector2f(0.0f, (((blockSize - 1.0f) * 2.0f) + 2.0f))); // 3
        createBlock(Vector2f(0.0f, (((blockSize - 1.0f) * 3.0f) + 2.0f)));
        createBlock(Vector2f((blockSize - 1.0f), 0.0f)); // 4
        createBlock(Vector2f((blockSize - 1.0f), ((blockSize - 1.0f) * 3.0f) + 2.0f)); // 5
        createBlock(Vector2f(((blockSize - 1.0f) * 2.0f) + 2.0f, 0.0f)); // 6
        createBlock(Vector2f((((blockSize - 1.0f) * 2.0f) + 2.0f), ((blockSize - 1.0f) * 3.0f) + 2.0f)); // 7
        createBlock(Vector2f((((blockSize - 1.0f) * 2.0f) + 2.0f), ((blockSize - 1.0f) * 3.0f) + 2.0f)); // 8
        createBlock(Vector2f((((blockSize - 1.0f) * 3.0f) + 2.0f), 0.0f)); // 9
        createBlock(Vector2f((((blockSize - 1.0f) * 3.0f) + 2.0f), (blockSize - 1.0f))); // 10
        createBlock(Vector2f((((blockSize - 1.0f) * 3.0f) + 2.0f), (((blockSize - 1.0f) * 2.0f) + 2.0f))); // 11
        createBlock(Vector2f((((blockSize - 1.0f) * 3.0f) + 2.0f), (((blockSize - 1.0f) * 3.0f) + 2.0f))); // 12

        createCenterBlock(Vector2f(blockSize, blockSize)); // 1
        createCenterBlock(Vector2f(blockSize, ((blockSize * 2.0f) - 1.0f))); // 2
        createCenterBlock(Vector2f(((blockSize * 2.0f) - 1.0f), blockSize)); // 3
        createCenterBlock(Vector2f(((blockSize * 2.0f) - 1.0f), (blockSize * 2.0f) - 1.0f)); // 4
    }

    GeoClipMapBlock* GeoClipMapLevel::newBlock(const Vector2f _blockPosition)
    {
        unsigned int blockSize = (gridSize_ + 1) / 4;
        return new GeoClipMapBlock(blockSize, gridSpacing_, _blockPosition, Vector2f(_blockPosition.x() * gridSpacing_,
            _blockPosition.y() * gridSpacing_), Size<float>(heightMap_->width(), heightMap_->height()));
    }

    void GeoClipMapLevel::createBlock(const Vector2f _blockPosition)
    {
        blocks_.push_back(newBlock(_blockPosition));
    }

    void GeoClipMapLevel::createCenterBlock(const Vector2f _blockPosition)
    {
        centerBlocks_.push_back(newBlock(_blockPosition));
    }

    void GeoClipMapLevel::setupRingFixUp()
    {
        ringFixUp_ = new GeoClipMapRingFixUp(gridSpacing_, gridSize_, (gridSize_ + 1) / 4);
    }

    void GeoClipMapLevel::setupInteriorTrim()
    {
        interiorTrim_.push_back(new GeoClipMapInteriorTrim(gridSpacing_, gridSize_, (gridSize_ + 1) / 4)); // 1
        interiorTrim_.push_back(new GeoClipMapInteriorTrim(gridSpacing_, gridSize_, (gridSize_ + 1) / 4)); // 2
    }

    void GeoClipMapLevel::setupDegenerateTriangle()
    {
        degenerateTriangle_ = new GeoClipMapDegenrateTriangle(gridSpacing_, gridSize_);
    }

    void GeoClipMapLevel::render(Camera* _camera, Shader* _shader)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, heightMap_->textureId());

        _shader->use();
        _shader->setFloat("gmapping.gridSize", gridSize_);
        _shader->setInt("gmapping.gridSize", gridSize_);
        _shader->setInt("gmapping.heightMapTexture", 0);
        _shader->setFloat("gmapping.maxHeight", maxHeight_);
        _shader->setVec2("gmapping.heightMapSize", heightMap_->width(), heightMap_->height());

        float transitionWith = gridSize_ / 10.0f;

        // ((n - 1) / 2) - w - 1
        // n - grid size
        // w - transition width
        _shader->setInt("gmapping.alphaOffset", ((gridSize_ - 1) / 2.0f) - transitionWith - 1.0f);

        // ((n - 1) / 2) - (1.0f / w) - 1
        // n - grid size
        // w - transition width
        _shader->setInt("gmapping.oneOverWidth", ((gridSize_ - 1) / 2.0f) - (1.0f / transitionWith) - 1.0f);

        Vector3f cameraPos = _camera->translation();
        Vector2i cameraPosWithoutHeight = Vector2i(cameraPos.x(), cameraPos.z());

        Vector2i roundedMinPosition = Vector2i(minPosition_.x(), minPosition_.y());
        Vector2i worldPosition = cameraPosWithoutHeight - roundedMinPosition;
        worldPosition /= gridSpacing_;

        if(!isInCentral(worldPosition))
        {
            unsigned int blockSize = (gridSize_ + 1) / 4;
            unsigned int lowerLimit = (blockSize - 1) * 2;

            Vector2i deltaPos = worldPosition - Vector2i(lowerLimit, lowerLimit);
            int xDelta = std::abs((int)deltaPos.x()) % 2;
            int yDelta = std::abs((int)deltaPos.y()) % 2;
            roundedMinPosition += (deltaPos - Vector2i(xDelta, yDelta)) * gridSpacing_;

            worldPosition = cameraPosWithoutHeight - roundedMinPosition;
            worldPosition /= gridSpacing_;
        }

        minPosition_ = Vector2f(roundedMinPosition.x(), roundedMinPosition.y());

        for(auto block : blocks_)
            block->drawChunk(_shader, minPosition_);

        ringFixUp_->drawChunk(_shader, minPosition_);

        for(auto trim : interiorTrim_)
            trim->drawChunk(_shader, minPosition_);

        degenerateTriangle_->drawChunk(_shader, minPosition_);

        if(childLevel_)
        {
            for(auto block : centerBlocks_)
                block->drawChunk(_shader, minPosition_);
        }
    }

    bool GeoClipMapLevel::isInCentral(Vector2i _currPosition)
    {
        int blockSize = (gridSize_ + 1) / 4;
        int lowerLimit = (blockSize - 1) * 2;
        int upperLimit = ((blockSize - 1) * 2) + 1;

        Vector2i roundedPos = Vector2i(_currPosition.x(), _currPosition.y());

        if((roundedPos.x() >= lowerLimit && roundedPos.y() >= lowerLimit) && (roundedPos.x() <= upperLimit && roundedPos.y() <= upperLimit))
            return true;

        return false;
    }
}
