#ifndef CAMERA_H
#define CAMERA_H

#include "../libraries/glm/glm.hpp"
#include "../libraries/glm/gtc/matrix_transform.hpp"
#include "../libraries/glm/gtc/type_ptr.hpp"

#include "./shader.h"
#include "./debugOutput.h"

class Camera {

public:
	glm::vec3 position;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float xPos = 0.0f;
	float yPos = 0.0f;
	float zPos = -3.0f;

	Camera(glm::mat4 modelValue, glm::mat4 viewValue, glm::mat4 projectValue, glm::vec3 positionValue)
	{
		DebugOutput debugOutput(true);

		position = position;
		model = modelValue;
		view = viewValue;
		projection = projectValue;

		debugOutput.outputGreenText("**SUCCESS**::CAMERA::INITIALIZED::[tools/camera.h]");
	}

	void setProjection(Shader shader, int screenWidth, int screenHeight)
	{
		projection = glm::mat4(1.0f);

		// Projection - Creates the clip space for near and far views
		// Params for projection:
		// 1. Field of view (FOV) - realistic view set at 45 degrees
		// 2. Aspect ratio
		// 3. near plane
		// 4. far plane
		projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

	}

	void setView(Shader shader)
	{
		view = glm::mat4(1.0f);
		// View space "camera"
		// Transforms world-space coordinates to coordinates in front of the user's view
		view = glm::translate(view, glm::vec3(xPos, yPos, zPos));
		shader.setMat4("view", view);
	}

	void setViewLookAt(Shader shader, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
	{
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", view);
		position = cameraPos;
	}

	void setRotationView(Shader shader)
	{
		view = glm::mat4(1.0f);
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		// View space "camera"
		// Transforms world-space coordinates to coordinates in front of the user's view
		view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4("view", view);
	}
	
	void use(Shader shader, glm::vec3 objectPosition, int arrayPosition = 0, bool scale = false)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, objectPosition);
		// Model matrix - transforms objects from local space into world space
		// Performs translations, scaling, and rotation to place objects in the world
		//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		if (scale)
		{
			model = glm::scale(model, glm::vec3(0.2f));
		}
		
		//float angle = 20.0f * position;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setMat4("model", model);
	}
	

};

#endif