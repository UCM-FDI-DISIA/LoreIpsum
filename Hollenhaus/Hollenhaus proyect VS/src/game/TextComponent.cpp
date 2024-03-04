#include "TextComponent.h"
#include "Transform.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color, Uint32 wrapLenght, BoxPivotPoint boxPivotPoint, TextAlignment textAlignment) :
	text_(nullptr),
	color_(color),
	font_(&sdl_.fonts().at(fontID)),
	wrapLenght_(wrapLenght),
	boxPivotPoint_(boxPivotPoint),
	textAlignment_(textAlignment)
{
	if (txt.empty()) txt_ = "11 ";
	else txt_ = txt;

	createTexture();
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

	Vector2D pos = tr_->getGlobalPos();
	SDL_Rect textRect = {pos.getX(), pos.getY(), text_->width(),text_->height() };

	//render debug
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 255, 255);
	SDL_RenderDrawRect(sdlutils().renderer(), &textRect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);

	float x = 0;
	float y = 0;
	float h = text_->height();
	float w = text_->width();

	switch (boxPivotPoint_)
	{
	case TextComponent::LeftTop:
		text_->render(tr_->getGlobalPos().getX(), tr_->getGlobalPos().getY());
		break;
	case TextComponent::LeftCenter:
		text_->render(tr_->getGlobalPos().getX(), tr_->getGlobalPos().getY() - h / 2);
		break;
	case TextComponent::LeftBot:
		text_->render(tr_->getGlobalPos().getX(), tr_->getGlobalPos().getY() - h);
		break;
	case TextComponent::RightTop:
		text_->render(tr_->getGlobalPos().getX() - w, tr_->getGlobalPos().getY());
		break;
	case TextComponent::RightCenter:
		text_->render(tr_->getGlobalPos().getX() - w, tr_->getGlobalPos().getY() - h / 2);
		break;
	case TextComponent::RightBot:
		text_->render(tr_->getGlobalPos().getX() - w, tr_->getGlobalPos().getY() - h);
		break;
	case TextComponent::CenterTop:
		text_->render(tr_->getGlobalPos().getX() - w / 2, tr_->getGlobalPos().getY());
		break;
	case TextComponent::CenterCenter:
		text_->render(tr_->getGlobalPos().getX() - w / 2, tr_->getGlobalPos().getY() - h / 2);
		break;
	case TextComponent::CenterBot:
		text_->render(tr_->getGlobalPos().getX() - w / 2, tr_->getGlobalPos().getY() - h);
		break;
	default:
		break;
	}
}

void TextComponent::setTxt(std::string txt)
{
	txt_ = txt;
	createTexture();
}

void TextComponent::setColor(SDL_Color color)
{
	color_ = color;
	createTexture();
}

void TextComponent::setWrapLenght(Uint32 wrapLenght)
{
	wrapLenght_ = wrapLenght;
	createTexture();
}

void TextComponent::SetBoxPivotPoint(BoxPivotPoint boxPivotPoint)
{
	boxPivotPoint_ = boxPivotPoint;
	createTexture();
}

void TextComponent::SetTextAlignment(TextAlignment textAlignment)
{
	textAlignment_ = textAlignment;
	// No hace falta crear textura nueva
}

void TextComponent::createTexture() {

	if(text_!= nullptr)
		delete text_;
	
	// Se utiliza una nueva constructora específica para crear una textura a partir de un texto embebido en una caja
	text_ = new Texture(sdl_.renderer(), txt_, *font_, color_, wrapLenght_, textAlignment_);
}

