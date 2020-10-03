#ifndef NAGE_ENGINE_WORLD_PROCEDURAL_DIAMONDSQUARE_H_
#define NAGE_ENGINE_WORLD_PROCEDURAL_DIAMONDSQUARE_H_

#include "engine/util/random.h" // random numbers generator
#include <cassert> // assert

namespace NAGE
{
    class DiamondSquare
    {
    public:
        DiamondSquare(int _width, int _height)
            : seedValue_(0.5f),
              width_(_width),
              height_(_height)
        {
            // Size (width, height) = 2 ^ n + 1, e.g. n = 2 -> width = 5, height = 5
            allocate(); // Allocate memory
            fill(0.0f); // Fill an array by random value.
            initialize(); // Initialize buffer (4 corners by seed value).
            generate(); // Generate a noise.
        }

        DiamondSquare(int _size)
            : seedValue_(0.5f),
              width_(_size),
              height_(_size)
        {
            allocate();
            fill(0.0f);
            initialize();
            generate();
        }

        ~DiamondSquare()
        {
            deallocate(); // Free buffer memory.
        }

        // Getters
        float seedValue() const { return seedValue_; }
        int width() const { return width_; }
        int height() const { return height_; }
        float value(int _x, int _z) const
        {
            assert(buffer_ && _x >= 0 && _x < width_ && _z >= 0 && _z < height_);
            return buffer_[_x * height_ + _z];
        }

        // Setters
        void setSeedValue(float _value) { seedValue_ = _value; }
        void setWidth(int _width) { width_ = _width; }
        void setHeight(int _height) { height_ = _height; }
        void setSize(int _size) { width_ = _size; height_ = _size; }

    private:
        // Private methods
        void allocate()
        {
            buffer_ = new float[width_ * height_];
        }

        void deallocate()
        {
            delete[] buffer_;
        }

        void fill(float _value)
        {
            for(int i = 0; i < width_; i++)
            {
                for(int j = 0; j < height_; j++)
                {
                    buffer_[i * height_ + j] = _value;
                }
            }
        }

        void setValue(int _x, int _z, float _value)
        {
            assert(_x >= 0 && _x < width_ && _z >= 0 && _z < height_);
            buffer_[_x * height_ + _z] = _value;
        }

        void initialize()
        {
            // Initialize values for 4 corners.
            setValue(0, 0, seedValue_);
            setValue(width_ - 1, 0, seedValue_);
            setValue(0, height_ - 1, seedValue_);
            setValue(height_ - 1, 0, seedValue_);
        }

        /*       n
         *
         *   w   x   e
         *
         *       s
         */
        float diamondStep(int _x, int _z, int _step)
        {
            int half = _step / 2;

            float n = value(_x, (_z - half + height_ - 1) % (height_ - 1));
            float w = value((_x - half + width_ - 1) % (width_ - 1), _z);
            float e = value((_x + half) % (width_ - 1), _z);
            float s = value(_x, (_z + half) % (height_ - 1));

            float avg = (n + w + e + s) / 4.0f;
            return avg + random(-1.0f, 1.0f);
        }

        /*  nw     ne
         *
         *      x
         *
         *  sw     se
         */
        float squareStep(int _x, int _z, int _step)
        {
            float nw = value(_x, _z);
            float ne = value(_x + _step, _z);
            float sw = value(_x, _z + _step);
            float se = value(_x + _step, _z + _step);

            float avg = (nw + ne + sw + se) / 4.0f;
            return avg + random(-1.0f, 1.0f);
        }

        void divide(int _stepSize)
        {
            int halfStep = _stepSize / 2;

            if(halfStep < 1)
                return;

            for(int z = 0; z < height_ - 1; z += _stepSize)
            {
                for(int x = 0; x < width_ - 1; x += _stepSize)
                {
                    float value = squareStep(x, z, _stepSize);
                    setValue(x + halfStep, z + halfStep, value);
                }
            }

            for(int z = 0; z < height_ - 1; z += halfStep)
            {
                for(int x = (z + halfStep) % _stepSize; x < width_ - 1; x += _stepSize)
                {
                    float value = diamondStep(x, z, _stepSize);
                    setValue(x, z, value);

                    if(z == 0) setValue(width_ - 1, z, value);
                    if(x == 0) setValue(x, height_ - 1, value);
                }
            }

            divide(halfStep);
        }

        void generate()
        {
            // Run recursively.
            divide(width_ - 1);
        }

        // Members
        float* buffer_; // Store y height values.
        float seedValue_; // Initial corner value.
        int width_, height_;
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_DIAMONDSQUARE_H_
