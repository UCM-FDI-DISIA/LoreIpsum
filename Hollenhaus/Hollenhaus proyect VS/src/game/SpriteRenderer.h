#pragma once
#include "ComponentRender.h"
#include "../sdlutils/SDLUtils.h"

class Transform;
class BoxCollider;

class SpriteRenderer : public ComponentRender
{
public:
	/// <summary>
	/// Constructora usa textura json
	/// </summary>
	/// <param name="textID"> ID de la textura en el Json </param>
	SpriteRenderer(const std::string _textID);

	/// <summary>
	/// Cambiar la textura en ejecucion
	/// </summary>
	/// <param name="_textID">ID de la textura en el Json</param>
	void setTexture(const std::string _textID);

	/// <summary>
	/// Prioriza el flipe de la X si "X" e "Y" estan en true, por defecto estan en false;
	/// </summary>
	void setFlipX(bool flip) { flipX_ = flip; }
	/// <summary>
	/// Prioriza el flipe de la X si "X" e "Y" estan en true, por defecto estan en false;
	/// </summary>
	void setFlipY(bool flip) { flipY_ = flip; }

	// Para inicializar el componenete si es necesario.
	void initComponent() override;

	// Para renderizar el estado
	void render() const override;

	// Getter textura
	Texture* getTexture() {
		return texture_;
	}

private:

	// Instancia del singleton
	SDLUtils& sdl_ = *SDLUtils::instance();

	// Puntero al componente transform
	Transform* transform_ = nullptr;

	// ID de la textura
	std::string textID_;

	// Puntero a la textura
	Texture* texture_ = nullptr;

	// FLip bools
	bool flipX_;
	bool flipY_;


};

