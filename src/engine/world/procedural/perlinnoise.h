#ifndef NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_
#define NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_

/* Improved Perlin noise algorithm.
 *
 * https://mrl.nyu.edu/~perlin/paper445.pdf
 * https://mrl.nyu.edu/~perlin/noise/
 */

#include <random>
#include <array>
#include <algorithm>
#include <cassert>

#include <iostream>

namespace NAGE
{
    template <typename T>
    class PerlinNoise;
    typedef PerlinNoise<float> FPerlinNoise;
    typedef PerlinNoise<double> DPerlinNoise;

    template <typename T>
    class PerlinNoise
    {
    public:
        struct OctaveSettings
        {
            T frequency = 1;
            T amplitude = 1;
            T persistence = 0.5;
            T lacunarity = 2;
            int octaves = 1;
        } settings;

        explicit PerlinNoise(unsigned long _seed = 0)
        {
            // First step: fill array of shuffled 0-255 values.
            for(size_t i = 0; i < 256; i++)
                mPermutationTable[i] = static_cast<uint8_t>(i);

            // Shuffle permutation array.
            std::shuffle(std::begin(mPermutationTable), std::begin(mPermutationTable) + 256, std::default_random_engine(_seed));

            // Second step: append 0-255 values.
            for(size_t i = 0; i < 256; i++)
                mPermutationTable[256 + i] = mPermutationTable[i];
        }

        // 1D, 2D and 3D noise.
        T noise(T _x)
        {
            return compute(_x, 0.0, 0.0);
        }

        T noise (T _x, T _y)
        {
            return compute(_x, _y, 0.0);
        }

        T noise (T _x, T _y, T _z)
        {
            return compute(_x, _y, _z);
        }

        /* Fractional Brownian Motion
         */
        T FBM(T _x, T _y, T _z)
        {
            assert(settings.octaves != 0);

            T total = 0;
            T amplitude = settings.amplitude;
            T frequency = settings.frequency;
            T maxValue = 0; // Normalize result to <0, 1> value.

            for(int i = 0; i < settings.octaves; i++)
            {
                total += compute(_x * frequency, _y * frequency, _z * frequency) * amplitude;
                maxValue += amplitude;

                amplitude *= settings.persistence;
                frequency *= settings.lacunarity;
            }

            return total / maxValue;
        }

    private:
        T compute (T _x, T _y, T _z)
        {
            int x = static_cast<int>(std::floor(_x)) & 255;
            int y = static_cast<int>(std::floor(_y)) & 255;
            int z = static_cast<int>(std::floor(_z)) & 255;

            _x -= std::floor(_x);
            _y -= std::floor(_y);
            _z -= std::floor(_z);

            // Compute fade curves for x, y, z.
            T u = fade(_x);
            T v = fade(_y);
            T w = fade(_z);

            // Hash coordinates.
            int A = mPermutationTable[x] + y;
            int AA = mPermutationTable[A] + z;
            int AB = mPermutationTable[A + 1] + z;
            int B = mPermutationTable[x + 1] + y;
            int BA = mPermutationTable[B] + z;
            int BB = mPermutationTable[B + 1] + z;

            // Add blended results from 8 cornerrs of cube.
            return lerp(w, lerp(v, lerp(u, grad(mPermutationTable[AA], x, y, z),
                grad(mPermutationTable[BA], x - 1, y, z)),
                lerp(u, grad(mPermutationTable[AB], x, y - 1, z),
                grad(mPermutationTable[BB], x - 1, y - 1, z))),
                lerp(v, lerp(u, grad(mPermutationTable[AA + 1], x, y, z - 1),
                grad(mPermutationTable[BA + 1], x - 1, y, z - 1)),
                lerp(u, grad(mPermutationTable[AB +1 ], x, y - 1, z - 1),
                grad(mPermutationTable[BB + 1], x - 1, y - 1, z - 1))));
        }

        constexpr T fade(T _value)
        {
            return _value * _value * _value * (_value * (_value * 6 - 15) + 10);
        }

        constexpr T lerp(T _t, T _a, T _b)
        {
            return _a + _t * (_b - _a);
        }

        constexpr T grad(uint8_t _hash, T _x, T _y, T _z)
        {
            // Convert L0 4 bits of hash code into 12 gradient directions.
            uint8_t h = _hash & 15;
            T u = h < 8 ? _x : _y;
            T v = h < 4 ? _y : h == 12 || h == 14 ? _x : _z;

            return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
        }

        std::array<uint8_t, 512> mPermutationTable; // Array of 0 - 255 values (shuffled).
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_
