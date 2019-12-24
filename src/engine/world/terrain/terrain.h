#ifndef NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_
#define NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_

#include "heightmap.h"
#include "terrainchunk.h"
#include "engine/util/random.h"
#include "engine/render/model/mesh.h"

#define PAGES_PER_DIMENSION 5

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
        Shader* shader();
        Transform* transform();

        // Setters
        void setWidth(int _width);
        void setHeight(int _height);
        void setShader(Shader* _shader);
        void setMaterial(Material* _material);
        void addTexture(Texture* _texture);

        void loadFromFile(const std::string& _path);
        void generateFlatTerrain(int _width, int _height);
        void generateNoise(int _width, int _height, HeightMap::NoiseType _type);
        void useMaterial();
        void bindTextures();
        void useHeightMap(int _width, int _height, float** _heightMap);
        void drawChunks(Camera* _camera);

    private:
        void splitIntoChunks(int _x, int _y, int _width, int _height, int _dimension);

        int mWidth, mHeight;
        Material* mMaterial;
        Transform* mTransform;
        Shader* mShader;
        std::vector<Texture*> mTextures;
        std::vector<TerrainChunk*> mChunks;
    };
}

#endif // NAGE_ENGINE_RENDER_TERRAIN_TERRAIN_H_
