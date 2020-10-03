#ifndef NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_
#define NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_

#include "glad/glad.h"
#include "common/log.h"
#include "engine/components/types.h"
#include "engine/components/image.h"
#include "engine/math/NAGEMath/nagemathvector.h"

#include <string>

namespace mr::nage
{
    class Texture
    {
    public:
        enum TextureFormat
        {
            RED = 1,
            RGB = 3,
            RGBA = 4
        };

        explicit Texture(TextureType _type = TextureType::TEXTURE_2D);
        explicit Texture(const std::string& _path, TextureType _type);
        ~Texture();

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

        void fromFile(const std::string& _path);
        void fromData(int _width, int _height, TextureFormat _format, unsigned char* _data);
        void empty(int _width, int _height);
        void clean();

    private:
        void bindTexture();
        void bindEmptyTexture();

        GLuint id_;
        TextureType type_;
        int width_, height_;
        unsigned char* data_;
        GLenum format_;
        Vector3<GLint> textureWrapping_; // S, T, R axis
        Vector2<GLint> textureFiltering_; // MIN - minifying, MAG - magnifying
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_TEXTURE_H_
