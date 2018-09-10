#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(Model * m) { setModel(m); }

GameObject::GameObject(const std::string & modelLocation) {
	auto m = new Model(modelLocation);
	setModel(m);
}

GameObject::~GameObject() { delete model; }

glm::mat4 GameObject::translateMat() const {
	return glm::translate(glm::mat4(), static_cast<glm::vec3>(pos));
}

glm::mat4 GameObject::scaleMat() const {
	return glm::scale(glm::mat4(), static_cast<glm::vec3>(scale));
}

void GameObject::setModel(Model * m) {
	model = m;
	setScale(Vec3d(m->scaleFactor()));
}

void GameObject::setPosition(Vec3d loc) { pos = loc; }

void GameObject::setScale(Vec3d axes) { scale = axes; }

void GameObject::setRotation(float radians, Vec3d axis) {
	rotation = glm::rotate(glm::mat4(), radians, static_cast<glm::vec3>(axis));
}

void GameObject::shaderSettings(Shader* shader, const glm::mat4& vpmat) {
	shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
	shader->setUniformMat4f("u_MVP", vpmat * modelMatrix());
}

void GameObject::draw(Renderer* r, Shader* shader) const {
	r->draw(model, shader);
}

void GameObject::update(double delta) {
	static double totalDelta = 0;
	
	totalDelta += delta;
	constexpr auto RATE = 1.41;
	auto x = std::cos(totalDelta / RATE);
	auto y = std::sin(totalDelta / RATE);
	setPosition(Vec3d(x, y, 0));
}
