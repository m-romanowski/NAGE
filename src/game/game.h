#ifndef NAGE_GAME_GAME_H_
#define NAGE_GAME_GAME_H_

#include "engine/core/igame.h"
#include "engine/world/light/sun.h"
#include "engine/world/primitives/cube.h"
#include "engine/world/primitives/sphere.h"
#include "engine/world/terrain/cdlodterrain.h"
#include "engine/world/water/cdlodwater.h"

namespace NAGE
{
    class Game : public IGame
    {
    public:
        Game(FpsLimit _limit = FpsLimit::FPS_60);
        virtual ~Game() override;

        void initializeScene() override;
    private:
        // Skybox
        Shader* skyboxShader;
        Skybox* skybox;

        // Lamp
        Shader* lampShader;
        PointLight* lamp;
        Transform* lampTransform;

        // Sun
        Sun* sun;

        // Terrain
        Texture *blendmap, *terrainTexture1, *terrainTexture2, *terrainTexture3, *terrainTexture4;
        HeightMap* heightMap;
        CDLODTerrain* cdlodTerrain;

        // Water
        CDLODWater* cdlodWater;
        HeightMap* waterHeightmap;
    };
}

#endif // NAGE_GAME_GAME_H_
