#pragma once
#include "../ComponentRender.h"

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

	void setTexture(Texture* _textu);

	/// <summary>
	/// Prioriza el flipe de la X si "X" e "Y" estan en true, por defecto estan en false;
	/// </summary>
	void setFlipX(bool flip) { flipX_ = flip; }
	/// <summary>
	/// Prioriza el flipe de la X si "X" e "Y" estan en true, por defecto estan en false;
	/// </summary>
	void setFlipY(bool flip) { flipY_ = flip; }

	/// <summary>
	/// Settea el color que multiplica
	/// </summary>
	/// <param name="r">Cantidad de rojo 0-255</param>
	/// <param name="g">Cantidad de verde 0-255</param>
	/// <param name="b">Cantidad de azul 0-255</param>
	/// <param name="a">0 - no multiplica, 255 - multiplica todo el color</param>
	void setMultiplyColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0) { 
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

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

	// Color que multiplica la textura
	SDL_Color color;

};

