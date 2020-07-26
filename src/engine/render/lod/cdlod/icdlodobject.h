#ifndef NAGE_ENGINE_RENDER_LOD_ICDLODOBJECT_H_
#define NAGE_ENGINE_RENDER_LOD_ICDLODOBJECT_H_

#include "cdlodobjectchunk.h"
#include "engine/components/camera/camera.h"
#include "engine/render/lod/cdlod/cdlod.h"
#include "engine/render/culling/frustumculling.h"

#include <map>

namespace NAGE
{
    class ICDLODObject
    {
    public:
        ICDLODObject(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settins = CDLODSettings());
        virtual ~ICDLODObject();

        // Getters
        int lodLevel() const;
        float maxHeight() const;
        unsigned int chunkCount() const;
        CDLOD* lod();
        std::map<int, CDLODObjectChunk*> chunks() const;
        CDLODObjectChunk* chunk(int _dimension);
        HeightMap* heightMap();

        // Setters
        void setMaxHeight(float _height);

        virtual void setHeightMapProperties(Shader* _shader);
        virtual void renderCDLOD(Camera* _camera, Shader* _shader, Transform* _transform);

    protected:
        int mLodLevel;
        float mMaxHeight;
        CDLOD* mLOD;
        FrustumCulling* mFrustum;
        HeightMap* mHeightMap;
        std::map<int, CDLODObjectChunk*> mTerrainChunks; // key: dimension, value: chunk grid
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_ICDLODOBJECT_H_
