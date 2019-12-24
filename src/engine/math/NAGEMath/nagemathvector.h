#ifndef NAGE_NAGEMATHVECTOR_H_
#define NAGE_NAGEMATHVECTOR_H_

#include <iostream>
#include <cmath>
#include <typeinfo>

namespace NAGE
{
    // Some defined vector types (int, float, double)
    template <typename T>
    class Vector2;

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;

    template <typename T>
    class Vector3;

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<double> Vector3d;

    template <typename T>
    class Vector4;

    typedef Vector4<int> Vector4i;
    typedef Vector4<float> Vector4f;
    typedef Vector4<double> Vector4d;

    template <typename T>
    class Vector2
    {
    public:
        Vector2() : mX(0), mY(0) {}
        Vector2(T _x, T _y) : mX(_x), mY(_y) {}
        Vector2(const Vector2<T>& _rhs) { mX = _rhs.mX; mY = _rhs.mY; }

        // Overloaded operators.
        inline Vector2<T> operator+(const T& _rhs) const { return Vector2(this->mX + _rhs, this->mY + _rhs); }
        inline Vector2<T> operator+(const Vector2<T>& _rhs) const { return Vector2(this->mX + _rhs.mX, this->mY + _rhs.mY); }
        inline Vector2<T> operator-() const { return Vector2(-this->mX, -this->mY); }
        inline Vector2<T> operator-(const T& _rhs) const { return Vector2(this->mX - _rhs, this->mY - _rhs); }
        inline Vector2<T> operator-(const Vector2<T>& _rhs) const { return Vector2(this->mX - _rhs.mX, this->mY - _rhs.mY); }
        inline Vector2<T> operator*(const T& _rhs) const { return Vector2(this->mX * _rhs, this->mY * _rhs); }
        inline Vector2<T> operator/(const T& _rhs) const { return Vector2(this->mX / _rhs, this->mY / _rhs); }

        inline bool operator==(const Vector2<T>& _rhs) { return this->mX == _rhs.mX && this->mY == _rhs.mY; }
        inline bool operator!=(const Vector2<T>& _rhs) { return !(*this == _rhs); }

        inline Vector2<T>& operator=(const Vector2<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->mX = _rhs.mX;
                this->mY = _rhs.mY;
            }

            return *this;
        }

        inline Vector2<T>& operator+=(const T& _rhs)
        {
            this->mX += _rhs;
            this->mY += _rhs;

            return *this;
        }

        inline Vector2<T>& operator+=(const Vector2<T>& _rhs)
        {
            this->mX += _rhs.mX;
            this->mY += _rhs.mY;

            return *this;
        }

        inline Vector2<T>& operator-=(const T& _rhs)
        {
            this->mX -= _rhs;
            this->mY -= _rhs;

            return *this;
        }

        inline Vector2<T>& operator-=(const Vector2<T>& _rhs)
        {
            this->mX -= _rhs.mX;
            this->mY -= _rhs.mY;

            return *this;
        }

        inline Vector2<T>& operator*=(const T& _rhs)
        {
            this->mX *= _rhs;
            this->mY *= _rhs;

            return *this;
        }

        inline Vector2<T> operator/=(const T& _rhs)
        {
            this->mX /= _rhs;
            this->mY /= _rhs;

            return *this;
        }


        template <typename S>
        friend const Vector2 operator*(const T& _lhs, const Vector2& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector2<T>& _vector);

        // Operations on vector.
        inline T length() { return static_cast<T>(std::sqrt(this->mX * this->mX + this->mY * this->mY)); }
        inline T lengthSquared() { return this->mX * this->mX + this->mY * this->mY; }
        inline T max() { return (this->mX > this->mY) ? this->mX : this->mY; }
        inline T dot(const Vector2<T>& _rhs) { return this->mX * _rhs.mX + this->mY * _rhs.mY; }
        inline T cross(const Vector2<T>& _rhs) { return this->mX * _rhs.mY - this->mY * _rhs.mX; }
        inline T lerp(const Vector2<T>& _rhs, T _factor) { return (_rhs - *this) * _factor + *this; }

        inline void normalize()
        {
            T len = length();

            if(len == 0)
                return;

            this->mX /= len;
            this->mY /= len;
        }

        inline Vector2<T> normalized() const
        {
            T len = length();

            if (len != 0)
                return Vector2(this->mX / len, this->mY / len);

            return *this;
        }

