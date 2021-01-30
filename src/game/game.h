#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include "engine/world/terrain/geoclipmapterrain.h"
#include "engine/world/skybox/sunlight.h"
#include "engine/core/igame.h"
#include "engine/world/light/directionallightobject.h"
#include "engine/world/light/pointlightobject.h"
#include "engine/world/primitives/cube.h"
#include "engine/world/primitives/sphere.h"
#include "engine/world/terrain/cdlodterrain.h"
#include "engine/world/water/cdlodwater.h"
#include "engine/world/skybox/daynightskybox.h"
#include "engine/world/skybox/daynightskydome.h"
#include "engine/render/model/model.h"

namespace mr::nage
{
    class Game : public IGame
    {
    public:
        Game(FpsLimit _limit = FpsLimit::FPS_60);
        virtual ~Game() override {};

        void initializeScene() override;
        void ioEventsSupplier() override;

    private:
        std::string addTrailingZeroIfNeeded(int _x);
        void printWorldHourLog();

        Camera camera;

        // Skybox
        std::shared_ptr<Shader> skyboxShader;
        std::shared_ptr<DayNightSkydome> skybox;

        // Lamp
        std::shared_ptr<Shader> lampShader;
        std::shared_ptr<PointLightObject> lamp;
        std::shared_ptr<Transform> lampTransform;

        // Sun
        std::shared_ptr<SunLight> sun;

        // CDLOD Terrain
        std::shared_ptr<Texture> blendmap, terrainTexture1, terrainTexture2, terrainTexture3, terrainTexture4;
        std::shared_ptr<HeightMap> heightMap;
        std::shared_ptr<CDLODTerrain> cdlodTerrain;

        // Geoclipmapping Terrain
        std::shared_ptr<GeoClipMapTerrain> geoclipmapTerrain;

        // Water
        std::shared_ptr<CDLODWater> cdlodWater;
        std::shared_ptr<HeightMap> waterHeightmap;

        int currHour, currMin;
        int counterForSun;
    };
}

#endif // GAME_GAME_H_
