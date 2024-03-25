#include "pch.h"
#include "BoxCollider.h"
#include "../managers/Manager.h"
#include "Transform.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string _textID) :
	textID_(_textID),
	flipX_(false),
	flipY_(false)
{
}

// Para inicializar el componenete si es necesario.
void SpriteRenderer::initComponent() {
	texture_ = &sdl_.images().at(textID_);
	setMultiplyColor(255, 255, 255, 0);

	//requiere component? // si no tiene transform, crea uno 

	transform_ = mngr_->getComponent<Transform>(ent_);
	if (transform_ == nullptr) {
		transform_ = mngr_->addComponent<Transform>(ent_);
	}
};

void SpriteRenderer::setTexture(const std::string _textID) {
	textID_ = _textID;
	texture_ = &sdl_.images().at(textID_);
}

void SpriteRenderer::setTexture(Texture* _textu)
{
	texture_ = _textu;
}

// Para renderizar la textura
void SpriteRenderer::render() const
{
	// Settea el flip de la textura.
	SDL_RendererFlip flip;
	if (flipX_)
		flip = SDL_FLIP_HORIZONTAL;
	else if (flipY_)
		flip = SDL_FLIP_VERTICAL;
	else
		flip = SDL_FLIP_NONE;

	// Llama a un render custom con todo lo que nos hace falta.
	texture_->render(transform_->getGlobalPos().getX(),
		transform_->getGlobalPos().getY(),
		transform_->getGlobalScale().getX(),
		transform_->getGlobalScale().getY(),
		transform_->getGlobalAngle(),
		flip,
		color);
};
