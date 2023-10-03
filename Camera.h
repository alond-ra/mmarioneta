#pragma once

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>

class Camera {
	public:
		Camera();
		Camera(float Pitch, float Yaw, glm::vec3 pos);
		glm::vec3 Position;
		glm::vec3 Direction;
		float pitch;
		float yaw;
};

#endif