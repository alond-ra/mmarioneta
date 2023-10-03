#include "Camera.h"

Camera::Camera()
{
	Direction = glm::vec3(0.f, 0.f, 0.f);
	Position = glm::vec3(0.f, 0.f, 0.f);
	pitch = 0;
	yaw = -90.f;
}

Camera::Camera(float Pitch, float Yaw, glm::vec3 pos)
{
	Position = pos;
	Direction = glm::vec3(0.f, 0.f, 0.f);
	pitch = Pitch;
	yaw =Yaw;
}