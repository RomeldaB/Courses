// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(normalize(dir))
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		m_focus = 1/tan(Pif*angle/2/180);
		m_aspect = (float) resolution.width/resolution.height;
		m_xAxis = m_dir.cross(m_up);
		m_yAxis = -m_up;
	}

	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		// Normalized device coordinates [0, 1]
		float ndcx = (x + 0.5) / getResolution().width;
		float ndcy = (y + 0.5) / getResolution().height;
		// Screen space coordinates [-1, 1]
		float sscx = (2 * ndcx - 1) * m_aspect;  
		float sscy = 2 * ndcy - 1;
		// Generate direction through pixel center
		Vec3f d =  m_dir * m_focus + sscx * m_xAxis + sscy * m_yAxis;
		ray.dir = normalize(d); // Normalize: d/|d|
		ray.t = FLT_MAX; //maximal float value in the library
		ray.org = m_pos;

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};