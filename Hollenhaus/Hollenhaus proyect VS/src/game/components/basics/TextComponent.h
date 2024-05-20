#pragma once

//Checkml
#include <game/checkML.h>

#include "../ComponentRender.h"
#include <string>

class Transform;


class TextComponent : public ComponentRender
{
public:
	/// <summary>
	/// Constructora para crear un componente texto.
	/// Las propiedades del texto est�n definidas en los par�metros de la constructora.
	/// El componente se encarga de renderizar el texto acorde a los par�metros introducidos.
	/// 
	/// El par�metro BoxPivotPoint puede tener los siguientes valores:
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
	/// El par�metro TextAlignment puede tener los siguientes valores:
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
	/// <param name="textAlignment"> Alineaci�n del texto respecto a la caja en la que se envuelve </param>
	TextComponent(std::string txt, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint = Text::LeftTop, Text::TextAlignment textAlignment = Text::Left);
	
	~TextComponent();
	void initComponent() override;
	void render() const override;
	
	// M�todo p�blico para cambiar el texto
	void setTxt(std::string txt);

	// M�todo p�blico para cambiar el color
	void setColor(SDL_Color color);

	// M�todo p�blico para cambiar la longitud horizontal de la caja
	void setWrapLenght(Uint32 wrapLenght);

	// M�todo p�blico para cambiar el punto de pivote de la caja
	void SetBoxPivotPoint(Text::BoxPivotPoint boxPivotPoint);

	// M�todo p�blico para cambiar la alineaci�n del texto respecto a la caja
	void SetTextAlignment(Text::TextAlignment textAlignment);

	// Metodo publico para cambiar la fuente del componente
	void setFont(const std::string& font) { font_ = &sdl_.fonts().at(font); createTexture(); }


	// GETTERS
	std::string getText() { return txt_; }
	Texture* getTexture() const { return text_; }
	SDL_Color getColor() const { return color_; }
	void setOffset(int x, int y) { offset = Vector2D(x, y); }
	Vector2D getOffset() const { return offset; }
	void setAlpha(int v) { alpha = v; }

	void setRelativeToTransform(bool value) { relativeToTransform = true; } // si la escala depende de la del transform del padre
	Vector2D getScale() const { return scale;}
	void setScale(const Vector2D& s) { scale = s; }

private:

	Transform* tr_ = nullptr;
	SDLUtils& sdl_ = *SDLUtils::instance();

	Texture* text_ = nullptr;

	std::string txt_;
	Font* font_ = nullptr;
	SDL_Color color_;
	Uint32 wrapLenght_;
	Text::BoxPivotPoint boxPivotPoint_;
	Text::TextAlignment textAlignment_;
	
	// Atributo y m�todo para calcular la posicion de renderizado seg�n el punto de pivote de la caja de texto
	Vector2D GetRenderPosAcordingPivotPoint() const;
	Vector2D renderPos_;
	Vector2D offset = { 0, 0 };

	int alpha = 255;
	bool relativeToTransform = false;
	Vector2D scale { 1, 1 };

	void createTexture();
	void RenderDebugRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

};

