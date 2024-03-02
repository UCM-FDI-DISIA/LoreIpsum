#include "TextComponent.h"
#include "Transform.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color, Alignment alignment) :
	text_(nullptr),
	color_(color),
	font_(&sdl_.fonts().at(fontID)),
	alignment_(alignment)
{
	if (txt.empty()) txt_ = " ";
	else txt_ = txt;
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

	float h = text_->height();
	float w = text_->width();

	switch (alignment_)
	{
	case TextComponent::Left:
		text_->render(tr_->getGlobalPos().getX(), tr_->getGlobalPos().getY() - h/2);
		break;
	case TextComponent::Right:
		text_->render(tr_->getGlobalPos().getX() - w, tr_->getGlobalPos().getY() - h/2);
		break;
	case TextComponent::Center:
		text_->render(tr_->getGlobalPos().getX() - w/2, tr_->getGlobalPos().getY() - h / 2);
		break;
	default:
		break;
	}
	
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

void TextComponent::setAlignment(Alignment alignment)
{
	alignment_ = alignment;
}

void TextComponent::createTexture(std::string txt, Font* font, SDL_Color color) {

	if(text_!= nullptr)
		delete text_;
	
	text_ = new Texture(sdl_.renderer(), txt_, *font_, color_);
}

