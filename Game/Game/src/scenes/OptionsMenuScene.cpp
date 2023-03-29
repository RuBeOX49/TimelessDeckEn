#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"

OptionsMenuScene::OptionsMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Botones
	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::newScene<MainMenuScene>(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
	aI.key = OPTIONS;
	addGameObject<Button>([]() { sdlutils().toggleFullScreen(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 200), aI);
}