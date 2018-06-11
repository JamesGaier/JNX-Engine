#ifndef _GAMEOBJ
#define _GAMEOBJ

#include "util/Vec3d.h"
#include "rendering/Model.h"
#include "rendering/Renderer.h"

class GameObject {
private:
	Vec3d pos;
	Vec3d scale;
	glm::mat4 rotation;
	Model* model;

	double totalDelta = 0;
public:
	GameObject(Model* m);
	virtual ~GameObject();

	glm::mat4 translateMat() const;
	glm::mat4 scaleMat() const;
	inline glm::mat4 rotationMat() const { return rotation; }

	inline glm::mat4 modelMatrix() const {return translateMat() * rotationMat() * scaleMat();}

	void setModel(Model* m);
	void setPosition(Vec3d loc);
	void setScale(Vec3d axes);
	void setRotation(float radians, Vec3d axis);

	virtual void shaderSettings(Shader* shader, const glm::mat4& vpmat);
	virtual void draw(Renderer* r, Shader* shader) const;
	virtual void update(double delta);
};

#endif