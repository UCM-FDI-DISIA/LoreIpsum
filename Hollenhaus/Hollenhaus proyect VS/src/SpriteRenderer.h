#pragma once
#include "game/ComponentRender.h"
#include "sdlutils/SDLUtils.h"
#include "Transform.h"

class SpriteRenderer : public ComponentRender
{
public:
	/// <summary>
	/// Constructora que busca la textura
	/// </summary>
	/// <param name="_textPath"> Path a la textura </param>
	SpriteRenderer(const std::string &_textPath);

	// Para inicializar el componenete si es necesario.
	void initCompomnent() override;

	// Para renderizar el estado
	void render() const override;

private:
	// Instancia del singleton
	SDLUtils& sdl = *SDLUtils::instance();

	// Puntero al componente transform
	Transform* transform = nullptr;

	// Path a la textura
	std::string texturePath;

	// Puntero a la textura
	Texture* texture = nullptr;


};

