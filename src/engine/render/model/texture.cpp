#include "texture.h"
#include <iostream>

namespace NAGE
{
    Texture::Texture(const std::string& _path, TextureType _type)
        : mType(_type),
          mTextureWrapping(Vector3<GLint>(GL_REPEAT, GL_REPEAT, GL_REPEAT)),
          mTextureFiltering(Vector2<GLint>(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR))
    {
        loadTexture(_path);
    }

    /* Texture id.
     *
     * @return unsigned int
     */
    GLuint Texture::id() const
    {
        return mId;
    }

    /* Texture width.
     *
     * @return int
     */
    int Texture::width() const
    {
        return mWidth;
    }

    /* Texture height.
     *
     * @return int
     */
    int Texture::height() const
    {
        return mHeight;
    }

    /* Texture format.
     *
     * @return GLenum { GL_RED, GL_RGB, GL_RGBA }
     */
    GLenum Texture::format() const
    {
        return mFormat;
    }

    /* Texture type.
     *
     * @return enum TextureType { TEXTURE_2D, TEXTURE_3D }
     */
    TextureType Texture::type() const
    {
        return mType;
    }

    /* Texture wrapping type.
     *
     * @return Vector3(S, T, R) - axises.
     */
    Vector3<GLint> Texture::textureWrapping() const
    {
        return mTextureWrapping;
    }

    /* Texture filtering type.
     *
     * @return Vector2(MIN, MAG)
     *  MIN - minifying
     *  MAG - magnifying
     */
    Vector2<GLint> Texture::textureFiltering() const
    {
        return mTextureFiltering;
    }

    /* Texture wrapping type.
     *
     * @param Vector3(S, T, R) - axises.
     */
    void Texture::setTextureWrapping(const Vector3<GLint>& _type)
    {
        mTextureWrapping = _type;
    }

    /* Texture filtering type.
     *
     * @param Vector2(MIN, MAG)
     *  MIN - minifying
     *  MAG - magnifying
     */
    void Texture::setTextureFiltering(const Vector2<GLint>& _type)
    {
        mTextureFiltering = _type;
    }

    /* Load and initialize texture from image.
     *
     * @param std::string - path to texture.
     */
    void Texture::loadTexture(const std::string& _path)
    {
        glGenTextures(1, &mId);

        Image image(_path);
        unsigned char* data = image.data();
        mFormat = static_cast<GLenum>(image.format());
        mWidth = image.width();
        mHeight = image.height();

        if(data)
        {
            GLenum textureFormat;

            if(mFormat == 1) textureFormat = GL_RED;
            else if(mFormat == 3) textureFormat = GL_RGB;
            else if(mFormat == 4) textureFormat = GL_RGBA;

            // Texture wrapping.
            if(mType == TextureType::TEXTURE_3D)
            {
                // TODO: 3D texture support
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, mId);
                glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(textureFormat), mWidth, mHeight,
                    0, textureFormat, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureWrapping.x());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureWrapping.y());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureFiltering.x());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureFiltering.y());
            }

            image.free();
        }
    }
}
