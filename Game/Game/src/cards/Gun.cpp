#include "Cards.h"
#include "../sdlutils/Texture.h"
#include "../gameObjects/Bullet.h"

GunCard::GunCard() {
	damage = 20;
	maxUses = 5;
	remainingUses = maxUses;
	mana = 35;
	downtime = 0.5;
	name = "Pistola";
	abilityText = "Se disparan todas las balas como escopeta";
	attackText = "";
	texture = nullptr;
}

void GunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {
	std::cout << "pium"<<endl;
}

void GunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
