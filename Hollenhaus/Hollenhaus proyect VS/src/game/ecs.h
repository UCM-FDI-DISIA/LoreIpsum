// Basado en el codigo para TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>

#include "GenID.h"

#pragma region Define lists


// Components Update list - must have at least one element
//
#define _CMPS_U_LIST_ \
	TRANSFORM, \
	IMAGE
// Components Render list - must have at least one element
//
#define _CMPS_R_LIST_ \
	TRANSFORM, \
	IMAGE

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	CARDS, \
	DROPS, \
	COINS, \
	DROPZONE

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    MATCH_MANAGER, \
	PADDLE, \
	TUTORIAL_MANAGER, \
    DRAG_MANAGER

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    COLLISION, \
	RENDER

#pragma endregion


namespace ecs {

// forward declaration of some classes, to be used when we
// just need to know that they exist
struct Component;
struct Entity;
class Manager;
class System;

using entity_t = Entity*;

// We define type for the identifiers so we can change them easily.
// For example, if we have less than 256 components we can use one
// byte, i.e. uint8_t, if we have up to 512 we can use uint16_t,
// and so on ...
//
using cmpId_t = uint8_t;
using grpId_t = uint8_t;
using hdlrId_t = uint8_t;
using sysId_t = uint8_t;

// we use a name space for the components enum to avoid conflicts
namespace cmpU {

// list of component identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum cmpUId : cmpId_t {
	_CMPS_U_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_CMP_ID
};
}

namespace cmpR {

// list of component identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum cmpRId : cmpId_t {
	_CMPS_R_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_CMP_ID
};
}


namespace grp {
// list of group identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum grpId : cmpId_t {
	DEFAULT,
	_GRPS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_GRP_ID
};
}

namespace hdlr {
// list of handler identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum hdlrId : hdlrId_t {
	_HDLRS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_HDLR_ID
};
}

namespace sys {
// list of system identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum sysId : hdlrId_t {
	_SYS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_SYS_ID
};
}

// GetID stuff

constexpr cmpId_t maxComponentUpdateId = 1000;
template<typename T>
cmpId_t cmpUpdateId = GenID::getUpdateId<T>();

constexpr cmpId_t maxComponentRenderId = 100;
template<typename T>
cmpId_t cmpRenderId = GenID::getRenderId<T>();


//IDs max
constexpr cmpId_t maxGroupId = grp::grpId::_LAST_GRP_ID;
constexpr hdlrId_t maxHandlerId = hdlr::hdlrId::_LAST_HDLR_ID;
constexpr sysId_t maxSystemId = sys::sysId::_LAST_SYS_ID;


// a template variable to obtain the system id.
template<typename T>
constexpr sysId_t sysId = T::id;

// a macro for component identifier declaration, e.g., __CMPID_DECL__(ecs::cmp::TRANSFORM)
// expands to:
//
//   constexpr static ecs::cmpId_t id = ecs::cmp::TRANSFORM;
//
#define __CMPID_DECL__(cId) constexpr static ecs::cmpId_t id = cId;

// a macro for system identifier declaration, e.g., __SYSID_DECL__(ecs::sys::ASTEROIDS)
// expands to:
//
//   constexpr static ecs::sysId_t id = ecs::sys::ASTEROIDS;
//
#define __SYSID_DECL__(cId) constexpr static ecs::sysId_t id = cId;

} // end of namespace

