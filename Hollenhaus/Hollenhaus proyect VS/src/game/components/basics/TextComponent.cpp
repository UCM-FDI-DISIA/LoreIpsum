#include "pch.h"
#include "TextComponent.h"
#include "Transform.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../Entity.h"

TextComponent::TextComponent(std::string txt, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint, Text::TextAlignment textAlignment) :
	text_(nullptr),
	color_(color),
	font_(&sdl_.fonts().at(fontID)),
	wrapLenght_(wrapLenght),
	boxPivotPoint_(boxPivotPoint),
	textAlignment_(textAlignment),
	txt_(txt)
{

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

	// El atributo es seteado en init porque necesita el transform
	renderPos_ = GetRenderPosAcordingPivotPoint();
}

void TextComponent::render() const
{

	//PROVISIONAL
	Vector2D aux  = GetRenderPosAcordingPivotPoint();

	text_->render(aux.getX(), aux.getY());

#ifdef _DEBUG
	RenderDebugRect( 0, 0, 255, 255 );
#endif // DEBUG
	
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

void TextComponent::SetBoxPivotPoint(Text::BoxPivotPoint boxPivotPoint)
{
	boxPivotPoint_ = boxPivotPoint;
	createTexture();
	renderPos_ = GetRenderPosAcordingPivotPoint();
}

void TextComponent::SetTextAlignment(Text::TextAlignment textAlignment)
{
	textAlignment_ = textAlignment;
	// No hace falta crear textura nueva
}

void TextComponent::createTexture() {

	if(text_!= nullptr)
		delete text_;
	
	std::string texto = txt_;
	if (txt_.empty())
		texto = " ";

	// Se utiliza una nueva constructora específica para crear una textura a partir de un texto embebido en una caja
	text_ = new Texture(sdl_.renderer(), texto, *font_, color_, wrapLenght_, textAlignment_);
}

Vector2D TextComponent::GetRenderPosAcordingPivotPoint() const
{
	float x = 0;
	float y = 0;
	float h = text_->height();
	float w = text_->width();

	switch (boxPivotPoint_)
	{
	case Text::LeftTop:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY();
		break;
	case Text::LeftCenter:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case Text::LeftBot:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY() - h;
		break;
	case Text::RightTop:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY();
		break;
	case Text::RightCenter:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case Text::RightBot:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY() - h;
		break;
	case Text::CenterTop:
		x = tr_->getGlobalPos().getX() - w / 2;
		y = tr_->getGlobalPos().getY();
		break;
	case Text::CenterCenter:
		x = tr_->getGlobalPos().getX() - w / 2;
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case Text::CenterBot:
		x = tr_->getGlobalPos().getX() - w / 2;
		y = tr_->getGlobalPos().getY() - h;
		break;
	default:
		break;
	}
	return Vector2D(x, y);
}

void TextComponent::RenderDebugRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_Rect textRect = {
		(int)renderPos_.getX(),
		(int)renderPos_.getY(),
		text_->width(),
		text_->height()
	};

	//render debug
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 255, 255);
	SDL_RenderDrawRect(sdlutils().renderer(), &textRect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
}

