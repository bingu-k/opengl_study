#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "header.hpp"

enum	Movement{
	FORWARD, BACKWARD, LEFT, RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
bool	firstMouse = true;


class Camera
{
public:
	glm::vec3	position;
	glm::vec3	direction;
	glm::vec3	worldUp;
	glm::vec3	right;
	glm::vec3	up;
	float		yaw;
	float		pitch;
	float		moveSensitivity;
	float		moveSpeed;
	float		zoom;
	
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW,
			float pitch = PITCH)
	: moveSensitivity(SENSITIVITY), moveSpeed(SPEED), zoom(ZOOM)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		updateCamera();
	};

	void	setPosition(glm::vec3 pos)
	{ position = pos; }

	glm::mat4	getCamView(void)
	{ return (glm::lookAt(position, position + direction, worldUp)); };

	bool	pressKeyBoard(Movement dir,float deltaTime)
	{
		float	velocity = moveSpeed * deltaTime;
		if(dir == FORWARD)
			this->position += this->direction * velocity;
		else if(dir == BACKWARD)
			this->position -= this->direction * velocity;
		else if(dir == LEFT)
			this->position -= this->right * velocity;
		else if(dir == RIGHT)
			this->position += this->right * velocity;
		else
			return (false);
		return (true);
	};

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= moveSensitivity;
        yoffset *= moveSensitivity;
        yaw   += xoffset;
        pitch += yoffset;

        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }
        updateCamera();
    }

    void ProcessMouseScroll(float yoffset)
    {
        zoom -= static_cast<float>(yoffset);
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f; 
    }

	~Camera()
	{};
private:
	void	updateCamera(void)
	{
		glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        direction	= glm::normalize(front);
        right		= glm::normalize(glm::cross(direction, worldUp));
        up			= glm::normalize(glm::cross(right, direction));
	};

};

#endif