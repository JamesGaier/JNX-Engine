#include "TexturedGameObject.h"
#include "Input.h"

TexturedGameObject::TexturedGameObject(Model* m, const std::string& textureLocation) {
	texture = new Texture(textureLocation);
	setModel(m);
	shader = new Shader("res/shaders/textured.shader");
}

TexturedGameObject::~TexturedGameObject() {
	delete texture;
}

void TexturedGameObject::shaderSettings(const glm::mat4& vpmat) const {
	
	shader->use_program();
	texture->Bind(1);
	
	shader->setUniform1i("u_Texture", 1);
	shader->setUniformMat4f("u_MVP", vpmat * modelMatrix());
	shader->setUniform4f("u_Color", 1, 1, 1, 1);
}

void TexturedGameObject::update(double delta) {
	constexpr auto maxSpeed = 50;
	constexpr auto speed = 2.55;

	Vec3d move;
	if(Input::isDown('w')) {
		move.setY(-delta);
	} else if(Input::isDown('s')) {
		move.setY(delta);
	}

	if(Input::isDown('d')) {
		move.setX(delta);
	} else if(Input::isDown('a')) {
		move.setX(-delta);
	}

	move *= speed;
	if(move.magnitudeSquared() > maxSpeed * maxSpeed) {
		auto newMove = move.normalized();
		newMove *= maxSpeed;
		move = newMove;
	}

	auto temp = position();
	temp += move;
	setPosition(temp);
}
