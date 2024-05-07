#pragma once

class TextComponent;

class ClickableText : public ComponentUpdate
{
	TextComponent* textComp_ = nullptr;
	BoxCollider* boxCol_ = nullptr;

	SDL_Color originalColor{0, 0, 0, 0};
	SDL_Color clickedColor{0, 0, 0, 0};
	SDL_Color hoverColor{0, 0, 0, 0};

	bool isClicked = false;

public:
	ClickableText() = default;

	ClickableText(SDL_Color first, SDL_Color click) : originalColor(first), clickedColor(click)
	{
	}

	ClickableText(SDL_Color first, SDL_Color click, SDL_Color hover)
		: originalColor(first), clickedColor(click), hoverColor(hover)
	{
	}

	~ClickableText() override;

	void setTextComponent(TextComponent* v) { textComp_ = v; }
	void setBoxCollider(BoxCollider* v) { boxCol_ = v; }
	TextComponent* getTextComponent() const { return textComp_; }
	BoxCollider* getBoxCollider() const { return boxCol_; }

	void onClickDown();
	void onClickUp();
	void initComponent() override;
	void update() override;
	static bool compareColors(SDL_Color, SDL_Color);
};
