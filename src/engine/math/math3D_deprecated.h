/*
	math3D - v0.1
	
    A mathematical library allowing operations on vectors and matrices -- 2D, 3D, 4D, ..., ND

	[CLASSES]
	Vector2, Vector3, Quaternion -- vector 2d, 3d, 4d
		- overloaded operators;
		- operations on vectors (normalization, dot product, etc).
	Matrix, Matrix2, Matrix3, Matrix4 -- matrix 2d, 3d, 4d
		- overloaded operators;
		- operations on matrices (addition, multiplication, etc).
*/

#ifndef MATH3D_H
#define MATH3D_H

#include <cmath>

#include <iostream> // std::ostream
#include <iomanip> // std::setw
#include <cstddef> // std::size_t
#include <stdexcept> // exceptions
#include <vector> // std::vector
#include <cassert>  // assert

#define toRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define toDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)
#define assertm(exp, msg) assert(((void)msg, exp))

class Quaternion;

template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Vector4;

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector4<int> Vector4i;
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

template <typename T>
class Matrix2;
template <typename T>
class Matrix3;
template <typename T>
class Matrix4;

typedef Matrix2<int> Matrix2i;
typedef Matrix2<float> Matrix2f;
typedef Matrix2<double> Matrix2d;
typedef Matrix3<int> Matrix3i;
typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
typedef Matrix4<int> Matrix4i;
typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

template <typename T>
class Vector2
{
public:
	Vector2() : x(0), y(0) {}
	Vector2(T _x, T _y) : x(_x), y(_y) {}
    Vector2(const Vector2& _rhs) { x = _rhs.x; y = _rhs.y; }

	// Overloaded operators.
	Vector2<T> operator+ (const Vector2<T> &rhs) const { return Vector2(this->x + rhs.x, this->y + rhs.y); }
	Vector2<T> operator- (const Vector2<T> &rhs) const { return Vector2(this->x - rhs.x, this->y - rhs.y); }
	Vector2<T> operator* (const T &rhs) const { return Vector2(this->x * rhs, this->y * rhs); }
	Vector2<T> operator/ (const T &rhs) const { return Vector2(this->x / rhs, this->y / rhs); }

	bool operator== (const Vector2<T> &rhs) { return this->x == rhs.x && this->y == rhs.y; }
	bool operator!= (const Vector2<T> &rhs) { return !(*this == rhs); }

	inline Vector2<T> operator =(const Vector2<T> &rhs)
	{
		if (this != &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
		}

		return *this;
	}

