#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include "../Card Objects/SwordSpin.h"

#include <iostream>

// Crea un gObj Slash en la direcci�n que apunta el jugador
void Torch::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();

	where->addGameObject<Hitbox>(playerPos, dir, where, damage * attackMult, SDLApplication::getTexture("SwordSlash"));

}

// Crea un gObj Spin en el centro del jugador
void Torch::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	where->addGameObject<SwordSpin>(playerPos, where, damage * remainingUses * attackMult);

}
