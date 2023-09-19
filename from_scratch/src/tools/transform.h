#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "debugOutput.h"
#include "./shader.h"

#include "../libraries/glm/glm.hpp"
#include "../libraries/glm/gtc/matrix_transform.hpp"
#include "../libraries/glm/gtc/type_ptr.hpp"

class Transform {

public:
	glm::mat4 trans = glm::mat4(1.0f);
	glm::vec4 vec = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const char* type;

	float translateX;
	float translateY;
	float translateZ;

	float rotateX;
	float rotateY;
	float rotateZ;
	float rotateRadians;

	float scaleX;
	float scaleY;
	float scaleZ;

	Transform(bool set)
	{
		DebugOutput debugOutput(true);
		debugOutput.outputGreenText("**SUCCESS**::TRANSFORM::INITIALIZED::[tools/transform.h]");
		return;
	}

	void setTranslate(float x, float y, float z)
	{
		translateX = x;
		translateY = y;
		translateZ = z;
		
	}

	void setRotate(float x, float y, float z, float radians)
	{

		rotateX = x;
		rotateY = y;
		rotateZ = z;
		rotateRadians = radians;
	}

	void setScale(float x, float y, float z)
	{
		scaleX = x;
		scaleY = y;
		scaleZ = z;
	}

	void startTransform(Shader shaderClass, bool willTranslate, bool willRotate, bool willScale)
	{

		glm::mat4 tempTrans = trans;

		if (willTranslate)
		{
			//std::cout << translateX << translateY << translateZ << std::endl;
			tempTrans = glm::translate(trans, glm::vec3(translateX, translateY, translateZ));
		}

		
		if (willRotate)
		{
			// rotate once
			tempTrans = glm::rotate(tempTrans, glm::radians(rotateRadians), glm::vec3(rotateX, rotateY, rotateZ));
			
			// rotate over timer
			//tempTrans = glm::rotate(tempTrans, (float)glfwGetTime(), glm::vec3(rotateX, rotateY, rotateZ));
		}

		if (willScale)
		{
			tempTrans = glm::scale(tempTrans, glm::vec3(scaleX, scaleY, scaleZ));
		}

		shaderClass.setMat4("transform", tempTrans);
		resetTransform();
	}
	
	void resetTransform()
	{
		translateX = 0.0f;
		translateY = 0.0f;
		translateZ = 0.0f;

		rotateX = 0.0f;
		rotateY = 0.0f;
		rotateZ = 0.0f;
		rotateRadians = 0.0f;

		scaleX = 0.0f;
		scaleY = 0.0f;
		scaleZ = 0.0f;
	}


};


#endif 