#include "TextComponent.h"
#include "Transform.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color)
{
	color_ = color;
	txt_ = txt;
	font_ = &sdl_.fonts().at(fontID);
}

void TextComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();

	
}

void TextComponent::render() const
{
	font_->renderText(txt_, color_);
}
