// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param color Color of the primitive
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---

		// Barycentric coordinates and 3D edge functions
		Vec3f s1 = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f s2 = (m_a - ray.org).cross(m_c - ray.org);
		Vec3f s3 = (m_c - ray.org).cross(m_b - ray.org);
		
		float lab  = s1.dot(ray.dir) / (s1.dot(ray.dir) + s2.dot(ray.dir) + s3.dot(ray.dir));
		float lac  = s2.dot(ray.dir) / (s1.dot(ray.dir) + s2.dot(ray.dir) + s3.dot(ray.dir));
		float lbc  = s3.dot(ray.dir) / (s1.dot(ray.dir) + s2.dot(ray.dir) + s3.dot(ray.dir));

		if(lab < 0 || lac < 0 || lbc < 0) 
			return false;

		Vec3f nrm = (m_b - m_a).cross(m_c - m_a);
		float t;
		t = -nrm.dot(ray.org - m_a) / nrm.dot(ray.dir);
		if(nrm.dot(ray.dir) == 0 || t < Epsilon || t > ray.t)
			return false;

		ray.t = t;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};