#ifndef NAGE_ENGINE_RENDER_COLOR_H_
#define NAGE_ENGINE_RENDER_COLOR_H_

#include <iostream>

namespace NAGE
{
    /* Pixel color representation.
     *
     * Format: rgb <0.0f, 1.0f>
     */
    class Color
    {
    public:
        Color(float _red = 0.0f, float _green = 0.0f,
            float _blue = 0.0f, float _alpha = 1.0f);

        // Getters
        float red() const;
        float green() const;
        float blue() const;
        float alpha() const;

        // Setters
        void setRed(float _red);
        void setGreen(float _green);
        void setBlue(float _blue);
        void setAlpha(float _alpha = 1.0f);

        /* Linear interpolation between two colors.
         *
         * function(a, b, t)
         *     return (1 - t) * a + t * b;
         */
        Color& lerp(Color _colorB, float _blending);
        static Color lerp(Color _colorA, Color _colorB, float _blending);

        static const Color white;
        static const Color black;

        friend std::ostream& operator<<(std::ostream& _out, const Color& _color);

    private:
        float red_;
        float green_;
        float blue_;
        float alpha_;
    };
}

#endif // NAGE_ENGINE_RENDER_COLOR_H_
