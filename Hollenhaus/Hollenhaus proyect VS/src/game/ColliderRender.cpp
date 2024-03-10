#include "pch.h"
#include "ColliderRender.h"
#include "../sdlutils/SDLUtils.h"
#include "Manager.h"
#include "Transform.h"
#include "BoxCollider.h"



ColliderRender::ColliderRender()
{
}


ColliderRender::~ColliderRender()
{
}

void ColliderRender::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
}

void ColliderRender::render() const
{
	//render debug
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(sdlutils().renderer(), myBoxCollider->getRect());
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
}
