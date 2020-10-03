#ifndef NAGE_GAME_GAME_H_
#define NAGE_GAME_GAME_H_

#include "engine/core/igame.h"
#include "engine/world/light/sun.h"
#include "engine/world/primitives/cube.h"
#include "engine/world/primitives/sphere.h"
#include "engine/world/terrain/cdlodterrain.h"
#include "engine/world/water/cdlodwater.h"

namespace mr::nage
{
    class Game : public IGame
    {
    public:
        Game(FpsLimit _limit = FpsLimit::FPS_60);
        virtual ~Game() override {};

        void initializeScene() override;

    private:
        // Skybox
        std::shared_ptr<Shader> skyboxShader;
        std::shared_ptr<Skybox> skybox;

        // Lamp
        std::shared_ptr<Shader> lampShader;
        std::shared_ptr<PointLight> lamp;
        std::shared_ptr<Transform> lampTransform;

        // Sun
        std::shared_ptr<Sun> sun;

        // Terrain
        std::shared_ptr<Texture> blendmap, terrainTexture1, terrainTexture2, terrainTexture3, terrainTexture4;
        std::shared_ptr<HeightMap> heightMap;
        std::shared_ptr<CDLODTerrain> cdlodTerrain;

        // Water
        std::shared_ptr<CDLODWater> cdlodWater;
        std::shared_ptr<HeightMap> waterHeightmap;
    };
}

#endif // NAGE_GAME_GAME_H_
