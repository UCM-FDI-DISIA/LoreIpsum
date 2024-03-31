#include "GameState.h"

class CityState : public GameState
{
public:

	CityState(); //Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
};