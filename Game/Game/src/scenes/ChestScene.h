#pragma once
#ifndef CHESTSCENE_H_
#define CHETSSCENE_H_

#include "NodeScene.h"

class ChestScene : public NodeScene {
private:

public:
	ChestScene();
	static void mainMenu();
	void gacha(GameObject* obj);

	
};

#endif