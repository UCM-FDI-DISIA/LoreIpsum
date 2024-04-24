#pragma once

class Fade
{
	Texture* image_;
	int opacity_;
	SDL_Rect rect_ = { 0, 0, sdlutils().width(), sdlutils().height() };

public:
	Fade(int);
	~Fade() = default;

	void render() const;

	void setOpacity(int value) { opacity_ = value; };
	int getOpacity() const { return opacity_;};
};
