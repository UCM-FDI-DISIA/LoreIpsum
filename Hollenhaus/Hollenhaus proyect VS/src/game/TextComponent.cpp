#include "TextComponent.h"
#include "Transform.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color)
{
	text_ = nullptr;
	color_ = color;
	if (txt.empty()) txt_ = " ";
	else txt_ = txt;	
	font_ = &sdl_.fonts().at(fontID);
	createTexture(txt_, font_, color_);
}

TextComponent::~TextComponent()
{
	delete text_;
}

void TextComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void TextComponent::render() const
{
	// Necesita un compomente transform.
	text_->render(tr_->getGlobalPos().getX(), tr_->getGlobalPos().getY());
}

void TextComponent::setTxt(std::string txt)
{
	txt_ = txt;
	createTexture(txt_, font_, color_);
}

void TextComponent::setColor(SDL_Color color)
{
	color_ = color;
	createTexture(txt_, font_, color_);
}

void TextComponent::createTexture(std::string txt, Font* font, SDL_Color color) {

	if(text_!= nullptr)
		delete text_;
	
	text_ = new Texture(sdl_.renderer(), txt_, *font_, color_);
}

