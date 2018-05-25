#ifndef _GAMEOBJ
#define _GAMEOBJ

#include "util/Vec3d.h"
#include "rendering/Model.h"
#include "rendering/Renderer.h"

class GameObject {
private:
	Vec3d pos;
	Model* model;
public:
	GameObject(Model* m);
	virtual ~GameObject();

	glm::mat4 getTranslateMat() const;

	void setModel(Model* m);
	void setPosition(Vec3d loc);

	void draw(Renderer* r, Shader* shader) const;
};

#endif