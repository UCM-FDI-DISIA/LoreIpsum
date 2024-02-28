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

	Transform* tr_;
	SDLUtils& sdl_ = *SDLUtils::instance();

	Font* font_;
	SDL_Color color_;

	std::string txt_;


};

