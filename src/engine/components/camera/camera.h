#ifndef NAGE_ENGINE_CORE_CAMERA_CAMERA_H_
#define NAGE_ENGINE_CORE_CAMERA_CAMERA_H_

#include "engine/render/projection.h"
#include "engine/math/NAGEMath/nagemathvector.h"
#include "engine/math/NAGEMath/nagemathmatrix.h"
#include "engine/math/NAGEMath/nagemathquaternion.h"

namespace NAGE
{
	class Camera
	{
	public:
        Camera();

        void translate(const Vector3f& _translation);
        void translate(float _x, float _y, float _z);
        void rotate(const Quaternion& _rotation);
        void rotate(float _angle, const Vector3f& _axis);
        void rotate(float _angle, float _x, float _y, float _z);

		// Setters
        void setForward(const Vector3f& _forward);
        void setUp(const Vector3f& _up);
        void setRight(const Vector3f& _right);
        void setTranslation(const Vector3f& _translation);
        void setTranslation(float _x, float _y, float _z);
        void setRotation(const Quaternion& _rotation);
        void setRotation(float _angle, const Vector3f& _axis);
        void setRotation(float _angle, float _x, float _y, float _z);

		// Getters
        Vector3f forward() const;
        Vector3f up() const;
        Vector3f right() const;
        Vector3f translation() const { return mTranslation; }
        Quaternion rotation() const { return mRotation; }
        float roll() const;
        float pitch() const;
        float yaw() const;

        Matrix4f view() const;

	private:
		Vector3f mForward;
		Vector3f mUp;
		Vector3f mRight;

		Vector3f mTranslation;
		Quaternion mRotation;
	};
}

#endif // NAGE_ENGINE_CORE_CAMERA_CAMERA_H_