	inline Vector2<T> operator+= (const Vector2<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	inline Vector2<T> operator-= (const Vector2<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	inline Vector2<T> operator*= (const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}

	inline Vector2<T> operator/= (const T &rhs)
	{
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

    template <typename S>
	friend std::ostream& operator<< (std::ostream& out, const Vector2& vector);

	// Operaton on vector.
    inline T length() { return static_cast<T>(sqrt(this->x * this->x + this->y * this->y)); }
	inline T max() { return (this->x > this->y) ? this->x : this->y; }
	inline T dot(const Vector2<T> &rhs) { return this->x * rhs.x + this->y * rhs.y; }
	inline T cross(const Vector2<T> &rhs) { return this->x * rhs.y - this->y * rhs.x; }
	inline T lerp(const Vector2<T> &rhs, T factor) { return (rhs - *this) * factor + *this; }

	inline Vector2<T> normalized()
	{
		T length = length();

		if (length > 0)
		{
			this->x /= length;
			this->y /= length;
		}

		return Vector2(this->x, this->y);
	}

	inline Vector2<T> rotate(T angle)
	{
        double radians = static_cast<double>(toRadians(angle));
		double c = cos(radians);
		double s = sin(radians);

        return Vector2(static_cast<T>((this->x * c - this->y * s)),
            static_cast<T>((this->x * s + this->y * c)));
	}

	// Getters and setters.
	inline void setX(T _x) { this->x = _x; }
	inline void setY(T _y) { this->y = _y; }
	inline T getX() const { return this->x; }
	inline T getY() const { return this->y; }

private:
    T x, y;
};

template <typename T>
class Vector3
{
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& _rhs) { x = _rhs.x; y = _rhs.y; z = _rhs.z; }

    // Overloaded operators.
	Vector3<T> operator+ (const Vector3<T> &rhs) const { return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
	Vector3<T> operator- (const Vector3<T> &rhs) const { return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
	Vector3<T> operator* (const T &rhs) const { return Vector3(this->x * rhs, this->y * rhs, this->z * rhs); }
	Vector3<T> operator/ (const T &rhs) const { return Vector3(this->x / rhs, this->y / rhs, this->z / rhs); }

	bool operator== (const Vector3<T> &rhs) { return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z; }
	bool operator!= (const Vector3<T> &rhs) { return !(*this == rhs); }

	inline Vector3<T> operator= (const Vector3<T> &rhs)
	{
		if (this != &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
		}

		return *this;
	}

	inline Vector3<T> operator+= (const Vector3<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	inline Vector3<T> operator-= (const Vector3<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	inline Vector3<T> operator*= (const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}

	inline Vector3<T> operator/= (const T &rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	template <typename S>
    friend std::ostream& operator<< (std::ostream& out, const Vector3& vector);

	// Opertions on vector.
    inline T length() { return static_cast<T>(sqrt(getX() * getX() + getY() * getY() + getZ() * getZ())); }
	static T dot(const Vector3f& lhs, const Vector3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    inline T lerp(const Vector3& rhs, T factor) { return (rhs - *this) * factor + *this; }

	inline T max()
	{
		T m = (this->x < this->y) ? this->y : this->x;
		return ((m < this->z) ? this->z : m);
    }

	inline static Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{
		const T _x = lhs.getY() * rhs.getZ() - rhs.getY() * lhs.getZ();
		const T _y = lhs.getZ() * rhs.getX() - rhs.getZ() * lhs.getX();
		const T _z = lhs.getX() * rhs.getY() - rhs.getX() * lhs.getY();

		return Vector3(_x, _y, _z);
	}

	inline static Vector3 normalize(const Vector3& vector)
	{
        T length = static_cast<T>(sqrtf(vector.getX() * vector.getX() + vector.getY() *
            vector.getY() + vector.getZ() * vector.getZ()));

		Vector3 res = vector;
		if (length > 0)
		{
			res.setX(vector.getX() / length);
			res.setY(vector.getY() / length);
			res.setZ(vector.getZ() / length);
		}

		return res;
	}

    inline Vector3 rotate(Vector3<T> axis, T angle)
	{
		double s = sin(-angle);
		double c = cos(-angle);

		return this->cross(axis * s) + // local X.
			(*this * c) + // local Y.
			axis * this->dot(axis * (1 - c)); // local Z.
	}

    Vector3 rotate(const Quaternion &rotation) const;

	// Getters and setters.
	inline void setX(T _x) { this->x = _x; }
    inline void setY(T _y) { this->y = _y; }
	inline void setZ(T _z) { this->z = _z; }
	inline T getX() const { return this->x; }
	inline T getY() const { return this->y; }
    inline T getZ() const { return this->z; }

private:
    T x, y, z;
};

template <typename T, std::size_t rows, std::size_t cols>
class Matrix
{
public:
	Matrix()
	{
		matrix.resize(rows * cols, T(0));
		identity();
	}

    Matrix(size_t _rows, size_t _cols)
	{
		matrix.resize(_rows * _cols, T(0));
		identity();
	}

	Matrix(const T &_initial)
	{
        matrix.resize(rows * cols, T(_initial));
	}

	Matrix(const Matrix& rhs)
	{
		matrix = rhs.matrix;
    }

    virtual ~Matrix() {}

	// Init identity matrix.
	void identity()
	{
		for (size_t i = 0; i < matrix.size(); i++)
		{
			if (i % (rows + 1) == 0) matrix[i] = T(1);
			else matrix[i] = T(0);
		}
	}

	// Overloaded operators.
	Matrix& operator= (const Matrix& rhs)
	{
		if (&rhs != this)
		{
			matrix.resize(rhs.getSize());

			for (std::size_t i = 0; i < rhs.rowsCount(); i++)
			{
				for (std::size_t j = 0; j < rhs.colsCount(); j++)
				{
					(*this)(i, j) = rhs(i, j);
				}
			}
		}

		return *this;
	}

	Matrix& operator+= (const Matrix& rhs)
	{
		if (rows != rhs.rowsCount() || cols != rhs.colsCount())
			throw std::length_error("The size of columns or rows is not equal.");

		for (std::size_t i = 0; i < rhs.rowsCount(); i++)
		{
			for (std::size_t j = 0; j < rhs.colsCount(); j++)
			{
				(*this)(i, j) += rhs(i, j);
			}
		}

		return *this;
	}

	Matrix& operator-= (const Matrix& rhs)
	{
		if (rows != rhs.rowsCount() || cols != rhs.colsCount())
			throw std::length_error("The size of columns or rows is not equal.");

		for (std::size_t i = 0; i < rhs.rowsCount(); i++)
		{
			for (std::size_t j = 0; j < rhs.colsCount(); j++)
			{
				(*this)(i, j) -= rhs(i, j);
			}
		}

		return *this;
	}

	Matrix& operator*= (const Matrix& rhs)
	{
	    Matrix tmp;
	    tmp = (*this) * rhs;
	    (*this) = tmp;

        return *this;
	}

	Matrix& operator+= (const T& rhs)
	{
		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				(*this)(i, j) += rhs;
			}
		}

		return *this;
	}

	Matrix& operator-= (const T& rhs)
	{
		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				(*this)(i, j) -= rhs;
			}
		}

		return *this;
	}

	Matrix& operator*= (const T& rhs)
	{
		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				(*this)(i, j) *= rhs;
			}
		}

		return *this;
	}

	Matrix& operator/= (const T& rhs)
	{
		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				(*this)(i, j) /= rhs;
			}
		}

		return *this;
	}

