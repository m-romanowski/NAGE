    #include "engine/render/glrenderengine.h"
#include "terrain.h"

namespace NAGE
{
    Terrain::Terrain()
        : mWidth(0),
          mHeight(0),
          mChunkDimension(DEFAULT_CHUNK_DIMENSION),
          mHeightMap(nullptr),
          mTransform(new Transform)
    {

    }

    Terrain::~Terrain()
    {
        delete mShader;

        // Clear all chunks.
        for(auto& chunk : mChunks)
            delete chunk;

        // Clear height map data
        if(mHeight)
            delete mHeightMap;
    }

    int Terrain::width() const
    {
        return mWidth;
    }

    int Terrain::height() const
    {
        return mHeight;
    }

    int Terrain::chunkDimension() const
    {
        return mChunkDimension;
    }

    Shader* Terrain::shader()
    {
        return mShader;
    }

    Transform* Terrain::transform()
    {
        return mTransform;
    }

    float Terrain::positionHeight(int _x, int _z)
    {
        if(!mHeightMap || _x < 0 || _x >= mWidth || _z < 0 || _z >= mHeight)
            return 0;

        return mHeightMap->noise(_x, _z);
    }

    HeightMap* Terrain::heightMap()
    {
        return mHeightMap;
    }

    void Terrain::setWidth(int _width)
    {
        mWidth = _width;
    }

    void Terrain::setHeight(int _height)
    {
        mHeight = _height;
    }

    void Terrain::setChunkDimension(int _size)
    {
        mChunkDimension = _size;
    }

    void Terrain::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void Terrain::setMaterial(Material* _material)
    {
        mMaterial = _material;
    }

    void Terrain::addTexture(Texture* _texture)
    {
        mTextures.push_back(_texture);
    }

    void Terrain::addHeightMap(HeightMap* _heightmap)
    {
        if(mHeightMap)
            delete mHeightMap;

        mWidth = _heightmap->width();
        mHeight = _heightmap->height();
        mHeightMap = _heightmap;

        splitIntoChunks(0, 0, mWidth, mHeight, mChunkDimension);
    }

    void Terrain::addFlatTerrain(int _width, int _height)
    {
        mWidth = _width;
        mHeight = _height;

        if(mHeightMap)
            delete mHeightMap;

        mHeightMap = new HeightMap;
        mHeightMap->flat(_width, _height);

        splitIntoChunks(0, 0, _width, _height, mChunkDimension);
    }

    /* Load mesh from the file.
     */
    void Terrain::loadFromFile(const std::string& _path)
    {
        // TODO
        NAGE_UNUSED(_path);
    }

    /* Send material values to the shader.
     */
    void Terrain::useMaterial()
    {
        mMaterial->use(mShader);
    }

    void Terrain::splitIntoChunks(int _x, int _y, int _width, int _height, int _dimension)
    {
        if(_dimension > 1)
        {
            int halfWidth = _width / 2;
            int halfHeight = _height / 2;
            int newDimension = _dimension - 1;

            splitIntoChunks(_x, _y, halfWidth, halfHeight, newDimension);
            splitIntoChunks(_x + halfWidth, _y, halfWidth, halfHeight, newDimension);
            splitIntoChunks(_x, _y + halfHeight, halfWidth, halfHeight, newDimension);
            splitIntoChunks(_x + halfWidth, _y + halfHeight, halfWidth, halfHeight, newDimension);
        }
        else
        {
            mChunks.push_back(new TerrainChunk(this, _x, _y, _width, _height));
        }
    }

    void Terrain::bindTextures()
    {
        for(GLuint i = 0; i < mTextures.size(); i++)
        {
            if(mTextures[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
            }
        }
    }

    /* Draw all terrain chunks.
     */
    void Terrain::drawChunks(Camera *_camera)
    {
        for(auto& chunk : mChunks)
            chunk->draw(_camera, mShader);
    }
}
