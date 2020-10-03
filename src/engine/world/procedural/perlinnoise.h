#ifndef NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_
#define NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_

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


    /* Improved Perlin noise algorithm.
     *
     * https://mrl.nyu.edu/~perlin/paper445.pdf
     * https://mrl.nyu.edu/~perlin/noise/
     */
    template <typename T>
    class PerlinNoise
    {
    public:
        struct OctaveSettings
        {
            OctaveSettings(T _frequency = 1, T _amplitude = 1, T _persistence = 0.5, T _lacunarity = 2,
                T _octaves = 1)
            {
                frequency = _frequency;
                amplitude = _amplitude;
                persistence = _persistence;
                lacunarity = _lacunarity;
                octaves = _octaves;
            }

            bool operator==(const OctaveSettings& _rhs)
            {
                return (this->frequency == _rhs.frequency &&
                    this->amplitude == _rhs.amplitude &&
                    this->persistence == _rhs.persistence &&
                    this->lacunarity == _rhs.lacunarity &&
                    this->octaves == _rhs.octaves);
            }

            bool operator!=(const OctaveSettings& _rhs)
            {
                return !(*this == _rhs);
            }

            T frequency;
            T amplitude;
            T persistence;
            T lacunarity;
            int octaves;
        };

        OctaveSettings settings;

        explicit PerlinNoise(unsigned long _seed = 0)
        {
            // First step: fill array of shuffled 0-255 values.
            for(size_t i = 0; i < 256; i++)
                permutationTable_[i] = static_cast<uint8_t>(i);

            // Shuffle permutation array.
            std::shuffle(std::begin(permutationTable_), std::begin(permutationTable_) + 256, std::default_random_engine(_seed));

            // Second step: append 0-255 values.
            for(size_t i = 0; i < 256; i++)
                permutationTable_[256 + i] = permutationTable_[i];
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
            int A = permutationTable_[x] + y;
            int AA = permutationTable_[A] + z;
            int AB = permutationTable_[A + 1] + z;
            int B = permutationTable_[x + 1] + y;
            int BA = permutationTable_[B] + z;
            int BB = permutationTable_[B + 1] + z;

            // Add blended results from 8 cornerrs of cube.
            return lerp(w, lerp(v, lerp(u, grad(permutationTable_[AA], x, y, z),
                grad(permutationTable_[BA], x - 1, y, z)),
                lerp(u, grad(permutationTable_[AB], x, y - 1, z),
                grad(permutationTable_[BB], x - 1, y - 1, z))),
                lerp(v, lerp(u, grad(permutationTable_[AA + 1], x, y, z - 1),
                grad(permutationTable_[BA + 1], x - 1, y, z - 1)),
                lerp(u, grad(permutationTable_[AB +1 ], x, y - 1, z - 1),
                grad(permutationTable_[BB + 1], x - 1, y - 1, z - 1))));
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

        std::array<uint8_t, 512> permutationTable_; // Array of 0 - 255 values (shuffled).
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_PERLIN_NOISE_H_