	std::vector<T> operator* (const std::vector<T> &rhs)
	{
		std::vector<T> result(rhs.size(), 0.0);

		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				result[i] = (*this)(i, j) * rhs[j];
			}
		}

		return result;
	}

	Matrix transpose()
	{
		Matrix result;

		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < cols; j++)
			{
				result(i, j) = (*this)(i, j);
			}
		}

		return result;
	}

	Matrix operator+ (const Matrix& rhs) { return (*this) += rhs; }
	Matrix operator- (const Matrix& rhs) { return (*this) -= rhs; }

	template <size_t new_cols>
	Matrix<T, rows, new_cols> operator* (const Matrix<T, cols, new_cols>& rhs) const
	{
        if (cols != rhs.rowsCount())
            throw std::length_error("The size of columns in first matrix and rows in second is not equal.");

		Matrix<T, rows, new_cols> tmp(T(0));

		for (std::size_t i = 0; i < rows; i++)
		{
			for (std::size_t j = 0; j < new_cols; j++)
			{
				for (std::size_t k = 0; k < cols; k++)
				{
					tmp(j, i) += (*this)(k, i) * rhs(j, k);
				}
			}
		}

		return tmp;
	}

	Matrix operator+ (const T &rhs) { return (*this) += rhs; }
	Matrix operator- (const T &rhs) { return (*this) -= rhs; }
	Matrix operator* (const T &rhs) { return (*this) *= rhs; }
	Matrix operator/ (const T &rhs) { return (*this) /= rhs; }

	inline T& operator() (const size_t& row, const size_t& col) { return matrix[row * cols + col]; }
	inline const T& operator() (const size_t& row, const size_t& col) const { return matrix[row * cols + col]; }

	template <typename S, size_t r, size_t c>
    friend std::ostream& operator<< (std::ostream& out, const Matrix<S, r, c>& matrix);

	// Getters and setters.
	std::size_t rowsCount() const { return rows; }
	std::size_t colsCount() const { return cols; }
	std::size_t getSize() const { return matrix.size(); }
	bool isEmpty() { return matrix.empty(); }

protected:
	std::vector<T> matrix;
};

template <typename T>
class Matrix2 : public Matrix<T, 2, 2>
{
public:
    Matrix2() : Matrix<T, 2, 2>() {}

	// Overloaded operators.
	Matrix2& operator= (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator=(rhs);
		return *this;
	}

	Matrix2& operator+ (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator+(rhs);
		return *this;
	}

	Matrix2& operator- (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator-(rhs);
		return *this;
	}

	Matrix2 operator* (const Matrix2& rhs)
	{
        Matrix2 res(*this);
        res *= rhs;

		return res;
	}

	Matrix2& operator+= (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator+=(rhs);
		return *this;
	}

	Matrix2& operator-= (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator-=(rhs);
		return *this;
	}

	Matrix2& operator*= (const Matrix2& rhs)
	{
		Matrix<T, 2, 2>::operator*=(rhs);
		return *this;
	}

	Matrix2& operator+ (const T& rhs)
	{
		Matrix<T, 2, 2>::operator+(rhs);
		return *this;
	}

	Matrix2& operator- (const T& rhs)
	{
		Matrix<T, 2, 2>::operator-(rhs);
		return *this;
	}

	Matrix2& operator* (const T& rhs)
	{
		Matrix<T, 2, 2>::operator*(rhs);
		return *this;
	}

	Matrix2& operator/ (const T& rhs)
	{
		Matrix<T, 2, 2>::operator/(rhs);
		return *this;
	}

	Matrix2& operator+= (const T& rhs)
	{
		Matrix<T, 2, 2>::operator+=(rhs);
		return *this;
	}

	Matrix2& operator-= (const T& rhs)
	{
		Matrix<T, 2, 2>::operator-=(rhs);
		return *this;
	}

	Matrix2& operator*= (const T& rhs)
	{
		Matrix<T, 2, 2>::operator*=(rhs);
		return *this;
	}

	Matrix2& operator/= (const T& rhs)
	{
		Matrix<T, 2, 2>::operator/=(rhs);
		return *this;
	}

	template <typename S>
    friend std::ostream& operator<< (std::ostream& out, const Matrix2& matrix)
    {
        Matrix<S, 2, 2>::operator<< (matrix);
        return out;
    }
};

template <typename T>
class Matrix3 : public Matrix<T, 3, 3>
{
public:
    Matrix3() : Matrix<T, 3, 3>() {}

	// Overloaded operators.
	Matrix3& operator= (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator=(rhs);
		return *this;
	}

	Matrix3& operator+ (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator+(rhs);
		return *this;
	}

	Matrix3& operator- (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator-(rhs);
		return *this;
	}

	Matrix3 operator* (const Matrix3& rhs)
	{
        Matrix3 res(*this);
        res *= rhs;

		return res;
	}

	Matrix3& operator+= (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator+=(rhs);
		return *this;
	}

	Matrix3& operator-= (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator-=(rhs);
		return *this;
	}

