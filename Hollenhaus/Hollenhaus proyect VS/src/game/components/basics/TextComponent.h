#pragma once
#include "../../pch.h"

#include "../ComponentRender.h"
#include <string>

class Transform;


class TextComponent : public ComponentRender
{
public:



	/// <summary>
	/// Constructora para crear un componente texto.
	/// Las propiedades del texto están definidas en los parámetros de la constructora.
	/// El componente se encarga de renderizar el texto acorde a los parámetros introducidos.
	/// 
	/// El parámetro BoxPivotPoint puede tener los siguientes valores:
	///		LeftTop
	///		LeftCenter
	///		LeftBot
	///		RightTop
	///		RightCenter
	///		RightBot
	///		CenterTop
	///		Center
	///		CenterBot
	/// 
	/// El parámetro TextAlignment puede tener los siguientes valores:
	/// 	Left
	///		Center
	///		Right
	/// 
	/// </summary>
	/// <param name="txt"> Texto a generar </param>
	/// <param name="fontID"> Fuente empleada para el texto. Debe ser cargada en "resources.json" </param>
	/// <param name="color"> Color del texto </param>
	/// <param name="wrapLenght"> Longitud horizontal de la caja en la que se envuelve el texto </param>
	/// <param name="boxPivotPoint"> Punto de pivote de la caja en la que se envuelve el texto </param>
	/// <param name="textAlignment"> Alineación del texto respecto a la caja en la que se envuelve </param>
	TextComponent(std::string txt, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint = Text::LeftTop, Text::TextAlignment textAlignment = Text::Left);
	
	~TextComponent();
	void initComponent() override;
	void render() const override;
	
	// Método público para cambiar el texto
	void setTxt(std::string txt);

	// Método público para cambiar el color
	void setColor(SDL_Color color);

	// Método público para cambiar la longitud horizontal de la caja
	void setWrapLenght(Uint32 wrapLenght);

	// Método público para cambiar el punto de pivote de la caja
	void SetBoxPivotPoint(Text::BoxPivotPoint boxPivotPoint);

	// Método público para cambiar la alineación del texto respecto a la caja
	void SetTextAlignment(Text::TextAlignment textAlignment);

private:

	Transform* tr_;
	SDLUtils& sdl_ = *SDLUtils::instance();

	Texture* text_;

	std::string txt_;
	Font* font_;
	SDL_Color color_;
	Uint32 wrapLenght_;
	Text::BoxPivotPoint boxPivotPoint_;
	Text::TextAlignment textAlignment_;
	
	// Atributo y método para calcular la posicion de renderizado según el punto de pivote de la caja de texto
	Vector2D GetRenderPosAcordingPivotPoint() const;
	Vector2D renderPos_;

	void createTexture();

	void RenderDebugRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

};

