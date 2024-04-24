#pragma once
#include "../ComponentUpdate.h"
#include <list>

struct Animationl
{
	float from;
	float to;
	float duration;
	tweeny::easing via;
};

class AnimatorManager : public ComponentUpdate
{
private:
	std::list<Animationl> animationlist;

public:
	AnimatorManager();
	~AnimatorManager() override;
	void update() override;
	void addAnimation(Animationl);
};
