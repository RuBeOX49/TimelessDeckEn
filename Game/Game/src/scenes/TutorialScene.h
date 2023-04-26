﻿#pragma once

#include "NodeScene.h"
#include "../gameObjects/Node Objects/Node.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../gameObjects/Enemy Objects/RangedEnemy.h"
#include "../gameObjects/Enemy Objects/TankEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/UI/HandUI.h"
#include "../components/Enemy components/EnemyGenerator.h"

class StatisticsUI;
class ChargedPortalComponent;
class HandUI;
class TutorialScene : public NodeScene {
private:
	Player* player;
	GameObject* floor, * background, * background1, * background2, * background3;

	// Generador de enemigos
	vector<GameObject*> enemies;
	GameObject* enemyGenerator;
	BattleType type;
	GameObject* deck;
	GameObject* pile;
	Music* battleSceneOST;
	// - UI -
	// Frame superior de vida, man� y �ter
	StatisticsUI* statistics;
	// Puntero a los contadores de cartas
	CardCounter* cardContLeft;
	CardCounter* cardContRight;
	// Puntero a la mano del jugador en la UI
	HandUI* hand;

public:
	// Constructora
	TutorialScene(BattleType bt);
	// Destructora
	virtual ~TutorialScene() { battleSceneOST->haltMusic(); };
};