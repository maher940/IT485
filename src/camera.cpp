#include "camera.h"
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <SDL.h>
#include <stdio.h>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}



//position of the camera 5 out on z axis
glm::vec3 position = glm::vec3(0, 0, 5);

//horizontal angle
float horizontalAngle = 3.14f;

//vertical angle
float verticalAngle = 0.0f;

//field of view
float initialFoV = 45.0f;


float speed = 3.0f; 

float mouseSpeed = 0.005f;

float oldtime;

void CameraSetUp()
{
	/*
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	*/
	int x, y;
	Uint8 buttons = SDL_GetMouseState(&x, &y);
	printf("%d\n", x);
	printf("%d\n", y);
	
	horizontalAngle += mouseSpeed * float(1024 / 2 - x);
	verticalAngle += mouseSpeed * float(768 / 2 - y);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	
	ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(position, position + direction,up);
}