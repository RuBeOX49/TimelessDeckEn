#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene() : NodeScene() {
	cout << "Has entrado en la escena de Cofre" << endl;

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}
void ChestScene::mainMenu() {
	SDLApplication::returnToMapScene();
}