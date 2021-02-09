#include "texture.h"
#include <iostream>

namespace mr::nage
{
    Texture::Texture(TextureType _type)
        : type_(_type),
          textureWrapping_(Vector3<GLint>(GL_REPEAT, GL_REPEAT, GL_REPEAT)),
          textureFiltering_(Vector2<GLint>(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR))
    {

    }

    Texture::Texture(const std::string& _path, TextureType _type)
        : type_(_type),
          textureWrapping_(Vector3<GLint>(GL_REPEAT, GL_REPEAT, GL_REPEAT)),
          textureFiltering_(Vector2<GLint>(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR))
    {
        fromFile(_path);
    }

    Texture::Texture(int _width, int _height, unsigned char* _data, TextureType _type, TextureFormat _textureFormat)
        : type_(_type),
          width_(_width),
          height_(_height),
          data_(_data),
          format_(_textureFormat),
          textureWrapping_(Vector3<GLint>(GL_REPEAT, GL_REPEAT, GL_REPEAT)),
          textureFiltering_(Vector2<GLint>(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR))
    {

    }

    Texture::~Texture()
    {
        // Clean up binding.
        clean();
    }

    /* Texture id.
     *
     * @return unsigned int
     */
    GLuint Texture::id() const
    {
        return id_;
    }

    /* Texture width.
     *
     * @return int
     */
    int Texture::width() const
    {
        return width_;
    }

    /* Texture height.
     *
     * @return int
     */
    int Texture::height() const
    {
        return height_;
    }

    /* Texture pixel color data.
     *
     * @return unsigned char*
     */
    unsigned char* Texture::data()
    {
        return data_;
    }

    std::vector<unsigned char> Texture::redColorData()
    {
        std::vector<unsigned char> result;

        for(int i = 0; i < width_; i++)
        {
            for(int j = 0; j < height_; j++)
                result.push_back(Image::red(data_, format_, width_, i, j));
        }

        return result;
    }

    std::vector<unsigned char> Texture::greenColorData()
    {
        std::vector<unsigned char> result;

        for(int i = 0; i < width_; i++)
        {
            for(int j = 0; j < height_; j++)
            {
                result.push_back(Image::green(data_, format_, width_, i, j));
            }
        }

        return result;
    }

    std::vector<unsigned char> Texture::blueColorData()
    {
        std::vector<unsigned char> result;

        for(int i = 0; i < width_; i++)
        {
            for(int j = 0; j < height_; j++)
            {
                result.push_back(Image::blue(data_, format_, width_, i, j));
            }
        }

        return result;
    }

    std::vector<unsigned char> Texture::alphaColorData()
    {
        std::vector<unsigned char> result;

        for(int i = 0; i < width_; i++)
        {
            for(int j = 0; j < height_; j++)
            {
                result.push_back(Image::alpha(data_, format_, width_, i, j));
            }
        }

        return result;
    }

    /* Pixel color at (x, y) position
     *
     * @return unsigned char[4] - RGBA value
     */
    unsigned char* Texture::dataAt(int _x, int _y)
    {
        // RGBA color
        unsigned char* pixelColor = new unsigned char[4];
        Image::colorAt(data_, format_, width_, _x, _y, &pixelColor[0], &pixelColor[1],
            &pixelColor[2], &pixelColor[3]);

        return pixelColor;
    }

    /* Texture format.
     *
     * @return GLenum { GL_RED, GL_RGB, GL_RGBA }
     */
    GLenum Texture::format() const
    {
        return format_;
    }

    /* Texture type.
     *
     * @return enum TextureType { TEXTURE_2D, TEXTURE_3D }
     */
    TextureType Texture::type() const
    {
        return type_;
    }

    /* Texture wrapping type.
     *
     * @return Vector3(S, T, R) - axises.
     */
    Vector3<GLint> Texture::textureWrapping() const
    {
        return textureWrapping_;
    }

    /* Texture filtering type.
     *
     * @return Vector2(MIN, MAG)
     *  MIN - minifying
     *  MAG - magnifying
     */
    Vector2<GLint> Texture::textureFiltering() const
    {
        return textureFiltering_;
    }

    /* Texture wrapping type.
     *
     * @param Vector3(S, T, R) - axises.
     */
    void Texture::setTextureWrapping(const Vector3<GLint>& _type)
    {
        textureWrapping_ = _type;
    }

    /* Texture filtering type.
     *
     * @param Vector2(MIN, MAG)
     *  MIN - minifying
     *  MAG - magnifying
     */
    void Texture::setTextureFiltering(const Vector2<GLint>& _type)
    {
        textureFiltering_ = _type;
    }

    void Texture::setDataAt(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
    {
        data_[format_ * (_y * width_ + _x) + 0] = _r;
        data_[format_ * (_y * width_ + _x) + 1] = _g;
        data_[format_ * (_y * width_ + _x) + 2] = _b;
        format_ >= 4
            ? data_[format_ * (_y * width_ + _x) + 3] = _a
            : data_[format_ * (_y * width_ + _x) + 3] = 0xff;
    }

    void Texture::bindTexture()
    {
        glGenTextures(1, &id_);
        GLenum textureFormat;

        if(format_ == 1) textureFormat = GL_RED;
        else if(format_ == 3) textureFormat = GL_RGB;
        else if(format_ == 4) textureFormat = GL_RGBA;

        // Texture wrapping.
        if(type_ == TextureType::TEXTURE_3D)
        {
            // TODO: 3D texture support
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, id_);
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(textureFormat), width_, height_,
                0, textureFormat, GL_UNSIGNED_BYTE, data_);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapping_.x());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapping_.y());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFiltering_.x());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFiltering_.y());
        }
    }

    void Texture::bindEmptyTexture()
    {
        glGenTextures(1, &id_);

        glBindTexture(GL_TEXTURE_2D, id_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    /* Load and initialize texture.
     *
     * @param std::string - path to texture.
     */
    void Texture::fromFile(const std::string& _path)
    {
        Image image(_path);
        data_ = image.data();
        format_ = static_cast<GLenum>(image.format());
        width_ = image.width();
        height_ = image.height();

        if(data_)
            bindTexture();
    }

    void Texture::fromData(int _width, int _height, TextureFormat _format, unsigned char* _data)
    {
        width_ = _width;
        height_ = _height;
        format_ = static_cast<GLenum>(_format);
        data_ = _data;

        bindTexture();
    }

    void Texture::empty(int _width, int _height)
    {
        width_ = _width;
        height_ = _height;

        bindEmptyTexture();
    }

    void Texture::clean()
    {
        glDeleteTextures(1, &id_);
    }
}
