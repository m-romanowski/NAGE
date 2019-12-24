#include "color.h"

namespace NAGE
{
    const Color Color::white(1.0f, 1.0f, 1.0f);
    const Color Color::black(0.0f, 0.0f, 0.0f);

    Color::Color(float _red, float _green, float _blue, float _alpha)
    {
        // Color r, g, b = <0.0f, 1.0f>
        if(_red > 1.0f) mRed = _red / 255.0f;
        else mRed = _red;

        if(_green > 1.0f) mGreen= _green / 255.0f;
        else mGreen = _green;

        if(_blue > 1.0f) mBlue = _blue / 255.0f;
        else mBlue = _blue;

        if(_alpha > 1.0f) mAlpha = _alpha / 255.0f;
        else mAlpha = _alpha;
    }

    float Color::red() const
    {
        return mRed;
    }

    float Color::green() const
    {
        return mGreen;
    }

    float Color::blue() const
    {
        return mBlue;
    }

    float Color::alpha() const
    {
        return mAlpha;
    }

    void Color::setRed(float _red)
    {
        if(_red > 1.0f)
            _red /= 255.0f;

        mRed = _red;
    }

    void Color::setGreen(float _green)
    {
        if(_green > 1.0f)
            _green /= 255.0f;

        mGreen = _green;
    }

    void Color::setBlue(float _blue)
    {
        if(_blue > 1.0f)
            _blue /= 255.0f;

        mBlue = _blue;
    }

    void Color::setAlpha(float _alpha)
    {
        if(_alpha > 1.0f)
            _alpha /= 255.0f;

        mAlpha = _alpha;
    }

    Color& Color::lerp(Color _color, float _blending)
    {
        float inverseBlending = 1.0f - _blending;

        float red = inverseBlending * this->red() + _blending * _color.red();
        float green = inverseBlending * this->green() + _blending * _color.green();
        float blue = inverseBlending * this->blue() + _blending * _color.blue();

        this->mRed = red;
        this->mGreen = green;
        this->mBlue = blue;

        return *this;
    }

    Color Color::lerp(Color _colorA, Color _colorB, float _blending)
    {
        float inverseBlending = 1.0f - _blending;

        float red = inverseBlending * _colorA.red() + _blending * _colorB.red();
        float green = inverseBlending * _colorA.green() + _blending * _colorB.green();
        float blue = inverseBlending * _colorA.blue() + _blending * _colorB.blue();

        return Color(red, green, blue);
    }

    std::ostream& operator<< (std::ostream& _out, const Color& _color)
    {
        _out << "Color(" << _color.red() << ", "
            << _color.green() << ", " << _color.blue() << ", " << _color.alpha() << ")" << std::endl;

        return _out;
    }
}
