#pragma once

using cmpId_type = int;
enum cmpId : cmpId_type {
	// ... (compoment ids)
	_TRANSFORM = 0,
	_IMAGE,
	_PLAYERMOVEMENTCOMPONENT,
	_POINTERCOMPONENT,
	_CARDCOMPONENT,
	_HEALTH,
	_CAMERACOMPONENT,
	_BUTTON,
	_ANIMATOR,
	_PLAYER_ANIMATOR,
	_MELEE_BEHAVIOUR,
	_RANGE_BEHAVIOUR,
	_TANK_BEHAVIOUR,
	_COLLIDER_COMPONENT,
	_HITBOX_DAMAGE_COMPONENT,
	_HITBOX_STATUS_COMPONENT,
	_HITBOX_EXPLOSION_COMPONENT,
	_LIFETIME,
	_BAR_COMPONENT,
	_ENEMY_GEN,

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
using grpId_type = int;
enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_ENEMIES,
	_grp_ENM_ATTACK,
	_grp_PLYR_ATTACK,
	_grp_PLAYER,
	_grp_RELICS,
	_grp_UI,
	_grp_POINTER, // El puntero debe ser lo ultimo en renderizar
	// do not remove this
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

// Animaciones
struct Animation {
	int startFrame, endFrame;
	int frameRate;
	int repeat;
	Animation() : startFrame(0), endFrame(0), frameRate(0), repeat(0) {}
	Animation(int _s, int _e, int _rate, int _rep) : startFrame(_s), endFrame(_e), frameRate(_rate), repeat(_rep) {}
};

#include <functional>
// Tipo de funci�n que devuelve y recibe void, funciona tambi�n con funciones lambda con capturas
using CallBack = std::function<void(void)>;
class GameObject;
using CallBackCol = std::function<void(GameObject*)>;
using BoolCallBack = std::function<bool(void)>;
