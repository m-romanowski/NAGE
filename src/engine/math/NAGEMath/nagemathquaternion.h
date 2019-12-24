#ifndef NAGEMATHQUATERNION_H
#define NAGEMATHQUATERNION_H

#include "nagemathcommon.h"
#include "nagemathvector.h"

namespace NAGE
{
    class Quaternion
    {
    public:
        Quaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f)
            : mX(_x), mY(_y), mZ(_z), mW(_w) {}
        Quaternion(const Vector3f& _vector, float _scalar)
            : mX(_vector.x()), mY(_vector.y()), mZ(_vector.z()), mW(_scalar) {}

        inline Quaternion& operator+=(const Quaternion& _quaternion)
        {
            this->mX += _quaternion.mX;
            this->mY += _quaternion.mY;
            this->mZ += _quaternion.mZ;
            this->mW += _quaternion.mW;

            return *this;
        }

        inline Quaternion& operator-=(const Quaternion& _quaternion)
        {
            this->mX -= _quaternion.mX;
            this->mY -= _quaternion.mY;
            this->mZ -= _quaternion.mZ;
            this->mW -= _quaternion.mW;

            return *this;
        }

        inline Quaternion& operator*=(float _factor)
        {
            this->mX *= _factor;
            this->mY *= _factor;
            this->mZ *= _factor;
            this->mW *= _factor;

            return *this;
        }

        inline Quaternion& operator*=(const Quaternion& _quaternion)
        {
            *this = *this * _quaternion;
            return *this;
        }

        inline Quaternion& operator/=(float _divisor)
        {
            this->mX /= _divisor;
            this->mY /= _divisor;
            this->mZ /= _divisor;
            this->mW /= _divisor;

            return *this;
        }

        inline bool operator==(const Quaternion& _rhs) const
        {
            return nage_floatCompare(this->mX, _rhs.mX) && nage_floatCompare(this->mY, _rhs.mY)
                && nage_floatCompare(this->mZ, _rhs.mZ) && nage_floatCompare(this->mW, _rhs.mW);
        }

        inline bool operator!=(const Quaternion& _rhs) const
        {
            return !operator==(_rhs);
        }

        inline Quaternion operator+(const Quaternion& _rhs) const
        {
            return Quaternion(this->mX + _rhs.mX, this->mY + _rhs.mY, this->mZ + _rhs.mZ,
                this->mW + _rhs.mW);
        }

        inline Quaternion operator-(const Quaternion& _rhs) const
        {
            return Quaternion(this->mX - _rhs.mX, this->mY - _rhs.mY, this->mZ - _rhs.mZ,
                this->mW - _rhs.mW);
        }

        inline const Quaternion operator-() const
        {
            return Quaternion(-this->mX, -this->mY, -this->mZ, -this->mW);
        }

        inline Vector3f operator*(const Vector3f& _vector) const
        {
            return rotatedVector(_vector);
        }

        inline const Quaternion operator*(const Quaternion& _rhs) const
        {
            float w = mW * _rhs.mW - mX * _rhs.mX - mY * _rhs.mY - mZ * _rhs.mZ;
            float x = mW * _rhs.mX + mX * _rhs.mW + mY * _rhs.mZ - mZ * _rhs.mY;
            float y = mW * _rhs.mY + mY * _rhs.mW + mZ * _rhs.mX - mX * _rhs.mZ;
            float z = mW * _rhs.mZ + mZ * _rhs.mW + mX * _rhs.mY - mY * _rhs.mX;

            return Quaternion(x, y, z, w);
        }

