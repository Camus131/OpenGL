#pragma once

#include "Matrix4x4f.h"


enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(const Vector3f& position, const Vector3f& target, const Vector3f& up);
    ~Camera();

    //获得视图矩阵
    Matrix4x4f GetViewMatrix()const { return Matrix4x4f::LookAt(position_, position_ + front_, up_); }

    //移动相机
    void Move(CameraMovement direction, float frame_time);

    //转动相机
    void Turn(float xoffset, float yoffset);

    //调整视野
    void Zoom(float offset);

    //获得视野
    float GetFov()const { return fov_; }

    //获得位置
    Vector3f GetPosition()const { return position_; }

private:
    void reset();

public:
    static Camera DeFaultCamera;

private:
    //实时位置
    Vector3f position_;
    Vector3f front_;
    Vector3f up_;
    Vector3f right_;

    //初始位置
    Vector3f default_position_;
    Vector3f default_front_;
    Vector3f default_up_;

    //欧拉角
    float yaw_;
    float pitch_;

    //移动速度
    float movement_speed_;

    //转动灵敏度
    float sensitivity_;

    //视野大小
    float fov_;
};