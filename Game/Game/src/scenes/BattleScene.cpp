#include "BattleScene.h"
#include "../core/SDLApplication.h"

BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena de Batalla" << endl;

	player = new GameObject();
	player->addComponent<Transform>(Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2), Vector2D(0, 0), WIN_WIDTH / 10, WIN_HEIGHT / 10);
	player->addComponent<Image>(game->getTexture("Player"));
	player->addComponent<PlayerMovementComponent>();
	
	stateScene.push_back(player);
}