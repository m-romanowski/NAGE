#ifndef NAGE_GAME_GAME_H_
#define NAGE_GAME_GAME_H_

#include "engine/core/igame.h"
#include "engine/world/light/sun.h"
#include "engine/world/primitives/cube.h"
#include "engine/world/primitives/sphere.h"
#include <engine/world/terrain/cdlodterrain.h>

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
        Shader* terrainShader;
        Texture* terrainTexture1;
        Material* terrainMaterial;
        HeightMap* heightMap;
        CDLODTerrain* cdlodTerrain;
    };
}

#endif // NAGE_GAME_GAME_H_
