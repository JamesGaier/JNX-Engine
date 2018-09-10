#include "TexturedGameObject.h"

TexturedGameObject::TexturedGameObject(Model* m, const std::string& textureLocation) : GameObject(m) {
	texture = new Texture(textureLocation);
}

TexturedGameObject::TexturedGameObject(const std::string& modelLocation) : GameObject(modelLocation) {}

TexturedGameObject::~TexturedGameObject() {
	delete texture;
}

void TexturedGameObject::shaderSettings(Shader* shader, const glm::mat4& vpmat) {
	texture->Bind(1);
	shader->setUniform1i("u_Texture", 1);
	shader->setUniformMat4f("u_MVP", vpmat * modelMatrix());
}

void TexturedGameObject::update(double delta) {
	
	static double totalDelta = 0;
	totalDelta += delta;
	
	constexpr auto RATE = 1.41;
	auto x = std::cos(totalDelta / RATE);
	auto y = std::sin(totalDelta / RATE);
	setPosition(Vec3d(x, y, 0));
}
