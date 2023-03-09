#pragma once
#include "../Component.h"
#include "../../core/SDLApplication.h"

class HitboxExplosionComponent :  public Component
{
private:
    //Duracion del gObj
	int damage;
    float lifeSpan;
    float currentLifeDuration;
	bool contact;
    BattleScene* scene;
    grpId target;
	Transform* tr;

	CallBackCol explosionFunction()
	{
		return [&](GameObject* gameObject) {
			//Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, Vector2D(data.width / 2, data.height / 2), 250, 250, 0, "Bullet", _grp_ENEMIES };

			//scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, false, 0.25, data);

			gObj->setAlive(false);
		};
	}

public:
    //Constructora. Determina el tick global en el que el gObj muere, la escena en la que se instancia la explosion y el da�o que hace esta
    HitboxExplosionComponent(int dmg, float lifeSpan, bool cntct, BattleScene* scn, grpId trgt) : damage(dmg), lifeSpan(lifeSpan), currentLifeDuration(0), scene(scn), target(trgt), tr(nullptr), contact(cntct) {}
    static const int id = _HITBOX_EXPLOSION_COMPONENT;

	void initComponent()
	{
		tr = gObj->getComponent<Transform>();
		if(contact) gObj->getComponent<ColliderComponent>()->addFunction(explosionFunction());
	}

	//Checkea que haya pasado el tiempo establecido y elimina el gObj creando una explosion en caso positivo
	void update()
	{
		currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
		if (currentLifeDuration > lifeSpan)
		{

			//Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, Vector2D(data.width / 2, data.height / 2), 250, 250, 0, "Bullet", _grp_ENEMIES };

			//scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, false, 0.25, data);

			gObj->setAlive(false);
		}
	}
};