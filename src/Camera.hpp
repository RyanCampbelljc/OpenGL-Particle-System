//-----------------------------------------------------------------------------
// File:			Camera.h
// Original Author:	Ryan Campbell
//
// class to represent a camera to move around the world
// https://learnopengl.com/Getting-started/Camera
//-----------------------------------------------------------------------------
#pragma once
#include "Utility.hpp"

// no move assingnment op
const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

class Camera
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	struct CamParams {
		CamParams(const glm::mat4& proj, const glm::mat4& view, const glm::vec3& pos)
			: proj(proj)
			, view(view)
			, position(pos)
		{
		}
		// if these are references it breaks
		const glm::mat4 proj;
		const glm::mat4 view;
		const glm::vec3 position;
	};
	Camera(int width, int height, wolf::App* pApp);
	~Camera();

	void update(float dt);
	void setWidth(int width);
	void setHeight(int height);
	glm::vec3 getCamPos() const
	{
		return m_position;
	}

	glm::mat4 getProjection() const
	{
		return m_mProj;
	}
	glm::mat4 getView() const
	{
		return m_mView;
	}
	CamParams getCamParams() const
	{
		return CamParams(getProjection(), getView(), getCamPos());
	}
	//-------------------------------------
private:
	//------------------------------------
	// PRIVATE INTERFACE
	//------------------------------------
	wolf::App* m_pApp;
	int m_width;
	int m_height;
	glm::vec3 m_camFront;
	glm::vec3 m_upDirection;
	glm::vec3 m_rightDirection;
	float m_yaw;
	float m_pitch;
	float m_cameraSens;
	glm::vec3 m_position;
	glm::mat4 m_mProj;
	glm::mat4 m_mView;
	float m_velocity;

	void updateCamAxisVectors();
	//---------------------------------------
};