        inline Vector2<T> rotate(T _angle)
        {
            double radians = static_cast<double>(toRadians(_angle));
            double c = std::cos(radians);
            double s = std::sin(radians);

            return Vector2(static_cast<T>((this->mX * c - this->mY * s)),
                static_cast<T>((this->mX * s + this->mY * c)));
        }

        // Getters and setters.
        inline void setX(T _x) { this->mX = _x; }
        inline void setY(T _y) { this->mY = _y; }
        inline T x() const { return this->mX; }
        inline T y() const { return this->mY; }

    private:
        T mX, mY;
    };

    template <typename T>
    const Vector2<T> operator*(const T& _lhs, const Vector2<T>& _rhs)
    {
        return Vector2<T>(_rhs.x() * _lhs, _rhs.y() * _lhs);
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& _out, const Vector2<T>& _vector)
    {
        _out << "Vector2<" << typeid(T).name() << ">(" << _vector.x() << ", " << _vector.y() << ")";
        return _out;
    }

    template <typename T>
    class Vector3
    {
    public:
        Vector3() : mX(0), mY(0), mZ(0) {}
        Vector3(T _x, T _y, T _z) : mX(_x), mY(_y), mZ(_z) {}
        Vector3(const Vector3& _rhs) { mX = _rhs.mX; mY = _rhs.mY; mZ = _rhs.mZ; }

        // Overloaded operators.
        inline Vector3<T> operator+(const T& _rhs) const { return Vector3(this->mX + _rhs, this->mY + _rhs, this->mZ + _rhs); }
        inline Vector3<T> operator+(const Vector3<T>& _rhs) const { return Vector3(this->mX + _rhs.mX, this->mY + _rhs.mY, this->mZ + _rhs.mZ); }
        inline Vector3<T> operator-() const { return Vector3(-this->mX, -this->mY, -this->mZ); }
        inline Vector3<T> operator-(const T& _rhs) const { return Vector3(this->mX - _rhs, this->mY - _rhs, this->mZ - _rhs); }
        inline Vector3<T> operator-(const Vector3<T>& _rhs) const { return Vector3(this->mX - _rhs.mX, this->mY - _rhs.mY, this->mZ - _rhs.mZ); }
        inline Vector3<T> operator*(const T& _rhs) const { return Vector3(this->mX * _rhs, this->mY * _rhs, this->mZ * _rhs); }
        inline Vector3<T> operator/(const T& _rhs) const { return Vector3(this->mX / _rhs, this->mY / _rhs, this->mZ / _rhs); }

        inline bool operator==(const Vector3<T>& _rhs) { return this->mX == _rhs.mX && this->mY == _rhs.mY && this->mZ == _rhs.mZ; }
        inline bool operator!=(const Vector3<T>& _rhs) { return !(*this == _rhs); }

        inline Vector3<T> operator=(const Vector3<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->mX = _rhs.mX;
                this->mY = _rhs.mY;
                this->mZ = _rhs.mZ;
            }

            return *this;
        }

        inline Vector3<T> operator+=(const T& _rhs)
        {
            this->mX += _rhs;
            this->mY += _rhs;
            this->mZ += _rhs;

            return *this;
        }

        inline Vector3<T> operator+=(const Vector3<T>& _rhs)
        {
            this->mX += _rhs.mX;
            this->mY += _rhs.mY;
            this->mZ += _rhs.mZ;

            return *this;
        }

        inline Vector3<T> operator-=(const T& _rhs)
        {
            this->mX -= _rhs;
            this->mY -= _rhs;
            this->mZ -= _rhs;

            return *this;
        }

        inline Vector3<T> operator-=(const Vector3<T>& _rhs)
        {
            this->mX -= _rhs.mX;
            this->mY -= _rhs.mY;
            this->mZ -= _rhs.mZ;

            return *this;
        }

        inline Vector3<T> operator*=(const T& _rhs)
        {
            this->mX *= _rhs;
            this->mY *= _rhs;
            this->mZ *= _rhs;

            return *this;
        }

        inline Vector3<T> operator/=(const T& _rhs)
        {
            this->mX /= _rhs;
            this->mY /= _rhs;
            this->mZ /= _rhs;

            return *this;
        }

        template <typename S>
        friend const Vector3 operator+(const T& _lhs, const Vector3& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector3& _vector);

        // Opertions on vector.
        inline T length() const { return static_cast<T>(std::sqrt(this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ)); }
        inline T lengthSquared() { return static_cast<T>(this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ); }
        inline T lerp(const Vector3& rhs, T factor) { return (rhs - *this) * factor + *this; }

        inline T max()
        {
            T m = (this->mX < this->mY) ? this->mY : this->mX;
            return ((m < this->mZ) ? this->mZ : m);
        }

        inline void normalize()
        {
            T len = length();

            if(len == 0)
                return;

            this->mX /= len;
            this->mY /= len;
            this->mZ /= len;
        }

        inline Vector3<T> normalized() const
        {
            T len = length();

            if (len != 0)
                return Vector3(this->mX / len, this->mY / len, this->mZ / len);

            return Vector3(this->mX, this->mY, this->mZ);
        }

        inline static Vector3<T> normalize(const Vector3<T>& _vector)
        {
            T len = std::sqrt(_vector.mX * _vector.mX + _vector.mY * _vector.mY
                        + _vector.mZ * _vector.mZ);

            if(len == 0)
                return _vector;

            return Vector3<T>(_vector.mX / len, _vector.mY / len, _vector.mZ / len);
        }

        inline Vector3<T> rotate(Vector3<T> _axis, T _angle)
        {
            double s = std::sin(-_angle);
            double c = std::cos(-_angle);

            return cross(_axis * s) + // local X
                (*this * c) + // local Y
                _axis * this->dot(_axis * (1 - c)); // local Z
        }

        inline T dot(const Vector3<T>& _rhs)
        {
            return this->mX * _rhs.mX + this->mY * _rhs.mY + this->mZ * _rhs.mZ;
        }

        inline static T dot(const Vector3<T>& _lhs, const Vector3<T>& _rhs)
        {
            return _lhs.mX * _rhs.mX + _lhs.mY * _rhs.mY + _lhs.mZ * _rhs.mZ;
        }

        inline Vector3<T> cross(const Vector3<T>& _rhs)
        {
            const T x = this->mY * _rhs.mZ - _rhs.mY * this->mZ;
            const T y = this->mZ * _rhs.mX - _rhs.mZ * this->mX;
            const T z = this->mX * _rhs.mY - _rhs.mX * this->mY;
        }

        inline static Vector3<T> cross(const Vector3<T>& _lhs, const Vector3<T>& _rhs)
        {
            const T x = _lhs.y() * _rhs.z() - _rhs.y() * _lhs.z();
            const T y = _lhs.z() * _rhs.x() - _rhs.z() * _lhs.x();
            const T z = _lhs.x() * _rhs.y() - _rhs.x() * _lhs.y();

            return Vector3(x, y, z);
        }

        // Getters and setters.
        inline void setX(T _x) { this->mX = _x; }
        inline void setY(T _y) { this->mY = _y; }
        inline void setZ(T _z) { this->mZ = _z; }
        inline T x() const { return this->mX; }
        inline T y() const { return this->mY; }
        inline T z() const { return this->mZ; }

        // Static members
        static Vector3<T> forward;
        static Vector3<T> up;
        static Vector3<T> right;

    private:
        T mX, mY, mZ;
    };

    // Static member initialization.
    template <typename T> Vector3<T> Vector3<T>::forward = Vector3<T>(0.0f, 0.0f, 1.0f);
    template <typename T> Vector3<T> Vector3<T>::up = Vector3<T>(0.0f, 1.0f, 0.0f);
    template <typename T> Vector3<T> Vector3<T>::right = Vector3<T>(1.0f, 0.0f, 0.0f);

    // Friend functions.
    template <typename T>
    const Vector3<T> operator*(const T& _lhs, const Vector3<T>& _rhs)
    {
        return Vector3<T>(_rhs.x() * _lhs, _rhs.y() * _lhs, _rhs.z() * _lhs);
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& _out, const Vector3<T>& _vector)
    {
        _out << "Vector3<" << typeid(T).name() << ">(" << _vector.x() << ", "
            << _vector.y() << ", " << _vector.z() << ")" << std::endl;

        return _out;
    }

    template <typename T>
    class Vector4
    {
    public:
        Vector4() : mX(0), mY(0), mZ(0), mW(0) {}
        Vector4(T _x, T _y, T _z, T _w) : mX(_x), mY(_y), mZ(_z), mW(_w) {}
        Vector4(const Vector4& _rhs) { mX = _rhs.mX; mY = _rhs.mY; mZ = _rhs.mZ; mW = _rhs.mW; }

        // Overloaded operators.
        inline Vector4<T> operator+(const T& _rhs) const { return Vector4(this->mX + _rhs, this->mY + _rhs, this->mZ + _rhs, this->mW + _rhs); }
        inline Vector4<T> operator+(const Vector4<T>& _rhs) const { return Vector4(this->mX + _rhs.mX, this->mY + _rhs.mY, this->mZ + _rhs.mZ, this-mW + _rhs.mW); }
        inline Vector4<T> operator-() const { return Vector3(-this->mX, -this->mY, -this->mZ, -this->mW); }
        inline Vector4<T> operator-(const T& _rhs) const { return Vector4(this->mX - _rhs, this->mY - _rhs, this->mZ - _rhs, this->mW - _rhs); }
        inline Vector4<T> operator-(const Vector3<T>& _rhs) const { return Vector4(this->mX - _rhs.mX, this->mY - _rhs.mY, this->mZ - _rhs.mZ, this->mW - _rhs.mW); }
        inline Vector4<T> operator*(const T& _rhs) const { return Vector4(this->mX * _rhs, this->mY * _rhs, this->mZ * _rhs, this->mW * _rhs); }
        inline Vector4<T> operator/(const T& _rhs) const { return Vector4(this->mX / _rhs, this->mY / _rhs, this->mZ / _rhs, this->mW / _rhs); }

        inline bool operator==(const Vector4<T>& _rhs) { return this->mX == _rhs.mX && this->mY == _rhs.mY && this->mZ == _rhs.mZ && this->mW == _rhs.mW; }
        inline bool operator!=(const Vector4<T>& _rhs) { return !(*this == _rhs); }

        inline Vector4<T> operator=(const Vector4<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->mX = _rhs.mX;
                this->mY = _rhs.mY;
                this->mZ = _rhs.mZ;
                this->mW = _rhs.mW;
            }

            return *this;
        }

        inline Vector4<T> operator+=(const T& _rhs)
        {
            this->mX += _rhs;
            this->mY += _rhs;
            this->mZ += _rhs;
            this->mW += _rhs;

            return *this;
        }

        inline Vector4<T> operator+=(const Vector4<T>& _rhs)
        {
            this->mX += _rhs.mX;
            this->mY += _rhs.mY;
            this->mZ += _rhs.mZ;
            this->mW += _rhs.mW;

            return *this;
        }

        inline Vector4<T> operator-=(const T& _rhs)
        {
            this->mX -= _rhs;
            this->mY -= _rhs;
            this->mZ -= _rhs;
            this->mW -= _rhs;

            return *this;
        }

        inline Vector4<T> operator-=(const Vector4<T>& _rhs)
        {
            this->mX -= _rhs.mX;
            this->mY -= _rhs.mY;
            this->mZ -= _rhs.mZ;
            this->mW -= _rhs.mW;

            return *this;
        }

        inline Vector4<T> operator*=(const T& _rhs)
        {
            this->mX *= _rhs;
            this->mY *= _rhs;
            this->mZ *= _rhs;
            this->mW *= _rhs;

            return *this;
        }

        inline Vector4<T> operator/=(const T& _rhs)
        {
            this->mX /= _rhs;
            this->mY /= _rhs;
            this->mZ /= _rhs;
            this->mW /= _rhs;

            return *this;
        }

        template <typename S>
        friend const Vector4 operator+(const T& _lhs, const Vector4& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector4& _vector);

        // Getters and setters.
        inline void setX(T _x) { this->mX = _x; }
        inline void setY(T _y) { this->mY = _y; }
        inline void setZ(T _z) { this->mZ = _z; }
        inline void setW(T _w) { this->mW = _w; }
        inline T x() const { return this->mX; }
        inline T y() const { return this->mY; }
        inline T z() const { return this->mZ; }
        inline T w() const { return this->mW; }

    private:
        T mX, mY, mZ, mW;
    };

    // Friend functions.
    template <typename T>
    const Vector4<T> operator*(const T& _lhs, const Vector4<T>& _rhs)
    {
        return Vector4<T>(_rhs.x() * _lhs, _rhs.y() * _lhs, _rhs.z() * _lhs, _rhs.w() * _lhs);
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& _out, const Vector4<T>& _vector)
    {
        _out << "Vector4<" << typeid(T).name() << ">(" << _vector.x() << ", "
            << _vector.y() << ", " << _vector.z() << ", " << _vector.mW << ")" << std::endl;

        return _out;
    }
}

#endif // NAGE_NAGEMATHVECTOR_H_
