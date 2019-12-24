#include "math3D_deprecated.h"

template <typename T>
Vector3<T> Vector3<T>::rotate(const Quaternion &rotation) const
{
	Quaternion conj = rotation.conjugate();
	Quaternion w = rotation * (*this) * conj;

    return Vector3(w.x(), w.y(), w.z());
}
