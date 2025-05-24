#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
private:
	glm::vec3 mPosition, mUp, mWorldUp, mFront, mRight;
	float mYaw, mPitch, mMovementSpeed, mMouseSensitivity, mZoom;

public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
	: mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM){
		
		mPosition = pos;
		mWorldUp = up;
		mYaw = yaw;
		mPitch = pitch;

		updateCamVector();
	}

	glm::mat4 GetViewMatrix(){
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	void ProcessKeyboard(Camera_Movement dir, float deltaTime) {

		float velocity = mMovementSpeed * deltaTime;
		if (dir == FORWARD) mPosition += mFront * velocity;
		if (dir == BACKWARD) mPosition -= mFront * velocity;
		if (dir == LEFT) mPosition -= mRight * velocity;
		if (dir == RIGHT) mPosition += mRight * velocity;


	}

	void ProcessMouseMovement(float xoffset, float yoffset, bool isContraintPitch = true) {

		xoffset *= mMouseSensitivity;
		yoffset *= mMouseSensitivity;

		mYaw += xoffset;
		mPitch += yoffset;

		if (isContraintPitch) {
			if (mPitch > 89.0f) mPitch = 89.0f;
			if (mPitch < -89.0f) mPitch = -89.0f;
		}

		updateCamVector();


	}

	void ProcessMouseScroll(float yoffset) {
		mZoom -= (float)yoffset;
		if (mZoom < 1.0f) mZoom = 1.0f;
		if (mZoom > 45.0f) mZoom = 45.0f;
		

	}

	void updateCamVector() {
		
		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

		mFront = glm::normalize(front);
		mRight = glm::normalize(glm::cross(mFront, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));
	}
};

#endif