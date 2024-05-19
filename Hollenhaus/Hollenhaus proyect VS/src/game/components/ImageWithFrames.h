#pragma once
#include <SDL_stdinc.h>
#include "../../sdlutils/Texture.h"
constexpr int FRAME_SPEED = 300	;

class ImageWithFrames : public ComponentUpdate
{
	Texture* image_ = nullptr;
	SpriteRenderer* spriteRend_ = nullptr;

	// 85 x 100
	int currentRow_; // fila actual
	int currentCol_; // columna actual

	float frameWidth_; // anchura de los frames
	float frameHeight_; // altura de los frames

	int nRows_; // número de filas
	int nCols_; // número de columnas

	Uint32 frameTimer; // contador del tiempo

	int frameSpeed;

public:

	ImageWithFrames() = default;
	ImageWithFrames(int, int, int = FRAME_SPEED);
	ImageWithFrames(SpriteRenderer*, int, int, int = FRAME_SPEED);
	~ImageWithFrames() override;
	void initComponent() override;
	void update() override;
	void syncRenderer();


	void setFrameSpeed(int speed) { frameSpeed = speed; }
	void setCurrentCol(int col) { currentCol_ = col;}
	void setCurrentRow(int row) { currentRow_ = row;}
};
