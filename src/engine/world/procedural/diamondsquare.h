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
            : mSeedValue(0.5f),
              mWidth(_width),
              mHeight(_height)
        {
            // Size (width, height) = 2 ^ n + 1, e.g. n = 2 -> width = 5, height = 5
            allocate(); // Allocate menory
            fill(0.0f); // Fill an array by random value.
            initialize(); // Initialize buffer (4 corners by seed value).
            generate(); // Generate a noise.
        }

        DiamondSquare(int _size)
            : mSeedValue(0.5f),
              mWidth(_size),
              mHeight(_size)
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
        float seedValue() const { return mSeedValue; }
        int width() const { return mWidth; }
        int height() const { return mHeight; }
        float value(int _x, int _z) const
        {
            assert(mBuffer && _x >= 0 && _x < mWidth && _z >= 0 && _z < mHeight);
            return mBuffer[_x * mHeight + _z];
        }

        // Setters
        void setSeedValue(float _value) { mSeedValue = _value; }
        void setWidth(int _width) { mWidth = _width; }
        void setHeight(int _height) { mHeight = _height; }
        void setSize(int _size) { mWidth = _size; mHeight = _size; }

    private:
        // Private methods
        void allocate()
        {
            mBuffer = new float[mWidth * mHeight];
        }

        void deallocate()
        {
            delete[] mBuffer;
        }

        void fill(float _value)
        {
            for(int i = 0; i < mWidth; i++)
            {
                for(int j = 0; j < mHeight; j++)
                {
                    mBuffer[i * mHeight + j] = _value;
                }
            }
        }

        void setValue(int _x, int _z, float _value)
        {
            assert(_x >= 0 && _x < mWidth && _z >= 0 && _z < mHeight);
            mBuffer[_x * mHeight + _z] = _value;
        }

        void initialize()
        {
            // Initialize values for 4 corners.
            setValue(0, 0, mSeedValue);
            setValue(mWidth - 1, 0, mSeedValue);
            setValue(0, mHeight - 1, mSeedValue);
            setValue(mHeight - 1, 0, mSeedValue);
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

            float n = value(_x, (_z - half + mHeight - 1) % (mHeight - 1));
            float w = value((_x - half + mWidth - 1) % (mWidth - 1), _z);
            float e = value((_x + half) % (mWidth - 1), _z);
            float s = value(_x, (_z + half) % (mHeight - 1));

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

            for(int z = 0; z < mHeight - 1; z += _stepSize)
            {
                for(int x = 0; x < mWidth - 1; x += _stepSize)
                {
                    float value = squareStep(x, z, _stepSize);
                    setValue(x + halfStep, z + halfStep, value);
                }
            }

            for(int z = 0; z < mHeight - 1; z += halfStep)
            {
                for(int x = (z + halfStep) % _stepSize; x < mWidth - 1; x += _stepSize)
                {
                    float value = diamondStep(x, z, _stepSize);
                    setValue(x, z, value);

                    if(z == 0) setValue(mWidth - 1, z, value);
                    if(x == 0) setValue(x, mHeight - 1, value);
                }
            }

            divide(halfStep);
        }

        void generate()
        {
            // Run recursively.
            divide(mWidth - 1);
        }

        // Members
        float* mBuffer; // Store y height values.
        float mSeedValue; // Initial corner value.
        int mWidth, mHeight;
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_DIAMONDSQUARE_H_
