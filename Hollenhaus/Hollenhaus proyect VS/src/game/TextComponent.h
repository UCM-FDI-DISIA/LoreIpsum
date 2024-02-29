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
	~TextComponent();
	void initComponent() override;
	void render() const override;
	
	// Método público para cambiar el texto
	void setTxt(std::string txt);

	// Método público para cambiar el color
	void setColor(SDL_Color color);


private:


	Transform* tr_;
	SDLUtils& sdl_ = *SDLUtils::instance();

	Texture* text_;
	Font* font_;
	SDL_Color color_;

	std::string txt_;

	void createTexture(std::string txt, Font* font, SDL_Color color);
};

