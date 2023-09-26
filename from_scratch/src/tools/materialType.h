#ifndef MATERIAL_TYPE_H
#define MATERIAL_TYPE_H

#include "../libraries/glm/glm.hpp"
#include "../libraries/glm/gtc/matrix_transform.hpp"
#include "../libraries/glm/gtc/type_ptr.hpp"

#include "./debugOutput.h"

class MaterialType {

public:
	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

	struct Light {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Material blackPlastic;
	Material obsidian;
	Material gold;

	glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	Light max;
	Light high;
	Light minimal;


	MaterialType(bool active) 
	{
		setMaterials();
		setLighting();

	}

private:
	void setMaterials()
	{
		DebugOutput debugOutput(true);

		blackPlastic.ambient = glm::vec3(0.0, 0.0, 0.0);
		blackPlastic.diffuse = glm::vec3(0.01, 0.01, 0.01);
		blackPlastic.specular = glm::vec3(0.50, 0.50, 0.50);
		blackPlastic.shininess = 0.25f;

		obsidian.ambient = glm::vec3(0.05375, 0.05, 0.06625);
		obsidian.diffuse = glm::vec3(0.01, 0.01, 0.01);
		obsidian.specular = glm::vec3(0.50, 0.50, 0.50);
		obsidian.shininess = 0.3f;

		gold.ambient = glm::vec3(0.24725, 0.1995, 0.0745);
		gold.diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
		gold.specular = glm::vec3(0.628281, 0.555802, 0.366065);
		gold.shininess = 0.4f;

		debugOutput.outputGreenText("**SUCCESS**::MATERIAL::MATERIALS_TYPES_SET::[tools/materialType.h]");
	}

	void setLighting()
	{
		DebugOutput debugOutput(true);

		max.position = glm::vec3(1.0f, 1.0f, 1.0f);
		max.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		max.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		max.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		high.position = glm::vec3(1.0f, 1.0f, 1.0f);
		high.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		high.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		high.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		minimal.position = glm::vec3(1.0f, 1.0f, 1.0f);
		minimal.ambient = (LightColor * glm::vec3(0.5f)) * glm::vec3(0.2f);
		minimal.diffuse = LightColor * glm::vec3(0.5f);
		minimal.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		debugOutput.outputGreenText("**SUCCESS**::MATERIAL::LIGHTING_TYPES_SET::[tools/materialType.h]");
	}


};


#endif