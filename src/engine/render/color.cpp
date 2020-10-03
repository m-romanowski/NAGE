#include "color.h"

namespace mr::nage
{
    const Color Color::white(1.0f, 1.0f, 1.0f);
    const Color Color::black(0.0f, 0.0f, 0.0f);

    Color::Color(float _red, float _green, float _blue, float _alpha)
    {
        // Color r, g, b = <0.0f, 1.0f>
        if(_red > 1.0f) red_ = _red / 255.0f;
        else red_ = _red;

        if(_green > 1.0f) green_ = _green / 255.0f;
        else green_ = _green;

        if(_blue > 1.0f) blue_ = _blue / 255.0f;
        else blue_ = _blue;

        if(_alpha > 1.0f) alpha_ = _alpha / 255.0f;
        else alpha_ = _alpha;
    }

    float Color::red() const
    {
        return red_;
    }

    float Color::green() const
    {
        return green_;
    }

    float Color::blue() const
    {
        return blue_;
    }

    float Color::alpha() const
    {
        return alpha_;
    }

    void Color::setRed(float _red)
    {
        if(_red > 1.0f)
            _red /= 255.0f;

        red_ = _red;
    }

    void Color::setGreen(float _green)
    {
        if(_green > 1.0f)
            _green /= 255.0f;

        green_ = _green;
    }

    void Color::setBlue(float _blue)
    {
        if(_blue > 1.0f)
            _blue /= 255.0f;

        blue_ = _blue;
    }

    void Color::setAlpha(float _alpha)
    {
        if(_alpha > 1.0f)
            _alpha /= 255.0f;

        alpha_ = _alpha;
    }

    Color& Color::lerp(Color _color, float _blending)
    {
        float inverseBlending = 1.0f - _blending;

        float red = inverseBlending * this->red() + _blending * _color.red();
        float green = inverseBlending * this->green() + _blending * _color.green();
        float blue = inverseBlending * this->blue() + _blending * _color.blue();

        this->red_ = red;
        this->green_ = green;
        this->blue_ = blue;

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
