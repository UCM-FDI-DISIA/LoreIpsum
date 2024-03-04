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

	// El atributo es seteado en init porque necesita el transform
	renderPos_ = GetRenderPosAcordingPivotPoint();
}

void TextComponent::render() const
{
	text_->render(renderPos_.getX(), renderPos_.getY());

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

void TextComponent::SetBoxPivotPoint(BoxPivotPoint boxPivotPoint)
{
	boxPivotPoint_ = boxPivotPoint;
	createTexture();
	renderPos_ = GetRenderPosAcordingPivotPoint();
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

Vector2D TextComponent::GetRenderPosAcordingPivotPoint() const
{
	float x = 0;
	float y = 0;
	float h = text_->height();
	float w = text_->width();

	switch (boxPivotPoint_)
	{
	case TextComponent::LeftTop:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY();
		break;
	case TextComponent::LeftCenter:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case TextComponent::LeftBot:
		x = tr_->getGlobalPos().getX();
		y = tr_->getGlobalPos().getY() - h;
		break;
	case TextComponent::RightTop:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY();
		break;
	case TextComponent::RightCenter:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case TextComponent::RightBot:
		x = tr_->getGlobalPos().getX() - w;
		y = tr_->getGlobalPos().getY() - h;
		break;
	case TextComponent::CenterTop:
		x = tr_->getGlobalPos().getX() - w / 2;
		y = tr_->getGlobalPos().getY();
		break;
	case TextComponent::CenterCenter:
		x = tr_->getGlobalPos().getX() - w / 2;
		y = tr_->getGlobalPos().getY() - h / 2;
		break;
	case TextComponent::CenterBot:
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
	SDL_Rect textRect = { renderPos_.getX(), renderPos_.getY(), text_->width(), text_->height() };

	//render debug
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 255, 255);
	SDL_RenderDrawRect(sdlutils().renderer(), &textRect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
}

