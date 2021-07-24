// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 * @param color Color of the primitive
	 */
	CPrimPlane(Vec3f color, Vec3f origin, Vec3f normal)
		: CPrim(color)
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{
		// Substituting ray parametrization
		float T = (m_origin.dot(m_normal)-ray.org.dot(m_normal))/ray.dir.dot(m_normal);
		if((m_normal.dot(ray.dir) == Epsilon) || (T > ray.t) || (T < Epsilon))
			return false;
		ray.t = T;
		return true;
	}
	
	
private:
	Vec3f m_normal;	///< Normal to the plane
	Vec3f m_origin;	///< Point on the plane
};