// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 * @param color Color of the primitive
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		// reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

		float a = ray.dir.dot(ray.dir);
		float b = 2*(ray.dir.dot((ray.org - m_center)));
 		float c = (ray.org - m_center).dot((ray.org - m_center))-(m_radius*m_radius);
		float D = b*b - 4*a*c;
		// No real solution case
		if(D<0)
			return false;
		// One solution case
		else if(D==0)
		{
			float T = -b/(2*a);
			if(T<Epsilon)
				return false;
			else
				ray.t = T;
		}
		// Two solutions case
		else
		{
			float t1 = (-b+sqrt(D))/(2*a);
			float t2 = (-b-sqrt(D))/(2*a);
			if(t1 > t2)
			{
				std::swap(t2, t1);
			}
			if(t1 < Epsilon || t1 > ray.t)
			{
				t1 = t2;
				if(t1 < Epsilon || t2 > ray.t)
					return false;
			}
			ray.t = t1;
			return true;
		}
		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};