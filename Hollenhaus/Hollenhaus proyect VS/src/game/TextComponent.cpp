#include "TextComponent.h"
#include "Transform.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color)
{
	color_ = color;
	txt_ = txt;
	font_ = &sdl_.fonts().at(fontID);
	setTexture(txt_, font_, color_);
}

void TextComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	
	
}

void TextComponent::render() const
{
	font_->renderText(txt_, color_);
}

void TextComponent::setTexture(std::string textStr, const Font* font, SDL_Color color) {
	delete text_;
	if (textStr.empty()) textStr = " ";
	
	text_ = new Texture(sdl_.renderer(), txt_, *font_, color_);

	//SDL_Surface* s = font->renderText(textStr, color);
	//text_ = font->generateTexture(textStr, color);
	//w = text_->getFrameWidth();
	//h = text_->getFrameHeight();
	//renderPos = Vector2D<>(centeredPos.GetX() - w / 2, centeredPos.GetY() - h / 2);
}

