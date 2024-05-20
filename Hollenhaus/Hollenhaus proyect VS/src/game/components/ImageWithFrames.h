#pragma once
#include <SDL_stdinc.h>
#include "../../sdlutils/Texture.h"
constexpr int FRAME_SPEED = 300	;

using SDLEventCallback = std::function<void(void)>;
class ImageWithFrames : public ComponentUpdate
{
	Texture* image_ = nullptr;
	SpriteRenderer* spriteRend_ = nullptr;

	int currentRow_; // fila actual
	int currentCol_; // columna actual

	float frameWidth_; // anchura de los frames
	float frameHeight_; // altura de los frames

	int nRows_; // número de filas
	int nCols_; // número de columnas

	Uint32 frameTimer; // contador del tiempo

	int frameSpeed;

	int loops; // veces que se loopea (-1 infinito)

	// ---- CALLBACKS ----
	std::list<SDLEventCallback> callbacks;
	bool callbacksExecuted;
	void useCallback() const;

public:

	ImageWithFrames() = default;
	ImageWithFrames(int, int, int, int = FRAME_SPEED);
	ImageWithFrames(SpriteRenderer*, int, int, int, int = FRAME_SPEED);
	~ImageWithFrames() override;
	void initComponent() override;
	void update() override;
	void syncRenderer();

	void setSprite(std::string, int = -1);
	void setFrameSpeed(int speed) { frameSpeed = speed; }
	void setCurrentCol(int col) { currentCol_ = col;}
	void setCurrentRow(int row) { currentRow_ = row;}
	void setLoops(int loop) { loops = loop; }

	// Add callback
	void addCallback(SDLEventCallback _callback);
};
