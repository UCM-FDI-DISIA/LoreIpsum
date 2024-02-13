#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Texture* _text): texture(_text)
{};

// Para inicializar el componenete si es necesario.
void SpriteRenderer::initCompomnent() {
	rect.h = texture->height();
	rect.w = texture->width();

};

// Para renderizar el estado
void SpriteRenderer::render() const {
	texture->render()
};