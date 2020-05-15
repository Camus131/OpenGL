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

    //�����ͼ����
    Matrix4x4f GetViewMatrix()const { return Matrix4x4f::LookAt(position_, position_ + front_, up_); }

    //�ƶ����
    void Move(CameraMovement direction, float frame_time);

    //ת�����
    void Turn(float xoffset, float yoffset);

    //������Ұ
    void Zoom(float offset);

    //�����Ұ
    float GetFov()const { return fov_; }

    //���λ��
    Vector3f GetPosition()const { return position_; }

private:
    void reset();

public:
    static Camera DeFaultCamera;

private:
    //ʵʱλ��
    Vector3f position_;
    Vector3f front_;
    Vector3f up_;
    Vector3f right_;

    //��ʼλ��
    Vector3f default_position_;
    Vector3f default_front_;
    Vector3f default_up_;

    //ŷ����
    float yaw_;
    float pitch_;

    //�ƶ��ٶ�
    float movement_speed_;

    //ת��������
    float sensitivity_;

    //��Ұ��С
    float fov_;
};