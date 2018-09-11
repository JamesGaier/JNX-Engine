#ifndef _GAMEOBJ
#define _GAMEOBJ

#include "util/Vec3d.h"
#include "rendering/Model.h"
#include "rendering/Renderer.h"
/*
* Purpose: superclass for all game objects
* @author Nicholas Baron
*/
class GameObject {
private:
	Vec3d pos;
	Vec3d scale;
	glm::mat4 rotation;
	Model* model;

	//0 for first render (background), greater is last rendered (foreground)
	unsigned char renderPriority; 

protected:
	inline const Vec3d& position() const { return pos; }
	//0 for background, higher fore foreground
	void setRenderLayer(unsigned char layer) { renderPriority = layer; }

public:
	GameObject(Model* m);
	GameObject(const std::string& modelLocation);
	virtual ~GameObject();

	inline unsigned char renderLayer() const { return renderPriority; }
	glm::mat4 translateMat() const;
	glm::mat4 scaleMat() const;
	inline glm::mat4 rotationMat() const { return rotation; }
	inline glm::mat4 modelMatrix() const { return translateMat() * rotationMat() * scaleMat(); }

	void setModel(Model* m);
	void setPosition(Vec3d loc);
	void setScale(Vec3d axes);
	void setRotation(float radians, Vec3d axis);

	virtual void onRegistered() { std::cout << "Registered!" << std::endl; }
	virtual void shaderSettings(Shader* shader, const glm::mat4& vpmat);
	virtual void draw(Shader* shader) const; //This may not need to be virtual
	virtual void update(double delta);
};

#endif
