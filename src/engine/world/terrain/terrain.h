#ifndef NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_
#define NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_

#include "heightmap.h"
#include "terrainchunk.h"
#include "engine/util/random.h"
#include "engine/render/model/mesh.h"

#define DEFAULT_CHUNK_DIMENSION 5

namespace NAGE
{
    class Terrain : public IObject
    {
    public:
        Terrain();
        ~Terrain();

        // Getters
        int width() const;
        int height() const;
        int chunkDimension() const;
        Shader* shader();
        Transform* transform();
        float positionHeight(int _x, int _z);
        HeightMap* heightMap();

        // Setters
        void setWidth(int _width);
        void setHeight(int _height);
        void setChunkDimension(int _size);
        void setShader(Shader* _shader);
        void setMaterial(Material* _material);
        void addTexture(Texture* _texture);
        void addHeightMap(HeightMap* _heightmap);
        void addFlatTerrain(int _width, int _height);

        void useMaterial();
        void bindTextures();
        void drawChunks(Camera* _camera);
        void loadFromFile(const std::string& _path);

    private:
        void splitIntoChunks(int _x, int _y, int _width, int _height, int _dimension);

        int mWidth, mHeight;
        int mChunkDimension;
        HeightMap* mHeightMap;
        Material* mMaterial;
        Transform* mTransform;
        Shader* mShader;
        std::vector<Texture*> mTextures;
        std::vector<TerrainChunk*> mChunks;
    };
}

#endif // NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_
