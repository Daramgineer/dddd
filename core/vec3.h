#pragma once

#define CUDA_CALLABLE
//#define CUDA_CALLABLE __global__ __device__
#define HIMATH_REAL float
//#define HIMATH_REAL double

#if 0 //_DEBUG
#define VEC3_VALIDATE() {	\
	assert(_finite(x));\
	assert(!_isnan(x));\
	\
	assert(_finite(y));\
	assert(!_isnan(y));\
	\
	assert(_finite(z));\
	assert(!_isnan(z));\
						 }
#else
#define VEC3_VALIDATE()
#endif

template <typename T = float>
class HiXVector3
{
public:

	typedef T value_type;

	CUDA_CALLABLE inline HiXVector3() : x(0.0f), y(0.0f), z(0.0f) {}
	CUDA_CALLABLE inline HiXVector3(T a) : x(a), y(a), z(a) {}
	CUDA_CALLABLE inline HiXVector3(const T* p) : x(p[0]), y(p[1]), z(p[2]) {}
	CUDA_CALLABLE inline HiXVector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_)
	{
		VEC3_VALIDATE();
	}

	CUDA_CALLABLE inline operator T* () { return &x; }
	CUDA_CALLABLE inline operator const T* () const { return &x; };

	CUDA_CALLABLE inline void Set(T x_, T y_, T z_) { VEC3_VALIDATE(); x = x_; y = y_; z = z_; }

	CUDA_CALLABLE inline HiXVector3<T> operator * (T scale) const { HiXVector3<T> r(*this); r *= scale; return r; VEC3_VALIDATE(); }
	CUDA_CALLABLE inline HiXVector3<T> operator / (T scale) const { HiXVector3<T> r(*this); r /= scale; return r; VEC3_VALIDATE(); }
	CUDA_CALLABLE inline HiXVector3<T> operator + (const HiXVector3<T>& v) const { HiXVector3<T> r(*this); r += v; return r; VEC3_VALIDATE(); }
	CUDA_CALLABLE inline HiXVector3<T> operator - (const HiXVector3<T>& v) const { HiXVector3<T> r(*this); r -= v; return r; VEC3_VALIDATE(); }
	CUDA_CALLABLE inline HiXVector3<T> operator /(const HiXVector3<T>& v) const { HiXVector3<T> r(*this); r /= v; return r; VEC3_VALIDATE(); }
	CUDA_CALLABLE inline HiXVector3<T> operator *(const HiXVector3<T>& v) const { HiXVector3<T> r(*this); r *= v; return r; VEC3_VALIDATE(); }

	CUDA_CALLABLE inline HiXVector3<T>& operator *=(T scale) { x *= scale; y *= scale; z *= scale; VEC3_VALIDATE(); return *this; }
	CUDA_CALLABLE inline HiXVector3<T>& operator /=(T scale) { T s(1.0f / scale); x *= s; y *= s; z *= s; VEC3_VALIDATE(); return *this; }
	CUDA_CALLABLE inline HiXVector3<T>& operator +=(const HiXVector3<T>& v) { x += v.x; y += v.y; z += v.z; VEC3_VALIDATE(); return *this; }
	CUDA_CALLABLE inline HiXVector3<T>& operator -=(const HiXVector3<T>& v) { x -= v.x; y -= v.y; z -= v.z; VEC3_VALIDATE(); return *this; }
	CUDA_CALLABLE inline HiXVector3<T>& operator /=(const HiXVector3<T>& v) { x /= v.x; y /= v.y; z /= v.z; VEC3_VALIDATE(); return *this; }
	CUDA_CALLABLE inline HiXVector3<T>& operator *=(const HiXVector3<T>& v) { x *= v.x; y *= v.y; z *= v.z; VEC3_VALIDATE(); return *this; }

	CUDA_CALLABLE inline bool operator != (const HiXVector3<T>& v) const { return (x != v.x || y != v.y || z != v.z); }

	// negate
	CUDA_CALLABLE inline HiXVector3<T> operator -() const { VEC3_VALIDATE(); return HiXVector3<T>(-x, -y, -z); }

	CUDA_CALLABLE void Validate()
	{
		VEC3_VALIDATE();
	}

	T x, y, z;
};

typedef HiXVector3<HIMATH_REAL> Vec3;
typedef HiXVector3<HIMATH_REAL> Vector3;

// lhs scalar scale
template <typename T>
CUDA_CALLABLE HiXVector3<T> operator *(T lhs, const HiXVector3<T>& rhs)
{
	HiXVector3<T> r(rhs);
	r *= lhs;
	return r;
}

template <typename T>
CUDA_CALLABLE bool operator==(const HiXVector3<T>& lhs, const HiXVector3<T>& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

template <typename T>
CUDA_CALLABLE typename T::value_type Dot3(const T& v1, const T& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

CUDA_CALLABLE inline float Dot3(const float* v1, const float* v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


template <typename T>
CUDA_CALLABLE inline T Dot(const HiXVector3<T>& v1, const HiXVector3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

CUDA_CALLABLE inline Vec3 Cross(const Vec3& b, const Vec3& c)
{
	return Vec3(b.y * c.z - b.z * c.y,
		b.z * c.x - b.x * c.z,
		b.x * c.y - b.y * c.x);
}

// component wise min max functions
template <typename T>
CUDA_CALLABLE inline HiXVector3<T> Max(const HiXVector3<T>& a, const HiXVector3<T>& b)
{
	return HiXVector3<T>(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
}

template <typename T>
CUDA_CALLABLE inline HiXVector3<T> Min(const HiXVector3<T>& a, const HiXVector3<T>& b)
{
	return HiXVector3<T>(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z));
}

