#ifndef NAGE_MATH_NAGEMATHVECTOR_H_
#define NAGE_MATH_NAGEMATHVECTOR_H_

#include <iostream>
#include <cmath>
#include <typeinfo>

namespace mr::nage
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
        Vector2() : x_(0), y_(0) {}
        Vector2(T _x, T _y) : x_(_x), y_(_y) {}
        Vector2(const Vector2<T>& _rhs) { x_ = _rhs.x_; y_ = _rhs.y_; }

        // Overloaded operators.
        inline Vector2<T> operator+(const T& _rhs) const { return Vector2(this->x_ + _rhs, this->y_ + _rhs); }
        inline Vector2<T> operator+(const Vector2<T>& _rhs) const { return Vector2(this->x_ + _rhs.x_, this->y_ + _rhs.y_); }
        inline Vector2<T> operator-() const { return Vector2(-this->x_, -this->y_); }
        inline Vector2<T> operator-(const T& _rhs) const { return Vector2(this->x_ - _rhs, this->y_ - _rhs); }
        inline Vector2<T> operator-(const Vector2<T>& _rhs) const { return Vector2(this->x_ - _rhs.x_, this->y_ - _rhs.y_); }
        inline Vector2<T> operator*(const T& _rhs) const { return Vector2(this->x_ * _rhs, this->y_ * _rhs); }
        inline Vector2<T> operator/(const T& _rhs) const { return Vector2(this->x_ / _rhs, this->y_ / _rhs); }

        inline bool operator==(const Vector2<T>& _rhs) { return this->x_ == _rhs.x_ && this->y_ == _rhs.y_; }
        inline bool operator!=(const Vector2<T>& _rhs) { return !(*this == _rhs); }

        inline Vector2<T>& operator=(const Vector2<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->x_ = _rhs.x_;
                this->y_ = _rhs.y_;
            }

            return *this;
        }

        inline Vector2<T>& operator+=(const T& _rhs)
        {
            this->x_ += _rhs;
            this->y_ += _rhs;

            return *this;
        }

        inline Vector2<T>& operator+=(const Vector2<T>& _rhs)
        {
            this->x_ += _rhs.x_;
            this->y_ += _rhs.y_;

            return *this;
        }

        inline Vector2<T>& operator-=(const T& _rhs)
        {
            this->x_ -= _rhs;
            this->y_ -= _rhs;

            return *this;
        }

        inline Vector2<T>& operator-=(const Vector2<T>& _rhs)
        {
            this->x_ -= _rhs.x_;
            this->y_ -= _rhs.y_;

            return *this;
        }

        inline Vector2<T>& operator*=(const T& _rhs)
        {
            this->x_ *= _rhs;
            this->y_ *= _rhs;

            return *this;
        }

        inline Vector2<T> operator/=(const T& _rhs)
        {
            this->x_ /= _rhs;
            this->y_ /= _rhs;

            return *this;
        }


        template <typename S>
        friend const Vector2 operator*(const T& _lhs, const Vector2& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector2<T>& _vector);

        // Operations on vector.
        inline T length() { return static_cast<T>(std::sqrt(this->x_ * this->x_ + this->y_ * this->y_)); }
        inline T lengthSquared() { return this->x_ * this->x_ + this->y_ * this->y_; }
        inline T max() { return (this->x_ > this->y_) ? this->x_ : this->y_; }
        inline T cross(const Vector2<T>& _rhs) { return this->x_ * _rhs.y_ - this->y_ * _rhs.x_; }
        inline T lerp(const Vector2<T>& _rhs, T _factor) { return (_rhs - *this) * _factor + *this; }

        inline void normalize()
        {
            T len = length();

            if(len == 0)
                return;

            this->x_ /= len;
            this->y_ /= len;
        }

        inline Vector2<T> normalized() const
        {
            T len = length();

            if (len != 0)
                return Vector2(this->x_ / len, this->y_ / len);

            return *this;
        }

        inline Vector2<T> rotate(T _angle)
        {
            double radians = static_cast<double>(toRadians(_angle));
            double c = std::cos(radians);
            double s = std::sin(radians);

            return Vector2(static_cast<T>((this->x_ * c - this->y_ * s)),
                static_cast<T>((this->x_ * s + this->y_ * c)));
        }

        inline T dot(const Vector2<T>& _rhs)
        {
            return this->x_ * _rhs.x_ + this->y_ * _rhs.y_;
        }

        inline static T dot(const Vector2<T>& _lhs, const Vector2<T>& _rhs)
        {
            return _lhs.x_ * _rhs.x_ + _lhs.y_ * _rhs.y_;
        }

        inline Vector2<T> abs()
        {
            return Vector2(std::abs(x_), std::abs(y_));
        }

        inline static Vector2<T> abs(const Vector2<T>& _rhs)
        {
            return Vector2(std::abs(_rhs.x_), std::abs(_rhs.y_));
        }

        // Getters and setters.
        inline void setX(T _x) { this->x_ = _x; }
        inline void setY(T _y) { this->y_ = _y; }
        inline T x() const { return this->x_; }
        inline T y() const { return this->y_; }

        // Static members
        static Vector2<T> zero;
        static Vector2<T> one;

    private:
        T x_, y_;
    };

    // Static members initialization.
    template <typename T> Vector2<T> Vector2<T>::zero = Vector2<T>(0, 0);
    template <typename T> Vector2<T> Vector2<T>::one = Vector2<T>(1, 1);

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
        Vector3() : x_(0), y_(0), z_(0) {}
        Vector3(T _x, T _y, T _z) : x_(_x), y_(_y), z_(_z) {}
        Vector3(const Vector3& _rhs) { x_ = _rhs.x_; y_ = _rhs.y_; z_ = _rhs.z_; }

        // Overloaded operators.
        inline Vector3<T> operator+(const T& _rhs) const { return Vector3(this->x_ + _rhs, this->y_ + _rhs, this->z_ + _rhs); }
        inline Vector3<T> operator+(const Vector3<T>& _rhs) const { return Vector3(this->x_ + _rhs.x_, this->y_ + _rhs.y_, this->z_ + _rhs.z_); }
        inline Vector3<T> operator-() const { return Vector3(-this->x_, -this->y_, -this->z_); }
        inline Vector3<T> operator-(const T& _rhs) const { return Vector3(this->x_ - _rhs, this->y_ - _rhs, this->z_ - _rhs); }
        inline Vector3<T> operator-(const Vector3<T>& _rhs) const { return Vector3(this->x_ - _rhs.x_, this->y_ - _rhs.y_, this->z_ - _rhs.z_); }
        inline Vector3<T> operator*(const T& _rhs) const { return Vector3(this->x_ * _rhs, this->y_ * _rhs, this->z_ * _rhs); }
        inline Vector3<T> operator/(const T& _rhs) const { return Vector3(this->x_ / _rhs, this->y_ / _rhs, this->z_ / _rhs); }

        inline bool operator==(const Vector3<T>& _rhs) { return this->x_ == _rhs.x_ && this->y_ == _rhs.y_ && this->z_ == _rhs.z_; }
        inline bool operator!=(const Vector3<T>& _rhs) { return !(*this == _rhs); }

        inline Vector3<T> operator=(const Vector3<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->x_ = _rhs.x_;
                this->y_ = _rhs.y_;
                this->z_ = _rhs.z_;
            }

            return *this;
        }

        inline Vector3<T> operator+=(const T& _rhs)
        {
            this->x_ += _rhs;
            this->y_ += _rhs;
            this->z_ += _rhs;

            return *this;
        }

        inline Vector3<T> operator+=(const Vector3<T>& _rhs)
        {
            this->x_ += _rhs.x_;
            this->y_ += _rhs.y_;
            this->z_ += _rhs.z_;

            return *this;
        }

        inline Vector3<T> operator-=(const T& _rhs)
        {
            this->x_ -= _rhs;
            this->y_ -= _rhs;
            this->z_ -= _rhs;

            return *this;
        }

        inline Vector3<T> operator-=(const Vector3<T>& _rhs)
        {
            this->x_ -= _rhs.x_;
            this->y_ -= _rhs.y_;
            this->z_ -= _rhs.z_;

            return *this;
        }

        inline Vector3<T> operator*=(const T& _rhs)
        {
            this->x_ *= _rhs;
            this->y_ *= _rhs;
            this->z_ *= _rhs;

            return *this;
        }

        inline Vector3<T> operator/=(const T& _rhs)
        {
            this->x_ /= _rhs;
            this->y_ /= _rhs;
            this->z_ /= _rhs;

            return *this;
        }

        template <typename S>
        friend const Vector3 operator+(const T& _lhs, const Vector3& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector3& _vector);

        // Opertions on vector.
        inline T length() const { return static_cast<T>(std::sqrt(this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_)); }
        inline T lengthSquared() { return static_cast<T>(this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_); }
        inline T lerp(const Vector3& rhs, T factor) { return (rhs - *this) * factor + *this; }

        inline T max()
        {
            T m = (this->x_ < this->y_) ? this->y_ : this->x_;
            return ((m < this->z_) ? this->z_ : m);
        }

        inline void normalize()
        {
            T len = length();

            if(len == 0)
                return;

            this->x_ /= len;
            this->y_ /= len;
            this->z_ /= len;
        }

        inline Vector3<T> normalized() const
        {
            T len = length();

            if (len != 0)
                return Vector3(this->x_ / len, this->y_ / len, this->z_ / len);

            return Vector3(this->x_, this->y_, this->z_);
        }

        inline static Vector3<T> normalize(const Vector3<T>& _vector)
        {
            T len = std::sqrt(_vector.x_ * _vector.x_ + _vector.y_ * _vector.y_
                        + _vector.z_ * _vector.z_);

            if(len == 0)
                return _vector;

            return Vector3<T>(_vector.x_ / len, _vector.y_ / len, _vector.z_ / len);
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
            return this->x_ * _rhs.x_ + this->y_ * _rhs.y_ + this->z_ * _rhs.z_;
        }

        inline static T dot(const Vector3<T>& _lhs, const Vector3<T>& _rhs)
        {
            return _lhs.x_ * _rhs.x_ + _lhs.y_ * _rhs.y_ + _lhs.z_ * _rhs.z_;
        }

        inline Vector3<T> cross(const Vector3<T>& _rhs)
        {
            const T x = this->y_ * _rhs.z_ - _rhs.y_ * this->z_;
            const T y = this->z_ * _rhs.x_ - _rhs.z_ * this->x_;
            const T z = this->x_ * _rhs.y_ - _rhs.x_ * this->y_;

            return Vector3(x, y, z);
        }

        inline static Vector3<T> cross(const Vector3<T>& _lhs, const Vector3<T>& _rhs)
        {
            const T x = _lhs.y() * _rhs.z() - _rhs.y() * _lhs.z();
            const T y = _lhs.z() * _rhs.x() - _rhs.z() * _lhs.x();
            const T z = _lhs.x() * _rhs.y() - _rhs.x() * _lhs.y();

            return Vector3(x, y, z);
        }

        inline Vector3<T> abs()
        {
            return Vector3(std::abs(x_), std::abs(y_), std::abs(z_));
        }

        inline static Vector3<T> abs(const Vector3<T>& _rhs)
        {
            return Vector3(std::abs(_rhs.x_), std::abs(_rhs.y_), std::abs(_rhs.z_));
        }

        // Getters and setters.
        inline void setX(T _x) { this->x_ = _x; }
        inline void setY(T _y) { this->y_ = _y; }
        inline void setZ(T _z) { this->z_ = _z; }
        inline T x() const { return this->x_; }
        inline T y() const { return this->y_; }
        inline T z() const { return this->z_; }

        // Static members
        static Vector3<T> zero;
        static Vector3<T> one;
        static Vector3<T> forward;
        static Vector3<T> up;
        static Vector3<T> right;

    private:
        T x_, y_, z_;
    };

    // Static member initialization.
    template <typename T> Vector3<T> Vector3<T>::zero = Vector3<T>(0, 0, 0);
    template <typename T> Vector3<T> Vector3<T>::one = Vector3<T>(1, 1, 1);
    template <typename T> Vector3<T> Vector3<T>::forward = Vector3<T>(0, 0, 1);
    template <typename T> Vector3<T> Vector3<T>::up = Vector3<T>(0, 1, 0);
    template <typename T> Vector3<T> Vector3<T>::right = Vector3<T>(1, 0, 0);

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
        Vector4() : x_(0), y_(0), z_(0), w_(0) {}
        Vector4(T _x, T _y, T _z, T _w) : x_(_x), y_(_y), z_(_z), w_(_w) {}
        Vector4(const Vector4& _rhs) { x_ = _rhs.x_; y_ = _rhs.y_; z_ = _rhs.z_; w_ = _rhs.w_; }

        // Overloaded operators.
        inline Vector4<T> operator+(const T& _rhs) const { return Vector4(this->x_ + _rhs, this->y_ + _rhs, this->z_ + _rhs, this->w_ + _rhs); }
        inline Vector4<T> operator+(const Vector4<T>& _rhs) const { return Vector4(this->x_ + _rhs.x_, this->y_ + _rhs.y_, this->z_ + _rhs.z_, this-w_ + _rhs.w_); }
        inline Vector4<T> operator-() const { return Vector3(-this->x_, -this->y_, -this->z_, -this->w_); }
        inline Vector4<T> operator-(const T& _rhs) const { return Vector4(this->x_ - _rhs, this->y_ - _rhs, this->z_ - _rhs, this->w_ - _rhs); }
        inline Vector4<T> operator-(const Vector3<T>& _rhs) const { return Vector4(this->x_ - _rhs.x_, this->y_ - _rhs.y_, this->z_ - _rhs.z_, this->w_ - _rhs.w_); }
        inline Vector4<T> operator*(const T& _rhs) const { return Vector4(this->x_ * _rhs, this->y_ * _rhs, this->z_ * _rhs, this->w_ * _rhs); }
        inline Vector4<T> operator/(const T& _rhs) const { return Vector4(this->x_ / _rhs, this->y_ / _rhs, this->z_ / _rhs, this->w_ / _rhs); }

        inline bool operator==(const Vector4<T>& _rhs) { return this->x_ == _rhs.x_ && this->y_ == _rhs.y_ && this->z_ == _rhs.z_ && this->w_ == _rhs.w_; }
        inline bool operator!=(const Vector4<T>& _rhs) { return !(*this == _rhs); }

        inline Vector4<T> operator=(const Vector4<T>& _rhs)
        {
            if (this != &_rhs)
            {
                this->x_ = _rhs.x_;
                this->y_ = _rhs.y_;
                this->z_ = _rhs.z_;
                this->w_ = _rhs.w_;
            }

            return *this;
        }

        inline Vector4<T> operator+=(const T& _rhs)
        {
            this->x_ += _rhs;
            this->y_ += _rhs;
            this->z_ += _rhs;
            this->w_ += _rhs;

            return *this;
        }

        inline Vector4<T> operator+=(const Vector4<T>& _rhs)
        {
            this->x_ += _rhs.x_;
            this->y_ += _rhs.y_;
            this->z_ += _rhs.z_;
            this->w_ += _rhs.w_;

            return *this;
        }

        inline Vector4<T> operator-=(const T& _rhs)
        {
            this->x_ -= _rhs;
            this->y_ -= _rhs;
            this->z_ -= _rhs;
            this->w_ -= _rhs;

            return *this;
        }

        inline Vector4<T> operator-=(const Vector4<T>& _rhs)
        {
            this->x_ -= _rhs.x_;
            this->y_ -= _rhs.y_;
            this->z_ -= _rhs.z_;
            this->w_ -= _rhs.w_;

            return *this;
        }

        inline Vector4<T> operator*=(const T& _rhs)
        {
            this->x_ *= _rhs;
            this->y_ *= _rhs;
            this->z_ *= _rhs;
            this->w_ *= _rhs;

            return *this;
        }

        inline Vector4<T> operator/=(const T& _rhs)
        {
            this->x_ /= _rhs;
            this->y_ /= _rhs;
            this->z_ /= _rhs;
            this->w_ /= _rhs;

            return *this;
        }

        template <typename S>
        friend const Vector4 operator+(const T& _lhs, const Vector4& _rhs);
        template <typename S>
        friend std::ostream& operator<<(std::ostream& _out, const Vector4& _vector);

        // Getters and setters.
        inline void setX(T _x) { this->x_ = _x; }
        inline void setY(T _y) { this->y_ = _y; }
        inline void setZ(T _z) { this->z_ = _z; }
        inline void setW(T _w) { this->w_ = _w; }
        inline T x() const { return this->x_; }
        inline T y() const { return this->y_; }
        inline T z() const { return this->z_; }
        inline T w() const { return this->w_; }

        // Static members
        static Vector4<T> zero;
        static Vector4<T> one;

    private:
        T x_, y_, z_, w_;
    };

    // Static members initialization.
    template <typename T> Vector4<T> Vector4<T>::zero = Vector4<T>(0, 0, 0, 0);
    template <typename T> Vector4<T> Vector4<T>::one = Vector4<T>(1, 1, 1, 1);

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
            << _vector.y() << ", " << _vector.z() << ", " << _vector.w_ << ")" << std::endl;

        return _out;
    }
}

#endif // NAGE_MATH_NAGEMATHVECTOR_H_
