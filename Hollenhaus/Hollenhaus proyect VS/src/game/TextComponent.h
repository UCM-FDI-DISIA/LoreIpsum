#pragma once
#include "ComponentRender.h"
#include "../../../Libraries/SDL2_ttf/include/SDL_ttf.h"
#include "../sdlutils/SDLUtils.h"
#include <string>

class Transform;

class TextComponent : public ComponentRender
{
public:
	TextComponent(std::string txt, std::string fontID, SDL_Color color);

	void initComponent() override;
	void render() const override;
	
private:

	void setTexture(std::string textStr, const Font* font, SDL_Color color);

	Transform* tr_;
	SDLUtils& sdl_ = *SDLUtils::instance();

	Texture* text_;
	Font* font_;
	SDL_Color color_;

	std::string txt_;


};

