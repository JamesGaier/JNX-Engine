#ifndef _TEXTURED_GAME_OBJECT
#define _TEXTURED_GAME_OBJECT

#include "rendering/Texture.h"
#include "GameObject.h"

class TexturedGameObject : public GameObject {
private:
	std::unique_ptr<Texture> texture;

public:
	TexturedGameObject(Model* m, const std::string& textureLocation);

	virtual void shaderSettings(const glm::mat4& vpmat) const override;
	virtual void update(double delta) override;
};

#endif // !_TEXTURED_GAME_OBJECT