        friend inline const Quaternion operator*(float _factor, const Quaternion& _quaternion);
        friend inline const Quaternion operator*(const Quaternion& _quaternion, float _factor);
        friend inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor);
        friend inline std::ostream& operator<< (std::ostream& _out, const Quaternion& _quaternion);

        inline bool isNull() const
        {
            return this->mX == 0.0f && this->mY == 0.0f && this->mZ == 0.0f && this->mW == 0.0f;
        }

        inline bool isIdentity() const
        {
            return this->mX == 0.0f && this->mY == 0.0f && this->mZ == 0.0f && this->mW == 1.0f;
        }

        inline float length() const
        {
            return std::sqrt(this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ + this->mW * this->mW);
        }

        inline float lengthSquared() const
        {
            return this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ + this->mW * this->mW;
        }

        inline void normalize()
        {
            double x = static_cast<double>(this->mX);
            double y = static_cast<double>(this->mY);
            double z = static_cast<double>(this->mZ);
            double w = static_cast<double>(this->mW);

            double len = std::sqrt(x * x + y * y + z * z + w * w);

            if(!nage_doubleCompare(len, 0.0))
            {
                this->mX /= static_cast<float>(len);
                this->mY /= static_cast<float>(len);
                this->mZ /= static_cast<float>(len);
                this->mW /= static_cast<float>(len);
            }
        }

        inline Quaternion normalized() const
        {
            double x = static_cast<double>(this->mX);
            double y = static_cast<double>(this->mY);
            double z = static_cast<double>(this->mZ);
            double w = static_cast<double>(this->mW);

            double len = std::sqrt(x * x + y * y + z * z + w * w);

            if(!nage_doubleCompare(len, 0.0))
                return *this / static_cast<float>(len);

            return *this;
        }

        inline Quaternion conjugate() const
        {
            return conjugated();
        }

        inline Quaternion conjugated() const
        {            
            return Quaternion(-this->mX, -this->mY, -this->mZ, this->mW);
        }

        inline Quaternion inverted() const
        {
            float len = mX * mX + mY * mY + mZ * mZ + mW * mW;

            if(!nage_floatCompare(len, 0.0))
            {
                return Quaternion(-this->mX / len, -this->mY / len,
                    -this->mZ / len, this->mW / len);
            }

            return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
        }

        // https://gamedev.stackexchange.com/a/50545
        inline Vector3f rotatedVector(const Vector3f& _vector) const
        {
            Quaternion quatV(_vector, 0.0f);
            Quaternion quatMult = (*this) * quatV * (*this).conjugated();

            return quatMult.vector();
        }

        static inline float dotProduct(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
        {
            return _quaternion1.mX * _quaternion2.mX + _quaternion1.mY * _quaternion2.mY
                + _quaternion1.mZ * _quaternion2.mZ + _quaternion1.mW * _quaternion2.mW;
        }

        inline void getAxisAndAngle(float* _x, float* _y, float* _z, float* _angle) const
        {
            assert(_x && _y && _z && _angle);

            float len = this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ;
            if(!nage_floatCompare(len, 0.0f))
            {
                *_x = this->mX;
                *_y = this->mY;
                *_z = this->mZ;

                *_x /= len;
                *_y /= len;
                *_z /= len;

                *_angle = 2.0f * std::acos(mW);
            }
            else
            {
                *_x = *_y = *_z = *_angle = 0.0f;
            }

            *_angle = nage_toDegrees(*_angle);
        }

        inline void getAxisAndAngle(Vector3f* _axis, float* _angle) const
        {
            float x, y, z;
            getAxisAndAngle(&x, &y, &z, _angle);
            *_axis = Vector3f(x, y, z);
        }

        // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q56
        static inline Quaternion fromAxisAndAngle(float _angle, float _x, float _y, float _z)
        {
            float len = std::sqrt(_x * _x + _y * _y + _z * _z);

            if(!nage_floatCompare(len, 0.0f))
            {
                _x /= len;
                _y /= len;
                _z /= len;
            }

            float a = nage_toRadians(_angle / 2.0f);
            float s = std::sin(a);
            float c = std::sin(a);

            return Quaternion(_x * s, _y * s, _z * s, c).normalized();
        }

        // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q56
        static inline Quaternion fromAxisAndAngle(float _angle, const Vector3f& _axis)
        {
            Vector3f ax = _axis.normalized();

            float a = nage_toRadians(_angle / 2.0f);
            float s = std::sin(a);
            float c = std::cos(a);

            return Quaternion(ax.x() * s, ax.y() * s, ax.z() * s, c).normalized();
        }

        inline void setX(float _x) { this->mX = _x; }
        inline void setY(float _y) { this->mY = _y; }
        inline void setZ(float _z) { this->mZ = _z; }
        inline void setW(float _w) { this->mW = _w; }
        inline void setVector(float _x, float _y, float _z) { this->mX = _x; this->mY = _y; this->mZ = _z; }

        inline float x() const { return this->mX; }
        inline float y() const { return this->mY; }
        inline float z() const { return this->mZ; }
        inline float w() const { return this->mW; }
        inline Vector3f vector() const { return Vector3f(this->mX, this->mY, this->mZ); }

    private:
        float mX, mY, mZ, mW;
    };

    inline const Quaternion operator*(float _factor, const Quaternion& _quaternion)
    {
        return Quaternion(_quaternion.mX * _factor, _quaternion.mY * _factor, _quaternion.mZ * _factor,
            _quaternion.mW * _factor);
    }

    inline const Quaternion operator*(const Quaternion& _quaternion, float _factor)
    {
        return Quaternion(_quaternion.mX * _factor, _quaternion.mY * _factor, _quaternion.mZ * _factor,
            _quaternion.mW * _factor);
    }

    inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor)
    {
        return Quaternion(_quaternion.mX / _divisor, _quaternion.mY / _divisor, _quaternion.mZ / _divisor,
            _quaternion.mW / _divisor);
    }

    inline std::ostream& operator<<(std::ostream& _out, const Quaternion& _quaternion)
    {
        _out << "Quaternion(" << _quaternion.x() << ", " << _quaternion.y() << ", "
            << _quaternion.z() << ", " << _quaternion.w() << ")" << std::endl;

        return _out;
    }
}

#endif // NAGEMATHQUATERNION_H