	Matrix3& operator*= (const Matrix3& rhs)
	{
		Matrix<T, 3, 3>::operator*=(rhs);
		return *this;
	}

	Matrix3& operator+ (const T& rhs)
	{
		Matrix<T, 3, 3>::operator+(rhs);
		return *this;
	}

	Matrix3& operator- (const T& rhs)
	{
		Matrix<T, 3, 3>::operator-(rhs);
		return *this;
	}

	Matrix3& operator* (const T& rhs)
	{
		Matrix<T, 3, 3>::operator*(rhs);
		return *this;
	}

	Matrix3& operator/ (const T& rhs)
	{
		Matrix<T, 3, 3>::operator/(rhs);
		return *this;
	}

	Matrix3& operator+= (const T& rhs)
	{
		Matrix<T, 3, 3>::operator+=(rhs);
		return *this;
	}

	Matrix3& operator-= (const T& rhs)
	{
		Matrix<T, 3, 3>::operator-=(rhs);
		return *this;
	}

	Matrix3& operator*= (const T& rhs)
	{
		Matrix<T, 3, 3>::operator*=(rhs);
		return *this;
	}

	Matrix3& operator/= (const T& rhs)
	{
		Matrix<T, 3, 3>::operator/=(rhs);
		return *this;
	}

	// 2D transformations.
	Matrix3 translate(T x, T y)
	{
		(*this)(0, 0) = T(1);  (*this)(0, 1) = T(0);  (*this)(0, 2) = x;
		(*this)(1, 0) = T(0);  (*this)(1, 1) = T(1);  (*this)(1, 2) = y;
		(*this)(2, 0) = T(0);  (*this)(2, 1) = T(0);  (*this)(2, 2) = T(1);

		return *this;
	}

	Matrix3 rotate(T x, T y)
	{
		Matrix3 rotX, rotY;

        x = static_cast<T>(toRadians(x));
        y = static_cast<T>(toRadians(y));

		(*this)(0, 0) = cos(x); (*this)(0, 1) = -sin(x); (*this)(0, 2) = T(0);
		(*this)(1, 0) = sin(x); (*this)(1, 1) = cos(x);  (*this)(1, 2) = T(0);
		(*this)(2, 0) = T(0);   (*this)(2, 1) = T(0);    (*this)(2, 2) = T(1);

		return *this;
	}

	Matrix3 scale(T x, T y)
	{
		(*this)(0, 0) = x;    (*this)(0, 1) = T(0); (*this)(0, 2) = T(0);
		(*this)(1, 0) = T(0); (*this)(1, 1) = y;    (*this)(1, 2) = T(0);
		(*this)(2, 0) = T(0); (*this)(2, 1) = T(0); (*this)(2, 2) = T(1);

		return *this;
	}

	Matrix3 shear(T x, T y)
	{
		Matrix3 shX, shY;

		shX(0, 0) = T(1); shX(0, 0) = x;    shX(0, 0) = T(0);
		shX(0, 0) = T(0); shX(0, 0) = T(1); shX(0, 0) = T(0);
		shX(0, 0) = T(0); shX(0, 0) = T(0); shX(0, 0) = T(1);

		shY(0, 0) = T(1); shY(0, 0) = T(0); shY(0, 0) = T(0);
		shY(0, 0) = y;    shY(0, 0) = T(1); shY(0, 0) = T(0);
		shY(0, 0) = T(0); shY(0, 0) = T(0); shY(0, 0) = T(1);

		*this = shY * shX;
		return *this;
	}

    template <typename S>
    friend std::ostream& operator<< (std::ostream& out, const Matrix3& matrix)
    {
        Matrix<S, 3, 3>::operator<< (matrix);
        return out;
    }
};

template <typename T>
class Matrix4 : public Matrix<T, 4, 4>
{
public:
    Matrix4() : Matrix<T, 4, 4>() {}
    Matrix4(const Matrix4& _rhs) : Matrix<T, 4, 4>(_rhs) {}

    // Overloaded operators.
    Matrix4& operator= (const Matrix4& rhs)
    {
        Matrix<T, 4, 4>::operator=(rhs);
        return *this;
    }

	Matrix4& operator+ (const Matrix4& rhs)
	{
		Matrix<T, 4, 4>::operator+(rhs);
		return *this;
	}

	Matrix4& operator- (const Matrix4& rhs)
	{
		Matrix<T, 4, 4>::operator-(rhs);
		return *this;
	}

    Matrix4& operator* (const Matrix4& rhs)
    {
        Matrix<T, 4, 4>::operator*(rhs);
        return *this;
    }

	Matrix4& operator+= (const Matrix4& rhs)
	{
		Matrix<T, 4, 4>::operator+=(rhs);
		return *this;
	}

	Matrix4& operator-= (const Matrix4& rhs)
	{
		Matrix<T, 4, 4>::operator-=(rhs);
		return *this;
	}

	Matrix4& operator*= (const Matrix4& rhs)
	{
		Matrix<T, 4, 4>::operator*=(rhs);
		return *this;
	}

