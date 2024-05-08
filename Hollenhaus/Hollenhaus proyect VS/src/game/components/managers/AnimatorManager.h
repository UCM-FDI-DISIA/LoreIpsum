#pragma once

//Checkml
#include <game/checkML.h>

#include "../ComponentUpdate.h"
#include <list>

struct Animationl
{
	float from;
	float to;
	float duration;
	tweeny::easing via;
};

class AnimatorManager: public ComponentUpdate
{
private:
	std::list<Animationl> animationlist;
public:
	AnimatorManager();
	~AnimatorManager();
	void update() override;
	void addAnimation(Animationl);
};
