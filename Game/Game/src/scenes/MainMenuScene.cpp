#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	// Imagen de fondo
	GameObject* background = new GameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(game->getTexture("MainMenuFondo"));
	stateScene.push_back(background);

	// Marco de los botones
	for (int i = 0; i < 4; i++) {
		GameObject* marco = new GameObject();
		marco->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		marco->addComponent<Animator>(game->getTexture("Marco"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
		stateScene.push_back(marco);
	}
	
	// Iterador para la asignaci�n del marco creado anteriormente para cada bot�n
	list<GameObject*>::iterator it = stateScene.begin(); 
	it++; it++; // Saltar la c�mara y el fondo

	// BOTONES -> se crean y se a�aden a la lista de la escena
	// Bot�n jugar
	Button* Play = new Button(play, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2), PLAY, *it);
	stateScene.push_back(Play);

	// Bot�n opciones
	it++;
	Button* Options = new Button(options, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8), OPTIONS, *it);
	stateScene.push_back(Options);

	// Bot�n album
	it++;
	Button* Album = new Button(album, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8), EXIT, *it);
	stateScene.push_back(Album);

	// Bot�n salir
	it++;
	Button* Exit = new Button(exit, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8), EXIT, *it);
	stateScene.push_back(Exit);
}

void MainMenuScene::play(SDLApplication* game) {
	SDLApplication::newScene<BattleScene>(game);
}

void MainMenuScene::options(SDLApplication* game) {
	SDLApplication::newScene<OptionsMenuScene>(game);
}

void MainMenuScene::album(SDLApplication* game) {
	SDLApplication::newScene<AlbumScene>(game);
}

void MainMenuScene::exit(SDLApplication* game) {
	game->quitGame(game);
}