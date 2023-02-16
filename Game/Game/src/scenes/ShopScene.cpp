#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene(SDLApplication* _game) : GameState(_game) {
	Button* MainMenu = new Button(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT-50), "Opciones");
	stateScene.push_back(MainMenu);
}
void ShopScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}