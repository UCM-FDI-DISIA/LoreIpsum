#pragma once
#include "../Fade.h"

class FadeComponent : public ComponentUpdate
{
public:
	FadeComponent();
	~FadeComponent() override;

	void initComponent() override;
	void update() override;

	void FadeIn();

	bool getFadeIn() { return fadeIn; }
	

private:
	SpriteRenderer* f;
	tweeny::tween<int> fadetween;

	bool fadeIn;
	bool fadeOut;

};
