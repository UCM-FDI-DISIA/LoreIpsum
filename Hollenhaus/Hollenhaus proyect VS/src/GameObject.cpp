#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "GameObject.h"
#include "GameState.h"
#include "PlayState.h"

GameObject::GameObject(GameState* game) : game(game) {};

GameObject::GameObject(PlayState* game) : game(game) {};