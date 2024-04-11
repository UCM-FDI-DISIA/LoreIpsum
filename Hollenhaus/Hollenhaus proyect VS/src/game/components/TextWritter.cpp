#include "pch.h"
#include "TextWritter.h"
#include "basics/TextComponent.h"

TextWritter::TextWritter()
{
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
	
	std::string text = tc->getText();
	text = text + s;
	tc->setTxt(text);
}

void TextWritter::DeleteLastChar()
{
	std::string text = tc->getText();
	if (text.size() > 1) {
		text.pop_back();
		tc->setTxt(text);
	}
}
