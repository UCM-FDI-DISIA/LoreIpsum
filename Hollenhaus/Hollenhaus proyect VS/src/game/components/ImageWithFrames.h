#pragma once
#include <SDL_stdinc.h>
#include "../../sdlutils/Texture.h"

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

public:

	ImageWithFrames() = default;
	ImageWithFrames(int, int);
	ImageWithFrames(SpriteRenderer*, int, int);
	~ImageWithFrames() override;
	void initComponent() override;
	void update() override;
	void syncRenderer();
};
