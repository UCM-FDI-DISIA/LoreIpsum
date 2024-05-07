#pragma once


/// \brief Componente para cambiar la imagen del spriterenderer al hacer click en la entidad
class Clickable : public ComponentUpdate
{
	SpriteRenderer* spriteRend_ = nullptr;
	BoxCollider* boxCol_ = nullptr;

	std::string firstFrame;
	std::string lastFrame;
	std::string hoverFrame;

	bool isClicked = false;

public:
	Clickable() = default;
	Clickable(std::string first, bool hasHover = false) : firstFrame(first)
	{
		lastFrame = first + "_click";
		if (hasHover)
			hoverFrame = first + "_hover";
	}
	Clickable(std::string first, std::string last, bool hasHover = false)
		: firstFrame(first), lastFrame(last)
	{
		if (hasHover) 
			hoverFrame = first + "_hover";
	}
	Clickable(std::string first, std::string last, std::string hover)
		: firstFrame(first), lastFrame(last), hoverFrame(hover)
	{

	}
	~Clickable() override;

	void setSpriteRenderer(SpriteRenderer* v) { spriteRend_ = v; }
	void setBoxCollider(BoxCollider* v) { boxCol_ = v; }
	SpriteRenderer* getSpriteRenderer() const { return spriteRend_; }
	BoxCollider* getBoxCollider() const { return boxCol_; }

	void onClickDown();
	void onClickUp();
	void initComponent() override;
	void update() override;

};
