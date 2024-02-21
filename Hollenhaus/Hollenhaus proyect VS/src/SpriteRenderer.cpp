#include "SpriteRenderer.h"
#include "game/Manager.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(const std::string& _textPath): texturePath_(_textPath)
{
	initComponent();
};

SpriteRenderer::SpriteRenderer(const std::string _textID) : textID_(_textID) {
}

// Para inicializar el componenete si es necesario.
void SpriteRenderer::initComponent() {
	texture_ = &sdl_.images().at(textID_);

	//requiere component? // si no tiene transform, crea uno 

	transform_ = mngr_->getComponent<Transform>(ent_);
	if (transform_ == nullptr) {
		transform_ = mngr_->addComponent<Transform>(ent_);
	}
};

// Para renderizar el estado
void SpriteRenderer::render() const
{
	texture_->render(transform_->getGlobalPos().getX(),
	                 transform_->getGlobalPos().getY(),
	                 transform_->getGlobalScale().getX(),
	                 transform_->getGlobalScale().getY(),
	                 transform_->getGlobalAngle());
};