	Matrix4& operator+ (const T& rhs)
	{
		Matrix<T, 4, 4>::operator+(rhs);
		return *this;
	}

	Matrix4& operator- (const T& rhs)
	{
		Matrix<T, 4, 4>::operator-(rhs);
		return *this;
	}

	Matrix4& operator* (const T& rhs)
	{
		Matrix<T, 4, 4>::operator*(rhs);
		return *this;
	}

	Matrix4& operator/ (const T& rhs)
	{
		Matrix<T, 4, 4>::operator/(rhs);
		return *this;
	}

	Matrix4& operator+= (const T& rhs)
	{
		Matrix<T, 4, 4>::operator+=(rhs);
		return *this;
	}

	Matrix4& operator-= (const T& rhs)
	{
		Matrix<T, 4, 4>::operator-=(rhs);
		return *this;
	}

	Matrix4& operator*= (const T& rhs)
	{
		Matrix<T, 4, 4>::operator*=(rhs);
		return *this;
	}

	Matrix4& operator/= (const T& rhs)
	{
		Matrix<T, 4, 4>::operator/=(rhs);
		return *this;
	}

	// 3D transformations.
	Matrix4 translate(T x, T y, T z)
    {
        (*this)(0, 0) = T(1); (*this)(0, 1) = T(0); (*this)(0, 2) = T(0); (*this)(0, 3) = T(0);
        (*this)(1, 0) = T(0); (*this)(1, 1) = T(1); (*this)(1, 2) = T(0); (*this)(1, 3) = T(0);
        (*this)(2, 0) = T(0); (*this)(2, 1) = T(0); (*this)(2, 2) = T(1); (*this)(2, 3) = T(0);
        (*this)(3, 0) = T(x); (*this)(3, 1) = T(y); (*this)(3, 2) = T(z); (*this)(3, 3) = T(1);

		return *this;
	}

	Matrix4 rotate(T x, T y, T z)
	{
		Matrix4 rotX, rotY, rotZ;

        x = static_cast<T>(toRadians(x));
        y = static_cast<T>(toRadians(y));
        z = static_cast<T>(toRadians(z));

		rotX(0, 0) = T(1); rotX(0, 1) = T(0);   rotX(0, 2) = T(0);    rotX(0, 3) = T(0);
		rotX(1, 0) = T(0); rotX(1, 1) = cos(x); rotX(1, 2) = -sin(x); rotX(1, 3) = T(0);
		rotX(2, 0) = T(0); rotX(2, 1) = sin(x); rotX(2, 2) = cos(x);  rotX(2, 3) = T(0);
		rotX(3, 0) = T(0); rotX(3, 1) = T(0);   rotX(3, 2) = T(0);    rotX(3, 3) = T(1);

		rotY(0, 0) = cos(y); rotY(0, 1) = T(0); rotY(0, 2) = -sin(y); rotY(0, 3) = T(0);
		rotY(1, 0) = T(0);   rotY(1, 1) = T(1); rotY(1, 2) = T(0);    rotY(1, 3) = T(0);
		rotY(2, 0) = sin(y); rotY(2, 1) = T(0); rotY(2, 2) = cos(y);  rotY(2, 3) = T(0);
		rotY(3, 0) = T(0);   rotY(3, 1) = T(0); rotY(3, 2) = T(0);    rotY(3, 3) = T(1);

		rotZ(0, 0) = cos(z); rotZ(0, 1) = -sin(z); rotZ(0, 2) = T(0); rotZ(0, 3) = T(0);
		rotZ(1, 0) = sin(z); rotZ(1, 1) = cos(z);  rotZ(1, 2) = T(0); rotZ(1, 3) = T(0);
		rotZ(2, 0) = T(0);   rotZ(2, 1) = T(0);    rotZ(2, 2) = T(1); rotZ(2, 3) = T(0);
		rotZ(3, 0) = T(0);   rotZ(3, 1) = T(0);    rotZ(3, 2) = T(0); rotZ(3, 3) = T(1);

		*this = rotZ * rotY * rotX;
		return *this;
	}

    Matrix4 rotate(const Quaternion& _quaternion);

	Matrix4 scale(T x, T y, T z)
	{
		(*this)(0, 0) = x;    (*this)(0, 1) = T(0); (*this)(0, 2) = T(0); (*this)(0, 3) = T(0);
		(*this)(1, 0) = T(0); (*this)(1, 1) = y;    (*this)(1, 2) = T(0); (*this)(1, 3) = T(0);
		(*this)(2, 0) = T(0); (*this)(2, 1) = T(0); (*this)(2, 2) = z;    (*this)(2, 3) = T(0);
		(*this)(3, 0) = T(0); (*this)(3, 1) = T(0); (*this)(3, 2) = T(0); (*this)(3, 3) = T(1);

		return *this;
	}

