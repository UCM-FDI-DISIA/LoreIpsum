#pragma once
#include "game/ComponentRender.h"
#include "sdlutils/SDLUtils.h"

class Transform;

class SpriteRenderer : public ComponentRender
{
public:
	/// <summary>
	/// Constructora que busca la textura
	/// </summary>
	/// <param name="_textPath"> Path a la textura </param>
	SpriteRenderer(const std::string& _textPath);
	/// <summary>
	/// Constructora usa textura json
	/// </summary>
	/// <param name="textID"> ID de la textura en el Json </param>
	SpriteRenderer(const char* _textID);

	// Para inicializar el componenete si es necesario.
	void initComponent() override;

	// Para renderizar el estado
	void render() const override;

	// Getter textura
	Texture* getTexture() {
		return texture_;
	}

private:
	void initFindTexture();

	// Instancia del singleton
	SDLUtils& sdl_ = *SDLUtils::instance();

	// Puntero al componente transform
	Transform* transform_ = nullptr;

	// Path a la textura
	std::string texturePath_; 
	// ID de la textura
	char* textID_;

	// Puntero a la textura
	Texture* texture_ = nullptr;


};

