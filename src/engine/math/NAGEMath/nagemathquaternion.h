#ifndef NAGE_MATH_NAGEMATHQUATERNION_H_
#define NAGE_MATH_NAGEMATHQUATERNION_H_

#include "nagemathcommon.h"
#include "nagemathvector.h"

namespace mr::nage
{
    class Quaternion
    {
    public:
        Quaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f)
            : x_(_x), y_(_y), z_(_z), w_(_w) {}
        Quaternion(const Vector3f& _vector, float _scalar)
            : x_(_vector.x()), y_(_vector.y()), z_(_vector.z()), w_(_scalar) {}

        inline Quaternion& operator+=(const Quaternion& _quaternion)
        {
            this->x_ += _quaternion.x_;
            this->y_ += _quaternion.y_;
            this->z_ += _quaternion.z_;
            this->w_ += _quaternion.w_;

            return *this;
        }

        inline Quaternion& operator-=(const Quaternion& _quaternion)
        {
            this->x_ -= _quaternion.x_;
            this->y_ -= _quaternion.y_;
            this->z_ -= _quaternion.z_;
            this->w_ -= _quaternion.w_;

            return *this;
        }

        inline Quaternion& operator*=(float _factor)
        {
            this->x_ *= _factor;
            this->y_ *= _factor;
            this->z_ *= _factor;
            this->w_ *= _factor;

            return *this;
        }

        inline Quaternion& operator*=(const Quaternion& _quaternion)
        {
            *this = *this * _quaternion;
            return *this;
        }

        inline Quaternion& operator/=(float _divisor)
        {
            this->x_ /= _divisor;
            this->y_ /= _divisor;
            this->z_ /= _divisor;
            this->w_ /= _divisor;

            return *this;
        }

        inline bool operator==(const Quaternion& _rhs) const
        {
            return nage_floatCompare(this->x_, _rhs.x_) && nage_floatCompare(this->y_, _rhs.y_)
                && nage_floatCompare(this->z_, _rhs.z_) && nage_floatCompare(this->w_, _rhs.w_);
        }

        inline bool operator!=(const Quaternion& _rhs) const
        {
            return !operator==(_rhs);
        }

        inline Quaternion operator+(const Quaternion& _rhs) const
        {
            return Quaternion(this->x_ + _rhs.x_, this->y_ + _rhs.y_, this->z_ + _rhs.z_,
                this->w_ + _rhs.w_);
        }

        inline Quaternion operator-(const Quaternion& _rhs) const
        {
            return Quaternion(this->x_ - _rhs.x_, this->y_ - _rhs.y_, this->z_ - _rhs.z_,
                this->w_ - _rhs.w_);
        }

        inline const Quaternion operator-() const
        {
            return Quaternion(-this->x_, -this->y_, -this->z_, -this->w_);
        }

        inline Vector3f operator*(const Vector3f& _vector) const
        {
            return rotatedVector(_vector);
        }

        inline const Quaternion operator*(const Quaternion& _rhs) const
        {
            float w = w_ * _rhs.w_ - x_ * _rhs.x_ - y_ * _rhs.y_ - z_ * _rhs.z_;
            float x = w_ * _rhs.x_ + x_ * _rhs.w_ + y_ * _rhs.z_ - z_ * _rhs.y_;
            float y = w_ * _rhs.y_ + y_ * _rhs.w_ + z_ * _rhs.x_ - x_ * _rhs.z_;
            float z = w_ * _rhs.z_ + z_ * _rhs.w_ + x_ * _rhs.y_ - y_ * _rhs.x_;

            return Quaternion(x, y, z, w);
        }

