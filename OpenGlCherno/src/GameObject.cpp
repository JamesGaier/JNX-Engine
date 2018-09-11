#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const std::string & modelLocation, const std::string& shaderLocation) {
	setModel(new Model(modelLocation));
	shader = new Shader(shaderLocation);
}

GameObject::~GameObject() { delete model; delete shader; }

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

void GameObject::shaderSettings(const glm::mat4 & vpmat) const {
	shader->use_program();
	shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
	shader->setUniformMat4f("u_MVP", vpmat * modelMatrix());
}

void GameObject::draw() const {
	Renderer::draw(model, shader);
}

void GameObject::update(double delta) {
	static double totalDelta = 0;

	totalDelta += delta;
	constexpr auto RATE = 1.41;
	auto x = std::cos(totalDelta / RATE);
	auto y = std::sin(totalDelta / RATE);
	setPosition(Vec3d(x, y, 0));
}
