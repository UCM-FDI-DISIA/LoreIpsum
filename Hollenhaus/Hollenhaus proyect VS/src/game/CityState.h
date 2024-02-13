#include "GameState.h"
class CityState : public GameState
{
public:
	virtual void Update();
	virtual void Render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_cityID; }
private:
	static const std::string s_cityID;
};