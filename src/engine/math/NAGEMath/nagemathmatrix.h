#ifndef NAGE_NAGEMATHMATRIX_H_
#define NAGE_NAGEMATHMATRIX_H_

#include "nagemathquaternion.h"

#include <iostream>
#include <typeinfo>
#include <iomanip>
#include <vector>
#include <stdexcept>

namespace NAGE
{
    template <typename T>
    class Matrix2;
    typedef Matrix2<int> Matrix2i;
    typedef Matrix2<float> Matrix2f;
    typedef Matrix2<double> Matrix2d;

    template <typename T>
    class Matrix3;
    typedef Matrix3<int> Matrix3i;
    typedef Matrix3<float> Matrix3f;
    typedef Matrix3<double> Matrix3d;

    template <typename T>
    class Matrix4;
    typedef Matrix4<int> Matrix4i;
    typedef Matrix4<float> Matrix4f;
    typedef Matrix4<double> Matrix4d;

    template <typename T>
    class Matrix
    {
    public:
        Matrix<T>() : mRows(0), mCols(0) {}

        Matrix<T>(uint _rows, uint _cols)
            : mRows(_rows),
              mCols(_cols)
        {
            allocate(); // Allocate matrix memory.
            fill(0); // Fill array with value.
        }

        Matrix<T>(uint _rows, uint _cols, T _value)
            : mRows(_rows),
              mCols(_cols)
        {
            allocate();
            fill(_value);
        }

