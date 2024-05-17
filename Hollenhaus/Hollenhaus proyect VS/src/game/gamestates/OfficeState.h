#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class Factory;

class OfficeState : public GameState
{
public:

	OfficeState();		//Constructora
	OfficeState(bool t);	// constructora tutorial
	~OfficeState() { }
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPauseOF();

	// -------------- tutorial --------------------
	void setTutorial();
	void prepareTutorial();
	void startTutorial(bool a);

private:
	Factory* factory;

	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU

	bool isTutorial;
};

