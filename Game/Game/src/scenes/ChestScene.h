#pragma once
#include "NodeScene.h"

class ChestScene : public NodeScene {
private:
	bool alreadyClicked;
	GameObject* gachaButton;
	AnimatorInfo* chestAI;

public:
	ChestScene();
	virtual ~ChestScene();

	void gacha(GameObject* obj);

	void spawnNewItem();
};