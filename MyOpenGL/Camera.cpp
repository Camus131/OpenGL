#include "Camera.h"


Camera::Camera(const Vector3f& position, const Vector3f& target, const Vector3f& up)
{
	default_position_ = position;
	default_front_ = (target - position).Normalize();
	default_up_ = up;
	default_up_.Normalize();
	position_ = default_position_;
	yaw_ = 0.0f;
	pitch_ = 0.0f;
	movement_speed_ = 2.0f;
	sensitivity_ = 0.2f;
	fov_ = 45.0f;
	reset();
}


Camera::~Camera()
{
}


void Camera::Move(CameraMovement direction, float frame_time)
{
	float time = frame_time * movement_speed_;
	switch (direction)
	{
	case FORWARD:
		position_ += front_ * time;
		break;
	case BACKWARD:
		position_ -= front_ * time;
		break;
	case LEFT:
		position_ -= right_ * time;
		break;
	case RIGHT:
		position_ += right_ * time;
		break;
	}
}


void Camera::Turn(float xoffset, float yoffset)
{
	xoffset *= sensitivity_;
	yoffset *= sensitivity_;

	yaw_ += xoffset;
	pitch_ += yoffset;

	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	reset();
}


void Camera::Zoom(float offset)
{
	if (fov_ >= 1.0f && fov_ <= 45.0f)
		fov_ += offset;
	if (fov_ < 1.0f)
		fov_ = 1.0f;
	if (fov_ > 45.0f)
		fov_ = 45.0f;
}


void Camera::reset()
{
	front_ = Matrix4x4f::Rotate(yaw_, Vector3f(0.0f, 1.0f, 0.0f)) * Matrix4x4f::Rotate(pitch_, Vector3f(1.0f, 0.0f, 0.0f)) * default_front_;
	right_ = Vector3f::CrossProduct(front_, default_up_);
	up_ = Vector3f::CrossProduct(right_, front_);
}

Camera Camera::DeFaultCamera(Vector3f(0.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));