	Matrix4 shear(T x, T y, T z)
	{
		Matrix4 shX, shY, shZ;

		shX(0, 0) = T(1); shX(0, 1) = T(0); shX(0, 2) = T(0); shX(0, 3) = T(0);
		shX(1, 0) = y;    shX(1, 1) = T(1); shX(1, 2) = T(0); shX(1, 3) = T(0);
		shX(2, 0) = z;    shX(2, 1) = T(0); shX(2, 2) = T(1); shX(2, 3) = T(0);
		shX(3, 0) = T(0); shX(3, 1) = T(0); shX(3, 2) = T(0); shX(3, 3) = T(1);

		shY(0, 0) = T(1); shY(0, 1) = x;    shY(0, 2) = T(0); shY(0, 3) = T(0);
		shY(1, 0) = T(0); shY(1, 1) = T(1); shY(1, 2) = T(0); shY(1, 3) = T(0);
		shY(2, 0) = T(0); shY(2, 1) = z;    shY(2, 2) = T(1); shY(2, 3) = T(0);
		shY(3, 0) = T(0); shY(3, 1) = T(0); shY(3, 2) = T(0); shY(3, 3) = T(1);

		shZ(0, 0) = T(1); shZ(0, 1) = T(0); shZ(0, 2) = x;    shZ(0, 3) = T(0);
		shZ(1, 0) = T(0); shZ(1, 1) = T(1); shZ(1, 2) = y;    shZ(1, 3) = T(0);
		shZ(2, 0) = T(0); shZ(2, 1) = T(0); shZ(2, 2) = T(1); shZ(2, 3) = T(0);
		shZ(3, 0) = T(0); shZ(3, 1) = T(0); shZ(3, 2) = T(0); shZ(3, 3) = T(1);

		*this = shZ * shY * shX;
		return *this;
	}

	Matrix4 perspective(T fov, T aspectRatio, T zNear, T zFar)
	{
        const T tanHalfFOV = static_cast<T>(tanf(toRadians(fov) / 2));
		const T zRange = zFar - zNear;

		(*this)(0, 0) = T(1) / (tanHalfFOV * aspectRatio); (*this)(0, 1) = T(0);              (*this)(0, 2) = T(0);                            (*this)(0, 3) = T(0);
		(*this)(1, 0) = T(0);                              (*this)(1, 1) = T(1) / tanHalfFOV; (*this)(1, 2) = T(0);                            (*this)(1, 3) = T(0);
		(*this)(2, 0) = T(0);                              (*this)(2, 1) = T(0);              (*this)(2, 2) = -(zFar + zNear) / zRange;        (*this)(2, 3) = -T(1);
		(*this)(3, 0) = T(0);                              (*this)(3, 1) = T(0);              (*this)(3, 2) = -(T(2) * zFar * zNear) / zRange; (*this)(3, 3) = T(0);

		return *this;
	}

	Matrix4 orthographic(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		const T width = (right - left);
		const T height = (top - bottom);
		const T depth = (zFar - zNear);

		(*this)(0, 0) = T(2) / width; (*this)(0, 1) = T(0);          (*this)(0, 2) = T(0);          (*this)(0, 3) = -(right + left) / width;
		(*this)(1, 0) = T(0);         (*this)(1, 1) = T(2) / height; (*this)(1, 2) = T(0);          (*this)(1, 3) = -(top + bottom) / height;
		(*this)(2, 0) = T(0);         (*this)(2, 1) = T(0);          (*this)(2, 2) = T(-2) / depth; (*this)(2, 3) = -(zFar + zNear) / depth;
		(*this)(3, 0) = T(0);         (*this)(3, 1) = T(0);          (*this)(3, 2) = T(0);          (*this)(3, 3) = T(1);

		return *this;
	}

	Matrix4 lookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
	{
		Vector3f f = Vector3f::normalize(target - eye);
		Vector3f s = Vector3f::normalize(Vector3f::cross(f, up));
		Vector3f u = Vector3f::cross(s, f);

		(*this)(0, 0) = s.getX();			    (*this)(0, 1) = u.getX();			    (*this)(0, 2) = -f.getX();		        (*this)(0, 3) = T(0);
		(*this)(1, 0) = s.getY();			    (*this)(1, 1) = u.getY();			    (*this)(1, 2) = -f.getY();			    (*this)(1, 3) = T(0);
		(*this)(2, 0) = s.getZ();			    (*this)(2, 1) = u.getZ();			    (*this)(2, 2) = -f.getZ();			    (*this)(2, 3) = T(0);
		(*this)(3, 0) = -Vector3f::dot(s, eye); (*this)(3, 1) = -Vector3f::dot(u, eye); (*this)(3, 2) = Vector3f::dot(f, eye);  (*this)(3, 3) = T(1);

		return *this;
	}

	Vector3f transform(const Vector3f &rhs)
	{
		return Vector3f((*this)(0, 0) * rhs.getX() + (*this)(0, 1) * rhs.getY() + (*this)(0, 2) * rhs.getZ() + (*this)(0, 3),
			(*this)(1, 0) * rhs.getX() + (*this)(1, 1) * rhs.getY() + (*this)(1, 2) * rhs.getZ() + (*this)(1, 3),
			(*this)(2, 0) * rhs.getX() + (*this)(2, 1) * rhs.getY() + (*this)(2, 2) * rhs.getZ() + (*this)(2, 3));
	}

