#include "pch.h"
#include "TextWritter.h"
#include "basics/TextComponent.h"


TextWritter::TextWritter()
{
	text = "";
}

TextWritter::~TextWritter()
{
}

void TextWritter::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
}

void TextWritter::update()
{

}

void TextWritter::UpdateText(std::string s)
{
	text = text + s;
	tc->setTxt(text);
}
