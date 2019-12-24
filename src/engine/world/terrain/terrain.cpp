#include "engine/render/glrenderengine.h"
#include "terrain.h"

namespace NAGE
{
    Terrain::Terrain()
        : mWidth(0),
          mHeight(0),
          mTransform(new Transform)
    {

    }

    Terrain::~Terrain()
    {
        delete mShader;

        // Clear all chunks.
        for(auto& chunk : mChunks)
            delete chunk;
    }

    int Terrain::width() const
    {
        return mWidth;
    }

    int Terrain::height() const
    {
        return mHeight;
    }

    Shader* Terrain::shader()
    {
        return mShader;
    }

    Transform* Terrain::transform()
    {
        return mTransform;
    }

    void Terrain::setWidth(int _width)
    {
        mWidth = _width;
    }

    void Terrain::setHeight(int _height)
    {
        mHeight = _height;
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

    void Terrain::generateFlatTerrain(int _width, int _height)
    {

    }

    /* Generate Perlin noise.
     */
    void Terrain::generateNoise(int _width, int _height, HeightMap::NoiseType _type)
    {
        mWidth = _width;
        mHeight = _height;

        HeightMap map1;
        float** heightMap1 = map1.generateFromNoise(_width, _height, HeightMap::NoiseType::Perlin);

        useHeightMap(_width, _height, heightMap1);
        setupBuffer();
        //splitIntoChunks(0, 0, mWidth, mHeight, 5);
    }

    /* Load mesh from the file.
     */
    void Terrain::loadFromFile(const std::string& _path)
    {

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
            int newPagesPerDimension = _dimension - 1;

            splitIntoChunks(_x, _y, halfWidth, halfHeight, newPagesPerDimension);
            splitIntoChunks(_x + halfWidth, _y, halfWidth, halfHeight, newPagesPerDimension);
            splitIntoChunks(_x, _y + halfHeight, halfWidth, halfHeight, newPagesPerDimension);
            splitIntoChunks(_x + halfWidth, _y + halfHeight, halfWidth, halfHeight, newPagesPerDimension);
        }
        else
        {
            mChunks.push_back(new TerrainChunk(this, _x, _y, _width, _height));
        }
    }

    void Terrain::useHeightMap(int _width, int _height, float** _heightMap)
    {
        Plane primitive(_width, _height);
        std::vector<Vertex> vertices = primitive.vertices();
        std::vector<unsigned int> indices = primitive.indices();

        for(auto& vertice : vertices)
        {
            int x = static_cast<int>(vertice.position.x());
            int z = static_cast<int>(vertice.position.z());
            vertice.position.setY(_heightMap[x][z]);
        }


        mVertices = vertices;
        mIndices = indices;
        Primitive::calculateNormals(mVertices, mIndices);
    }

    /* Draw all terrain chunks.
     */
    void Terrain::drawChunks(Camera *_camera)
    {
        for(auto& chunk : mChunks)
        {
            chunk->draw(_camera, mShader);
        }

        if(!mShader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        mShader->use();
        mShader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        mShader->setMat4("view", _camera->view().transpose());
        mShader->setMat4("model", mTransform->model().transpose());

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
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
}