    template <typename S>
    friend std::ostream& operator<< (std::ostream& out, const Matrix4& matrix)
    {
        Matrix<S, 4, 4>::operator<< (matrix);
        return out;
    }
};

class Quaternion
{
public:
    Quaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f);
    Quaternion(const Vector3f& _vector, float _scalar);

    Quaternion &operator+=(const Quaternion& _quaternion);
    Quaternion &operator-=(const Quaternion& _quaternion);
    Quaternion &operator*=(float _factor);
    Quaternion &operator*=(const Quaternion& _quaternion);
    Quaternion &operator/=(float _divisor);
    friend inline bool operator==(const Quaternion& _quaternion1, const Quaternion& _quaternion2);
    friend inline bool operator!=(const Quaternion& _quaternion1, const Quaternion& _quaternion2);
    friend inline const Quaternion operator+(const Quaternion& _quaternion1, const Quaternion& _quaternion2);
    friend inline const Quaternion operator-(const Quaternion& _quaternion1, const Quaternion& _quaternion2);
    friend inline const Quaternion operator-(const Quaternion& _quaternion);
    friend inline const Quaternion operator*(float _factor, const Quaternion& _quaternion);
    friend inline const Quaternion operator*(const Quaternion& _quaternion, float _factor);
    friend inline const Vector3f operator*(const Quaternion& _quaternion, const Vector3f& _vector);
    friend inline const Quaternion operator*(const Quaternion& _quaternion1, const Quaternion& _quaternion2);
    friend inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor);
    friend inline std::ostream& operator<< (std::ostream& _out, const Quaternion& _quaternion);

    inline bool isNull() const;
    inline bool isIdentity() const;
    inline float length() const;
    inline float lengthSquared() const;
    inline void normalize();
    inline Quaternion normalized() const;
    inline Quaternion conjugate() const;
    inline Quaternion conjugated() const;
    inline Quaternion inverted() const;
    inline Vector3f rotatedVector(const Vector3f& _vector) const;
    static inline float dotProduct(const Quaternion& _quaternion1, const Quaternion& _quaternion2);

    inline void getAxisAndAngle(float* _x, float* _y, float* _z, float* _angle) const;
    inline void getAxisAndAngle(Vector3f* _axis, float* _angle) const;
    static Quaternion fromAxisAndAngle(const Vector3f& _axis, float _angle);
    static Quaternion fromAxisAndAngle(float _x, float _y, float _z, float _angle);

    void setX(float _x) { mX = _x; }
    void setY(float _y) { mY = _y; }
    void setZ(float _z) { mZ = _z; }
    void setW(float _w) { mW = _w; }
    void setVector(float _x, float _y, float _z) { mX = _x; mY = _y; mZ = _z; }

    float x() const { return mX; }
    float y() const { return mY; }
    float z() const { return mZ; }
    float w() const { return mW; }
    Vector3f vector() const { return Vector3f(mX, mY, mZ); }

private:
    float mX, mY, mZ, mW;
};

inline Quaternion Quaternion::conjugate() const
{
    return conjugated();
}

inline Quaternion Quaternion::conjugated() const
{
    return Quaternion(-mX, -mY, -mZ, mW);
}

inline Vector3f Quaternion::rotatedVector(const Vector3f& _vector) const
{
    return (*this * Quaternion(_vector, 0) * conjugated()).vector();
}

template <typename T>
Matrix4<T> Matrix4<T>::rotate(const Quaternion& _quaternion)
{
    // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q54
/*
    const float f2x = _quaternion.x() + _quaternion.x();
    const float f2y = _quaternion.y() + _quaternion.y();
    const float f2z = _quaternion.z() + _quaternion.z();
    const float f2xw = f2x * _quaternion.w();
    const float f2yw = f2y * _quaternion.w();
    const float f2zw = f2z * _quaternion.w();
    const float f2xx = f2x * _quaternion.x();
    const float f2xy = f2x * _quaternion.y();
    const float f2xz = f2x * _quaternion.z();
    const float f2yy = f2y * _quaternion.y();
    const float f2yz = f2y * _quaternion.z();
    const float f2zz = f2z * _quaternion.z();

    (*this)(0, 0) = 1.0f - (f2yy + f2zz); (*this)(0, 1) = f2xy + f2zw;          (*this)(0, 2) = f2xz - f2yw;           (*this)(0, 3) = 0.0f;
    (*this)(1, 0) = f2xy - f2zw;          (*this)(1, 1) = 1.0f - (f2xx + f2zz); (*this)(1, 2) = f2yz + f2xw;           (*this)(1, 3) = 0.0f;
    (*this)(2, 0) = f2xz + f2yw;          (*this)(2, 1) = f2yz - f2xw;          (*this)(2, 2) = 1.0f - (f2xx + f2yy);  (*this)(2, 3) = 0.0f;
    (*this)(3, 0) = 0.0f;                 (*this)(3, 1) = 0.0f;                 (*this)(3, 2) = 0.0f;                  (*this)(3, 3) = 1.0f;

    return *this;*/

    // https://stackoverflow.com/a/1556470

    const float n = 1.0f / std::sqrt(_quaternion.x() * _quaternion.x() + _quaternion.y() * _quaternion.y()
        + _quaternion.z() * _quaternion.z() + _quaternion.w() * _quaternion.w());


    return *this;
}

