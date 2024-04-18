#pragma once

#pragma region Pch original

/*

//c++ basico
#include <iostream>
#include <fstream>
#include <string>

//tads de c++
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

//sdl 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//sdlUtils


#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Music.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"


//ecs


//#include "Game.h"
//#include "GameState.h"
//#include "Entity.h"
//#include "Manager.h"
//#include "GameStateMachine.h"
#include "ecs.h"



//components
/*
#include "ComponentRender.h"
#include "ComponentUpdate.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "SpriteRenderer.h"
#include "TextComponent.h"
*/


#pragma endregion


//para json y utils
#pragma region pch_c++_basic

/*
//c++ basico
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cwctype>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <cassert>
#include <memory>


//tads de c++
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

*/


#pragma endregion

//para sdl utils
#pragma region pch_SDL

/*
//c++ basico
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cwctype>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <cassert>
#include <memory>


//tads de c++
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

//sdl 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

*/


#pragma endregion

//para el resto del proyecto
#pragma region Pch_SDL_Utils


//c++ basico
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cwctype>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <cassert>
#include <memory>


//tads de c++
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

//sdl 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


//sdlUtils
//este incluye la mayoria de los include de sdl_Utils(expcepto algunos como sdl_net)
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

//entity component sistem
#include "ecs.h"
#include "Namespaces.h"
#include "components/managers/Manager.h"
#include "../utils/tweeny-3.2.0.h"


#pragma endregion



