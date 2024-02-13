#pragma once
#include "game/ComponentRender.h"
#include "sdlutils/SDLUtils.h"
#include "Transform.h"

class SpriteRenderer : public ComponentRender
{
public:
	SpriteRenderer(Texture* _text);

	// Para inicializar el componenete si es necesario.
	void initCompomnent() override;

	// Para renderizar el estado
	void render() const override;

private:
	// Componente transform
	Transform* transform = nullptr;

	Texture* texture = nullptr;
	SDL_Rect rect;

};

