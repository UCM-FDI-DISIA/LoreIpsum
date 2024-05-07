#pragma once

class ClickableText : public ComponentUpdate
{
	SpriteRenderer* spriteRend_ = nullptr;
	BoxCollider* boxCol_ = nullptr;

	std::string firstFrame;
	std::string lastFrame;

	bool isClicked = false;

public:
	ClickableText() = default;
	ClickableText(std::string first) : firstFrame(first)
	{
		lastFrame = first + "_click";
	}
	ClickableText(std::string first, std::string last)
		: firstFrame(first), lastFrame(last) {}
	~ClickableText() override;

	void setSpriteRenderer(SpriteRenderer* v) { spriteRend_ = v; }
	void setBoxCollider(BoxCollider* v) { boxCol_ = v; }
	SpriteRenderer* getSpriteRenderer() const { return spriteRend_; }
	BoxCollider* getBoxCollider() const { return boxCol_; }

	void onClickDown();
	void onClickUp();
	void initComponent() override;
	
};
