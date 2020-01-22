#ifndef NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_
#define NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_

#include "glad/glad.h"
#include "common/log.h"
#include "engine/components/types.h"
#include "engine/components/image.h"
#include "engine/math/NAGEMath/nagemathvector.h"

#include <string>

namespace NAGE
{
    class Texture
    {
    public:
        Texture(const std::string& _path, TextureType _type);

        // Getters
        GLuint id() const;
        int width() const;
        int height() const;
        unsigned char* data();
        std::vector<unsigned char> redColorData();
        std::vector<unsigned char> greenColorData();
        std::vector<unsigned char> alphaColorData();
        std::vector<unsigned char> blueColorData();
        unsigned char* dataAt(int _x, int _y);
        GLenum format() const;
        TextureType type() const;
        Vector3<GLint> textureWrapping() const;
        Vector2<GLint> textureFiltering() const;

        // Setters
        void setTextureWrapping(const Vector3<GLint>& _type);
        void setTextureFiltering(const Vector2<GLint>& _type);

    private:
        void loadTexture(const std::string& _path);

        GLuint mId;
        TextureType mType;
        int mWidth, mHeight;
        unsigned char* mData;
        GLenum mFormat;
        Vector3<GLint> mTextureWrapping; // S, T, R axis
        Vector2<GLint> mTextureFiltering; // MIN - minifying, MAG - magnifying
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_
