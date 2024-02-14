#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string & _textPath): texturePath(_textPath)
{
	initCompomnent();
};

// Para inicializar el componenete si es necesario.
void SpriteRenderer::initCompomnent() {
	texture = new Texture(sdl.renderer(), texturePath);
};

// Para renderizar el estado
void SpriteRenderer::render() const {
	texture->render(transform->getPos().getX(),
		transform->getPos().getY(),
		transform->getScale().getX(),
		transform->getScale().getY(),
		transform->getAngle());
};