#pragma once
#include "basics/TextComponent.h"

class FadeComponent : public ComponentUpdate
{
public:
	FadeComponent();
	~FadeComponent() override;

	void initComponent() override;
	void update() override;

	void setFadeInFalse();
	void setFadeOutTrue();

	bool getFadeIn() { return fadeIn; }
	bool getFadeOut() { return fadeOut; }

	float getProgress() { return fadetween.progress(); }
	

private:
	SpriteRenderer* f = nullptr;
	TextComponent* t = nullptr;
	tweeny::tween<int> fadetween;

	bool fadeIn;
	bool fadeOut;

	bool isText = false;
	bool isImage = false;
};