inline Quaternion& Quaternion::operator+=(const Quaternion& _quaternion)
{
    mX += _quaternion.mX;
    mY += _quaternion.mY;
    mZ += _quaternion.mZ;
    mW += _quaternion.mW;

    return *this;
}

inline Quaternion& Quaternion::operator-=(const Quaternion& _quaternion)
{
    mX -= _quaternion.mX;
    mY -= _quaternion.mY;
    mZ -= _quaternion.mZ;
    mW -= _quaternion.mW;

    return *this;
}

inline Quaternion& Quaternion::operator*=(float _factor)
{
    mX *= _factor;
    mY *= _factor;
    mZ *= _factor;
    mW *= _factor;

    return *this;
}

inline Quaternion& Quaternion::operator*=(const Quaternion& _quaternion)
{
    *this = *this * _quaternion;
    return *this;
}

inline Quaternion& Quaternion::operator/=(float _divisor)
{
    mX /= _divisor;
    mY /= _divisor;
    mZ /= _divisor;
    mW /= _divisor;

    return *this;
}

inline bool operator==(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
{
    return _quaternion1.mX == _quaternion2.mX && _quaternion1.mY == _quaternion2.mY && _quaternion1.mZ == _quaternion2.mZ
        && _quaternion1.mW == _quaternion2.mW;
}

inline bool operator!=(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
{
    return !operator==(_quaternion1, _quaternion2);
}

inline const Quaternion operator+(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
{
    return Quaternion(_quaternion1.mX + _quaternion2.mX, _quaternion1.mY + _quaternion2.mY, _quaternion1.mZ + _quaternion2.mZ,
        _quaternion1.mW + _quaternion2.mW);
}

inline const Quaternion operator-(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
{
    return Quaternion(_quaternion1.mX - _quaternion2.mX, _quaternion1.mY - _quaternion2.mY, _quaternion1.mZ - _quaternion2.mZ,
        _quaternion1.mW - _quaternion2.mW);
}

inline const Quaternion operator-(const Quaternion& _quaternion)
{
    return Quaternion(-_quaternion.mX, -_quaternion.mY, -_quaternion.mZ, -_quaternion.mW);
}

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

inline const Vector3f operator*(const Quaternion& _quaternion, const Vector3f& _vector)
{
    return _quaternion.rotatedVector(_vector);
}

inline const Quaternion operator*(const Quaternion& _quaternion1, const Quaternion& _quaternion2)
{
    float yy = (_quaternion1.mW - _quaternion1.mY) * (_quaternion2.mW + _quaternion2.mZ);
    float zz = (_quaternion1.mW + _quaternion1.mY) * (_quaternion2.mW - _quaternion2.mZ);
    float ww = (_quaternion1.mZ + _quaternion1.mX) * (_quaternion2.mX + _quaternion2.mY);
    float xx = ww + yy + zz;
    float qq = 0.5f * (xx + (_quaternion1.mZ - _quaternion1.mX) * (_quaternion2.mX - _quaternion2.mY));

    float w = qq - ww + (_quaternion1.mZ - _quaternion1.mY) * (_quaternion2.mY - _quaternion2.mZ);
    float x = qq - xx + (_quaternion1.mX + _quaternion1.mW) * (_quaternion2.mX + _quaternion2.mW);
    float y = qq - yy + (_quaternion1.mW - _quaternion1.mX) * (_quaternion2.mY + _quaternion2.mZ);
    float z = qq - zz + (_quaternion1.mZ + _quaternion1.mY) * (_quaternion2.mW - _quaternion2.mX);

    return Quaternion(x, y, z, w);
}

inline const Quaternion operator/(const Quaternion& _quaternion, float _divisor)
{
    return Quaternion(_quaternion.mX / _divisor, _quaternion.mY / _divisor, _quaternion.mZ / _divisor,
        _quaternion.mW / _divisor);
}

inline std::ostream& operator<< (std::ostream& _out, const Quaternion& _quaternion)
{
    _out << "Quaternion(" << _quaternion.x() << ", " << _quaternion.y() << ", " << _quaternion.z() << ", "
        << _quaternion.w() << ")";
    return _out;
}

template <typename T, size_t rows, size_t cols>
std::ostream& operator<< (std::ostream& out, const Matrix<T, rows, cols>& matrix)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            out << std::setw(8) << matrix(i, j);//floorf(matrix(i, j) * 100) / 100;
        }
        out << std::endl;
    }

    return out;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Vector2<T>& vector)
{
    out << "Vector2(" << vector.getX() << ", " << vector.getY() << ")";
    return out;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Vector3<T>& vector)
{
    out << "Vector3(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
    return out;
}

#endif // MATH3D_H
