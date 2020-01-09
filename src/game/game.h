#ifndef NAGE_GAME_GAME_H_
#define NAGE_GAME_GAME_H_

#include "engine/core/igame.h"
#include "engine/world/light/sun.h"
#include "engine/world/terrain/terrain.h"
#include "engine/world/primitives/cube.h"
#include "engine/world/primitives/sphere.h"

namespace NAGE
{
    class Game : public IGame
    {
    public:
        Game(FpsLimit _limit = FpsLimit::FPS_60);
        virtual ~Game() override;

        void initializeScene() override;
    private:
        Shader *lightingShader, *lampShader, *skyboxShader, *cubeShader;
        Mesh* mesh, *cubeMesh;
        Model* cubeModel;
        Material* material;
        Transform *transform, *cubeTransform;

        PointLight* lamp;
        Sun* sun;
        Skybox* skybox;
        Texture* diff, *spec, *diffCube, *specCube;

        // Terrain
        Terrain* terrain;
        Shader* terrainShader;
        Material* terrainMaterial;
    };
}

#endif // NAGE_GAME_GAME_H_