        Matrix<T>(const Matrix<T>& _matrix)
            : mRows(_matrix.mRows),
              mCols(_matrix.mCols)
        {
            allocate();
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] = _matrix.mArr[i * mCols + j];
                }
            }
        }

        virtual ~Matrix<T>()
        {
            deallocate(); // Deallocate matrix memory.
        }

        inline T& operator()(uint _row, uint _col)
        {
            if(_row < 0 || _row > mRows || _col < 0 || _col > mCols)
                throw std::out_of_range("[ERROR] Access elements out of defined range");

            return mArr[_row * mCols + _col];
        }

        inline const T& operator()(uint _row, uint _col) const
        {
            if(_row < 0 || _row > mRows || _col < 0 || _col > mCols)
                throw std::out_of_range("[ERROR] Access elements out of defined range");

            return mArr[_row * mCols + _col];
        }

        inline Matrix<T>& operator=(const Matrix<T>& _rhs)
        {
            if(this == &_rhs)
                return *this;

            if(mRows != _rhs.mRows || mCols != _rhs.mCols)
            {
                deallocate();

                mRows = _rhs.mRows;
                mCols = _rhs.mCols;

                allocate();
            }

            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] = _rhs.mArr[i * mCols + j];
                }
            }

            return *this;
        }

        inline Matrix<T>& operator*=(const Matrix<T>& _rhs)
        {
            if(mCols != _rhs.mRows)
                throw std::invalid_argument("[ERROR] lhs columns size != rhs rows size");

            Matrix<T> result(mRows, _rhs.mCols);
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < result.mCols; j++)
                {
                    for(uint k = 0; k < mCols; k++)
                    {
                         result.mArr[i * _rhs.mCols + j] += mArr[i * mCols + k]
                            * _rhs.mArr[k * result.mCols + j];
                    }
                }
            }

            return (*this = result);
        }

        inline Matrix<T>& operator*=(T _rhs)
        {
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] *= _rhs;
                }
            }

            return *this;
        }

        inline Matrix<T>& operator/=(T _rhs)
        {
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] /= _rhs;
                }
            }

            return *this;
        }

        inline Matrix<T>& operator+=(const Matrix<T>& _rhs)
        {
            if(mRows != _rhs.mRows || mCols != _rhs.mCols)
                throw std::invalid_argument("[ERROR] Unexpected data size, matrices sizes must be equal.");

            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] += _rhs.mArr[i * mCols + j];
                }
            }

            return *this;
        }

        inline Matrix<T>& operator-=(const Matrix<T>& _rhs)
        {
            if(mRows != _rhs.mRows || mCols != _rhs.mCols)
                std::cerr << "[ERROR] Unexpected data size" << std::endl;

            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] -= _rhs.mArr[i * mCols + j];
                }
            }

            return *this;
        }

        inline bool operator==(const Matrix<T>& _rhs) const
        {
            if(mRows != _rhs.mRows || mCols != _rhs.mCols)
                return false;

            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    if(mArr[i * mCols + j] != _rhs.mArr[i * mCols + j])
                        return false;
                }
            }

            return true;
        }

        inline bool operator!=(const Matrix<T>& _rhs) const
        {
            return !operator==(_rhs);
        }

        template <typename U>
        friend Matrix<U> operator+(const Matrix<U>& _lhs, const Matrix<U>& _rhs);
        template <typename U>
        friend Matrix<U> operator-(const Matrix<U>& _lhs, const Matrix<U>& _rhs);
        template <typename U>
        friend Matrix<U> operator*(const Matrix<U>& _lhs, const Matrix<U>& _rhs);
        template <typename U>
        friend Matrix<U> operator*(const Matrix<U>& _lhs, U _rhs);
        template <typename U>
        friend Matrix<U> operator*(U _lhs, const Matrix<U>& _rhs);
        template <typename U>
        friend Matrix<U> operator/(const Matrix<U>& _lhs, U _rhs);
        template <typename U>
        friend std::istream& operator>>(std::istream& _is, const Matrix<U>& _matrix);
        template <typename U>
        friend std::ostream& operator<<(std::ostream& _os, const Matrix<U>& _matrix);

        inline bool isIdentity()
        {
            if(!isSquare())
                return false;

            for(int i = 0; i < mRows; i++)
            {
                for(int j = 0; j < mCols; j++)
                {
                    if((i == j && mArr[i * mCols + j] != 1) || (i != j && mArr[i * mCols + j] != 0))
                        return false;
                }
            }

            return true;
        }

        inline bool isSquare()
        {
            if(mRows == mCols)
                return true;

            return false;
        }

        inline bool isNull()
        {
            for(int i = 0; i < mRows; i++)
            {
                for(int j = 0; j < mCols; j++)
                {
                    if(mArr[i * mCols + j] != 0)
                        return false;
                }
            }

            return true;
        }

        inline bool isDiagonal()
        {
            if(!isSquare())
                return false;

            for(int i = 0; i < mRows; i++)
            {
                for(int j = 0; j < mCols; j++)
                {
                    if(i != j && mArr[i * mCols + j] != 0)
                        return false;
                }
            }

            return true;
        }

        inline void fill(T _value)
        {
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    mArr[i * mCols + j] = _value;
                }
            }
        }

        inline void identity()
        {
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    if(i == j) mArr[i * mCols + j] = 1;
                    else mArr[i * mCols + j] = 0;
                }
            }
        }

        inline Matrix<T>& transpose()
        {
            Matrix<T> result(mRows, mCols);
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    result.mArr[i * mCols + j] = mArr[j * mCols + i];
                }
            }

            return (*this = result);
        }

        inline std::vector<T> vector1D()
        {
            std::vector<T> result;
            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    result.push_back(mArr[i * mCols + j]);
                }
            }

            return result;
        }

        inline std::vector<std::vector<T>> vector2D()
        {
            std::vector<std::vector<T>> result;

            result.resize(mRows);
            for(std::size_t i = 0; result.size(); i++)
                result[i].resize(mCols);

            for(uint i = 0; i < mRows; i++)
            {
                for(uint j = 0; j < mCols; j++)
                {
                    result[i][j] = mArr[i * mCols + j];
                }
            }

            return result;
        }

        inline uint rows() const { return mRows; }
        inline uint cols() const { return mCols; }
        inline uint size() const { return mRows * mCols; }
        inline T** data() const { return mArr; }

    protected:
        T* mArr; // 1D array for matrix.
        uint mRows, mCols;

    private:
        void allocate()
        {
            mArr = new T[mRows * mCols];
        }

        void deallocate()
        {
            delete[] mArr;
        }
    };

    template <typename T>
    Matrix<T> operator+(const Matrix<T>& _lhs, const Matrix<T>& _rhs)
    {
        Matrix<T> result(_lhs);
        return (result += _rhs);
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T>& _lhs, const Matrix<T>& _rhs)
    {
        Matrix<T> result(_lhs);
        return (result -= _rhs);
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T>& _lhs, const Matrix<T>& _rhs)
    {
        Matrix<T> result(_lhs);
        return (result *= _rhs);
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T>& _lhs, T _rhs)
    {
        Matrix<T> result(_lhs);
        return (result *= _rhs);
    }

    template <typename T>
    Matrix<T> operator*(T _lhs, const Matrix<T>& _rhs)
    {
        return (_rhs * _lhs);
    }

    template <typename T>
    Matrix<T> operator/(const Matrix<T>& _lhs, T _rhs)
    {
        Matrix<T> result(_lhs);
        return (result /= _rhs);
    }

    template <typename T>
    std::istream& operator>>(std::istream& _is, const Matrix<T>& _matrix)
    {
        for(uint i = 0; i < _matrix.mRows; i++)
        {
            for(uint j = 0; j < _matrix.mCols; j++)
            {
                _is >> _matrix.mArr[i * _matrix.mCols + j];
            }
        }

        return _is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& _os, const Matrix<T>& _matrix)
    {
        _os << "Matrix<" << typeid(T).name() << ">(" << _matrix.mRows << ", " << _matrix.mCols
            << ")" << std::endl;

        for(uint i = 0; i < _matrix.mRows; i++)
        {
            for(uint j = 0; j < _matrix.mCols; j++)
            {
                _os << std::setw(12) << _matrix.mArr[i * _matrix.mCols + j];
            }

            _os << std::endl;
        }

        return _os;
    }

    template <typename T>
    class Matrix2 : public Matrix<T>
    {
    public:
        Matrix2<T>() : Matrix<T>(2, 2) {}
        Matrix2<T>(T _value) : Matrix<T>(2, 2, _value) {}
        Matrix2<T>(const Matrix<T>& _matrix) : Matrix<T>(_matrix) {}
    };

    template <typename T>
    class Matrix3 : public Matrix<T>
    {
    public:
        Matrix3<T>() : Matrix<T>(3, 3) {}
        Matrix3<T>(T _value) : Matrix<T>(3, 3, _value) {}
        Matrix3<T>(const Matrix<T>& _matrix) : Matrix<T>(_matrix) {}

        // 2D transformations.
        Matrix3<T>& translate(T _x, T _y)
        {
            Matrix3<T> translation;
            translation.identity();

            translation(0, 2) = _x;
            translation(1, 2) = _y;

            *this = *this * translation;
            return *this;
        }

        Matrix3<T>& translate(const Vector2<T>& _vector)
        {
            return translate(_vector.x(), _vector.y());
        }

        Matrix3<T>& rotate(double _angle)
        {
            Matrix3<T> rotation;
            rotation.identity();

            double angle = nage_toRadians(_angle);
            double s = std::sin(angle);
            double c = std::cos(angle);

            rotation(0, 0) = c;
            rotation(0, 1) = -s;
            rotation(1, 0) = s;
            rotation(1, 1) = c;

            *this = *this * rotation;
            return *this;
        }

        Matrix3<T>& scale(T _x, T _y)
        {
            Matrix3<T> scaling;
            scaling.identity();

            scaling(0, 0) = _x;
            scaling(1, 1) = _y;

            *this = *this * scaling;
            return *this;
        }

        Matrix3<T>& scale(const Vector2<T>& _vector)
        {
            return scale(_vector.x(), _vector.y());
        }

        Matrix3<T>& shear(T _x, T _y)
        {
            Matrix3<T> shearX, shearY;
            shearX.identity();
            shearY.identity();

            shearX(0, 1) = _x;
            shearY(1, 0) = _y;

            *this = *this * shearY * shearX;
            return *this;
        }

        Matrix3<T>& shear(const Vector2<T>& _vector)
        {
            return shear(_vector.x(), _vector.y());
        }
    };

    template <typename T>
    class Matrix4 : public Matrix<T>
    {
    public:
        Matrix4<T>() : Matrix<T>(4, 4) {}
        Matrix4<T>(T _value) : Matrix<T>(4, 4, _value) {}
        Matrix4<T>(const Matrix<T>& _matrix) : Matrix<T>(_matrix) {}

        // 3D transformations.
        Matrix4<T>& translate(T _x, T _y, T _z)
        {
            Matrix4<T> translation;
            translation.identity();

            translation(0, 3) = _x;
            translation(1, 3) = _y;
            translation(2, 3) = _z;

            *this = *this * translation;
            return *this;
        }

        Matrix4<T>& translate(const Vector3<T>& _vector)
        {
            return translate(_vector.x(), _vector.y(), _vector.z());
        }

        Matrix4<T>& rotate(double _angle, T _x, T _y, T _z)
        {
            Matrix4<T> rotation;
            rotation.identity();

            double radianAngle = nage_toRadians(_angle);
            double s = std::sin(radianAngle);
            double c = std::cos(radianAngle);
            double t = 1 - c;

            rotation(0, 0) = _x * _x * t + c;
            rotation(1, 0) = _x * _y * t + _z * s;
            rotation(2, 0) = _x * _z * t - _y * s;

            rotation(0, 1) = _y * _x * t - _z * s;
            rotation(1, 1) = _y * _y * t + c;
            rotation(2, 1) = _y * _z * t + _x * s;

            rotation(0, 2) = _z * _x * t + _y * s;
            rotation(1, 2) = _z * _y * t - _x * s;
            rotation(2, 2) = _z * _z * t + c;

            *this = *this * rotation;
            return *this;
        }

        Matrix4<T>& rotate(double _angle, const Vector3<T>& _axis)
        {
            return rotate(_angle, _axis.x(), _axis.y(), _axis.z());
        }

        /* https://stackoverflow.com/a/1556470
         * http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q54
         *
         * You might have to transpose it before passing to OpenGL.
         */
        Matrix4<T>& rotate(const Quaternion& _quaternion)
        {
            Matrix4<T> rotation;
            rotation.identity();

            float qw = _quaternion.w();
            float qx = _quaternion.x();
            float qy = _quaternion.y();
            float qz = _quaternion.z();

            const float len = 1.0f / std::sqrt(qx * qx + qy * qy + qz * qz + qw * qw);
            qw *= len;
            qx *= len;
            qw *= len;
            qz *= len;

            rotation(0, 0) = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
            rotation(0, 1) = 2.0f * qx * qy - 2.0f * qz* qw;
            rotation(0, 2) = 2.0f * qx * qz + 2.0f * qy * qw;
            rotation(1, 0) = 2.0f * qx * qy + 2.0f * qz * qw;
            rotation(1, 1) = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
            rotation(1, 2) = 2.0f * qy * qz - 2.0f * qx * qw;
            rotation(2, 0) = 2.0f * qx * qz - 2.0f * qy * qw;
            rotation(2, 1) = 2.0f * qy * qz + 2.0f * qx * qw;
            rotation(2, 2) = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;

            *this = *this * rotation;
            return *this;
        }

        Matrix4<T>& scale(T _x, T _y, T _z)
        {
            Matrix4<T> scaling;
            scaling.identity();

            scaling(0, 0) = _x;
            scaling(1, 1) = _y;
            scaling(2, 2) = _z;

            *this = *this * scaling;
            return *this;
        }

        Matrix4<T>& scale(const Vector3<T>& _vector)
        {
            return scale(_vector.x(), _vector.y(), _vector.z());
        }

        Matrix4<T>& shear(T _x, T _y, T _z)
        {
            Matrix4<T> shearX, shearY, shearZ;
            shearX.identity();
            shearY.identity();
            shearZ.identity();

            shearX(1, 0) = _y;
            shearX(2, 0) = _z;

            shearY(0, 1) = _x;
            shearY(2, 1) = _z;

            shearZ(0, 2) = _x;
            shearZ(1, 2) = _y;

            *this = *this * shearZ * shearY * shearX;
            return *this;
        }

        Matrix4<T>& shear(const Vector3<T>& _vector)
        {
            return shear(_vector.x(), _vector.y(), _vector.z());
        }

        Matrix4<T>& perspective(T _fov, T _aspectRatio, T _zNear, T _zFar)
        {
            Matrix4<T> perspectiveMat;
            perspectiveMat.identity();

            const double tanHalfFOV = std::tan(nage_toRadians(_fov) / 2);
            const double zRange = _zFar - _zNear;

            perspectiveMat(0, 0) = 1 / (tanHalfFOV * _aspectRatio);
            perspectiveMat(1, 1) = 1 / tanHalfFOV;
            perspectiveMat(2, 2) = -(_zFar + _zNear) / zRange;
            perspectiveMat(2, 3) = -(2 * _zFar * _zNear) / zRange;
            perspectiveMat(3, 2) = -1;
            perspectiveMat(3, 3) = 0;

            *this = *this * perspectiveMat;
            return *this;
        }

        Matrix4<T>& orthographic(T _left, T _right, T _top, T _bottom, T _zNear, T _zFar)
        {
            Matrix4<T> orthographicMat;
            orthographicMat.identity();

            const double width = (_right - _left);
            const double height = (_top - _bottom);
            const double depth = (_zFar - _zNear);

            orthographicMat(0, 0) = 2 / width;
            orthographicMat(0, 3) = -(_right + _left) / width;
            orthographicMat(1, 1) = 2 / height;
            orthographicMat(1, 3) = -(_top + _bottom) / height;
            orthographicMat(2, 2) = -2 / depth;
            orthographicMat(2, 3) = -(_zFar + _zNear) / depth;

            *this = *this * orthographicMat;
            return *this;
        }

        Matrix4<T>& lookAt(const Vector3<T>& _eye, const Vector3<T>& _target, const Vector3<T>& _up)
        {
            Matrix4<T> lookAtMat;
            lookAtMat.identity();

            const Vector3<T> f = Vector3f::normalize(_target - _eye);
            const Vector3<T> s = Vector3f::normalize(Vector3f::cross(f, _up));
            const Vector3<T> u = Vector3f::cross(s, f);

            lookAtMat(0, 0) = s.x();
            lookAtMat(0, 1) = u.x();
            lookAtMat(0, 2) = -f.x();
            lookAtMat(1, 0) = s.y();
            lookAtMat(1, 1) = u.y();
            lookAtMat(1, 2) = -f.y();
            lookAtMat(2, 0) = s.z();
            lookAtMat(2, 1) = u.z();
            lookAtMat(2, 2) = -f.z();
            lookAtMat(3, 0) = -Vector3<T>::dot(s, _eye);
            lookAtMat(3, 1) = -Vector3<T>::dot(u, _eye);
            lookAtMat(3, 2) = Vector3<T>::dot(f, _eye);

            *this = *this * lookAtMat;
            return *this;
        }

        // Transform Matrix4<T> to Matrix3<T> - remove translation from the Matrix.
        // Its useful for light, cubemap (skybox).
        static Matrix3<T> transform(const Matrix4<T>& _rhs)
        {
            Matrix3<T> transformation(0);

            transformation(0, 0) = _rhs(0, 0);
            transformation(0, 1) = _rhs(0, 1);
            transformation(0, 2) = _rhs(0, 2);
            transformation(1, 0) = _rhs(1, 0);
            transformation(1, 1) = _rhs(1, 1);
            transformation(1, 2) = _rhs(1, 2);
            transformation(2, 0) = _rhs(2, 0);
            transformation(2, 1) = _rhs(2, 1);
            transformation(2, 2) = _rhs(2, 2);

            return transformation;
        }

        // Transform Matrix3<T> to Matrix4<T>
        static Matrix4<T> transform(const Matrix3<T>& _rhs)
        {
            Matrix4<T> transformation;
            transformation.identity();

            transformation(0, 0) = _rhs(0, 0);
            transformation(0, 1) = _rhs(0, 1);
            transformation(0, 2) = _rhs(0, 2);
            transformation(1, 0) = _rhs(1, 0);
            transformation(1, 1) = _rhs(1, 1);
            transformation(1, 2) = _rhs(1, 2);
            transformation(2, 0) = _rhs(2, 0);
            transformation(2, 1) = _rhs(2, 1);
            transformation(2, 2) = _rhs(2, 2);

            return transformation;
        }

        Vector3<T> transform(const Vector3<T>& _rhs)
        {
            return Vector3<T>(
                (*this)(0, 0) * _rhs.x() + (*this)(0, 1) * _rhs.y() + (*this)(0, 2) * _rhs.z() + (*this)(0, 3),
                (*this)(1, 0) * _rhs.x() + (*this)(1, 1) * _rhs.y() + (*this)(1, 2) * _rhs.z() + (*this)(1, 3),
                (*this)(2, 0) * _rhs.x() + (*this)(2, 1) * _rhs.y() + (*this)(2, 2) * _rhs.z() + (*this)(2, 3));
        }
    };
}

#endif // NAGE_NAGEMATHMATRIX_H_
