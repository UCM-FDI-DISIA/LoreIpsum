#include <../pchs/pch.h>

#include "CasinoState.h"
#include "../components/managers/Manager.h"
#include "../components/ShineComponent.h"
#include "../components/NPC.h"
#include "../GameStateMachine.h"
#include "../components/Button.h"
#include "../../sdlutils/RandomNumberGenerator.h"
#include "../SoundManager.h"

// Factorias:
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"
#include "game/components/Clickable.h"