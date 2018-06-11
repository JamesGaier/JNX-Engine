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
public:
	GameObject(Model* m);
	virtual ~GameObject();

	glm::mat4 getTranslateMat() const;
	glm::mat4 getScaleMat() const;
	inline glm::mat4 getRotationMat() const { return rotation; }

	inline glm::mat4 getModelMatrix() const {return getTranslateMat() * getRotationMat() * getScaleMat();}

	void setModel(Model* m);
	void setPosition(Vec3d loc);
	void setScale(Vec3d axes);
	void setRotation(float radians, Vec3d axis);

	void draw(Renderer* r, Shader* shader) const;
};

#endif