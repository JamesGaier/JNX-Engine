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
	Vec3d pos = Vec3d(0);
	Vec3d scale = Vec3d(1);
	glm::mat4 rotation;
	Model* model;

	//0 for first render (background), greater is last rendered (foreground)
	unsigned char renderPriority;

protected:
	inline const Vec3d& position() const { return pos; }
	//0 for background, higher for foreground
	void setRenderLayer(unsigned char layer) { renderPriority = layer; }
	Shader* shader;

public:
	GameObject() {}
	GameObject(const std::string& modelLocation, const std::string& shaderLocation);
	virtual ~GameObject();

	inline unsigned char renderLayer() const { return renderPriority; }
	glm::mat4 translateMat() const;
	glm::mat4 scaleMat() const;
	inline glm::mat4 rotationMat() const { return rotation; }
	inline glm::mat4 modelMatrix() const { return translateMat() * rotationMat() * scaleMat(); }
	void draw() const;

	void setModel(Model* m);
	void setPosition(Vec3d loc);
	void setScale(Vec3d axes);
	void setRotation(float radians, Vec3d axis);

	virtual void onRegistered() { std::cout << "Registered!" << std::endl; }
	virtual void shaderSettings(const glm::mat4& vpmat) const;
	virtual void update(double delta);
};

#endif
