#include <functional>
#include "../core/Vector2D.h"
#include "../sdlutils/Texture.h"
using namespace std;
#pragma once

class Vector2D;

class Card
{
	private:
		int damage, maxUses, remainingUses, mana;
		float downtime;
		string name, abilityText, attackText;
		Texture* texture;
		function<void(Vector2D,Vector2D)> attackFunction;
		function<void(Vector2D, Vector2D)> abilityFunction;

		void gunattack(Vector2D playerPos, Vector2D mousePos);
		void gunability(Vector2D playerPos, Vector2D mousePos);
		void swordattack(Vector2D playerPos, Vector2D mousePos);
		void swordability(Vector2D playerPos, Vector2D mousePos);


	public:
		Card(int damage,int uses,int mana, float downtime, string name, string abilityText, string attackText, Texture* texture, function<void(Vector2D, Vector2D)> attackFunction, function<void(Vector2D, Vector2D)> abilityFunction);
		void attack(Vector2D playerPos, Vector2D mousePos) { attackFunction(playerPos, mousePos); }
		void ability(Vector2D playerPos, Vector2D mousePos) { abilityFunction(playerPos, mousePos); }
		int getUses() { return remainingUses; }
		void use() { remainingUses -= 1;}
		void resetUses() { remainingUses = maxUses;}
		int getMana() { return mana; }
};

