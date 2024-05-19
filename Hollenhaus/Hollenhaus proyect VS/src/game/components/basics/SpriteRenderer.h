#pragma once

//Checkml
#include <game/checkML.h>

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
	void setMultiplyColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) { 
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setMultiplyColor(SDL_Color scolor) { 
		color = scolor;
	}

	void setOpacity(int alpha) { opacity = alpha; }
	int getOpacity() const { return opacity; }

	// Para inicializar el componenete si es necesario.
	void initComponent() override;

	// Para renderizar el estado
	void render() const override;

	Vector2D getImageSize();

	// Getter textura
	Texture* getTexture() {
		return texture_;
	}

	void setAnimated(bool v) { isAnimated = v; }
	bool getAnimated() const { return isAnimated; }
	void setSourceRect(SDL_Rect r) { sourceRect = r;}
	SDL_Rect getSourceRect() const { return sourceRect; }
	void setRows(int n) { nRows = n; }
	void setCols(int n) { nCols = n; }
	void setOffset(float x, float y) { offset = { x, y };}

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

	// Alfa de la textura
	int opacity = 255;

	Vector2D offset = { 0, 0};

	/// animaciones
	bool isAnimated = false;
	SDL_Rect sourceRect = { 0, 0, 0, 0 };
	SDL_Rect destRect = { 0, 0, 0, 0 };
	int nRows;
	int nCols;
};

