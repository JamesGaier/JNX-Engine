#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(Model * m) { setModel(m); }

GameObject::~GameObject() { delete model; }

glm::mat4 GameObject::getTranslateMat() const {
	return glm::translate(glm::mat4(), static_cast<glm::vec3>(pos));
}

glm::mat4 GameObject::getScaleMat() const {
	return glm::scale(glm::mat4(), static_cast<glm::vec3>(scale));
}

void GameObject::setModel(Model * m) { model = m; }

void GameObject::setPosition(Vec3d loc) { pos = loc; }

void GameObject::setScale(Vec3d axes) { scale = axes; }

void GameObject::draw(Renderer* r, Shader* shader) const { 
	r->draw(model, shader); 
}



