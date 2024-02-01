#ifndef Button_H_
#define Button_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <functional>


#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include "Vector2D.h"

using Callback = std::function<void(void)>;


class Button : public  GameObject , public EventHandler {
	
	//imagen del boton
	Texture* texture;

	//posicion
	Point2D<> pos;

	int width;
	int height;

	//Rect para detectar si el mouse esta encima
	SDL_Rect myRect;

	bool hover = false;
	

	std::list<Callback> callbackList;


	void emit() const;

public:

	//constructor
	Button(GameState*  game,Texture* texture,Point2D<> pos);


	void connect(Callback c);
	
	void handleEvent(const SDL_Event& ev) override;

	
	void Render() const override;

 	void Update() override;


	//save vacio
	void Save(std::ostream& out) const override{};
};




#endif // !Button_H_

