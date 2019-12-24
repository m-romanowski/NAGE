#ifndef TERRAINCHUNK_H
#define TERRAINCHUNK_H

#include "engine/render/iobject.h"
#include "engine/math/NAGEMath/nagemathvector.h"

namespace NAGE
{
    class Terrain;

    class TerrainChunk : public IObject
    {
    public:
        TerrainChunk(Terrain* _terrain, float _x, float _y, int _width, int _height);
        TerrainChunk(const Vector2f& _position, int _width, int _height);

        // Getters
        float x() const;
        float y() const;
        Vector2f position() const;
        int width() const;
        int height() const;
        bool isVisible() const;

        // Setters
        void setVisible(bool _visible);
        void draw(Camera* _camera, Shader* _shader) override;

    private:
        Vector2f mPosition; // Chunk coordinates
        int mWidth, mHeight; // Chunk width, height
        bool mVisible;

        Terrain* terrain;
    };
}

#endif // TERRAINCHUNK_H
