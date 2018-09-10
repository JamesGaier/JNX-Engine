#ifndef _TEXTURED_GAME_OBJECT
#define _TEXTURED_GAME_OBJECT

#include "rendering/Texture.h"
#include "GameObject.h"

class TexturedGameObject : public GameObject {
private:
	Texture* texture;

public:
	TexturedGameObject(Model* m, const std::string& textureLocation);
	TexturedGameObject(const std::string& modelLocation);
	virtual ~TexturedGameObject();

	virtual void shaderSettings(Shader* shader, const glm::mat4& vpmat) override;
	virtual void update(double delta) override;
};

#endif // !_TEXTURED_GAME_OBJECT