        friend inline const Quaternion operator*(float _factor, const Quaternion& _quaternion);
        friend inline const Quaternion operator*(const Quaternion& _quaternion, float _factor);
        friend inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor);
        friend inline std::ostream& operator<< (std::ostream& _out, const Quaternion& _quaternion);

        inline bool isNull() const
        {
            return this->x_ == 0.0f && this->y_ == 0.0f && this->z_ == 0.0f && this->w_ == 0.0f;
        }

        inline bool isIdentity() const
        {
            return this->x_ == 0.0f && this->y_ == 0.0f && this->z_ == 0.0f && this->w_ == 1.0f;
        }

        inline float length() const
        {
            return std::sqrt(this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_ + this->w_ * this->w_);
        }

        inline float lengthSquared() const
        {
            return this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_ + this->w_ * this->w_;
        }

        inline void normalize()
        {
            double x = static_cast<double>(this->x_);
            double y = static_cast<double>(this->y_);
            double z = static_cast<double>(this->z_);
            double w = static_cast<double>(this->w_);

            double len = std::sqrt(x * x + y * y + z * z + w * w);

            if(!nage_doubleCompare(len, 0.0))
            {
                this->x_ /= static_cast<float>(len);
                this->y_ /= static_cast<float>(len);
                this->z_ /= static_cast<float>(len);
                this->w_ /= static_cast<float>(len);
            }
        }

        inline Quaternion normalized() const
        {
            double x = static_cast<double>(this->x_);
            double y = static_cast<double>(this->y_);
            double z = static_cast<double>(this->z_);
            double w = static_cast<double>(this->w_);

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
            return Quaternion(-this->x_, -this->y_, -this->z_, this->w_);
        }

        inline Quaternion inverted() const
        {
            float len = x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;

            if(!nage_floatCompare(len, 0.0))
            {
                return Quaternion(-this->x_ / len, -this->y_ / len,
                    -this->z_ / len, this->w_ / len);
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
            return _quaternion1.x_ * _quaternion2.x_ + _quaternion1.y_ * _quaternion2.y_
                + _quaternion1.z_ * _quaternion2.z_ + _quaternion1.w_ * _quaternion2.w_;
        }

        inline void getAxisAndAngle(float* _x, float* _y, float* _z, float* _angle) const
        {
            assert(_x && _y && _z && _angle);

            float len = this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_;
            if(!nage_floatCompare(len, 0.0f))
            {
                *_x = this->x_;
                *_y = this->y_;
                *_z = this->z_;

                *_x /= len;
                *_y /= len;
                *_z /= len;

                *_angle = 2.0f * std::acos(w_);
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

        inline void setX(float _x) { this->x_ = _x; }
        inline void setY(float _y) { this->y_ = _y; }
        inline void setZ(float _z) { this->z_ = _z; }
        inline void setW(float _w) { this->w_ = _w; }
        inline void setVector(float _x, float _y, float _z) { this->x_ = _x; this->y_ = _y; this->z_ = _z; }

        inline float x() const { return this->x_; }
        inline float y() const { return this->y_; }
        inline float z() const { return this->z_; }
        inline float w() const { return this->w_; }
        inline Vector3f vector() const { return Vector3f(this->x_, this->y_, this->z_); }

    private:
        float x_, y_, z_, w_;
    };

    inline const Quaternion operator*(float _factor, const Quaternion& _quaternion)
    {
        return Quaternion(_quaternion.x_ * _factor, _quaternion.y_ * _factor, _quaternion.z_ * _factor,
            _quaternion.w_ * _factor);
    }

    inline const Quaternion operator*(const Quaternion& _quaternion, float _factor)
    {
        return Quaternion(_quaternion.x_ * _factor, _quaternion.y_ * _factor, _quaternion.z_ * _factor,
            _quaternion.w_ * _factor);
    }

    inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor)
    {
        return Quaternion(_quaternion.x_ / _divisor, _quaternion.y_ / _divisor, _quaternion.z_ / _divisor,
            _quaternion.w_ / _divisor);
    }

    inline std::ostream& operator<<(std::ostream& _out, const Quaternion& _quaternion)
    {
        _out << "Quaternion(" << _quaternion.x() << ", " << _quaternion.y() << ", "
            << _quaternion.z() << ", " << _quaternion.w() << ")" << std::endl;

        return _out;
    }
}

#endif // NAGE_MATH_NAGEMATHQUATERNION_H_
