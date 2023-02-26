#include "../../core/Vector2D.h"
#include "../../sdlutils/Texture.h"

#pragma once

enum CardId
{
	gun = 0,
	sword,
	laserShades,
};
class BattleScene;
class Card
{
	protected:
		int damage, maxUses, remainingUses, mana;
		float downtime, bulletSpeed;
		std::string name, abilityText, attackText;
		Texture* texture;

	public:
		Card(int _damage, int _maxUses, int _mana, float _downtime, float _bulletSpeed, std::string _data, Texture* _texture);
		static Card getCard(CardId type);
		//Ataque
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		//Habilidad
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		//Se gasta un uso
		void use() { remainingUses -= 1;}
		//Se reinician sus usos respecto a los m�ximos
		void resetUses() { remainingUses = maxUses;}
		

		// Getters
		int getUses() { return remainingUses; }
		int getMana() { return mana; }
		int getDownTime() { return downtime; }
		Texture* getTexture() { return texture; }
};

