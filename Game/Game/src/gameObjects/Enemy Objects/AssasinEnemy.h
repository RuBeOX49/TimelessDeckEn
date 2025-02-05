#pragma once
#include "../../components/Enemy components/AssasinBehaviour.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/Enemy components/OnDeath.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../scenes/GameState.h"
#include "../Player Object/Mana.h"

class SDLApplication;
class AssasinEnemy :public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, int life, Player* player);
};


