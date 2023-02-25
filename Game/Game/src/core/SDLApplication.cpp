#include "SDLApplication.h"

// Constructora
SDLApplication::SDLApplication() {

	// Creacion de la ventana
	SDLUtils::init("Timeless Deck - Es tiempo", WIN_WIDTH, WIN_HEIGHT, "../Game/src/data/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();
	//utils->toggleFullScreen();

	Node::initializeNodeMap();

	// Maquina de estados
	gameStateMachine = new GameStateMachine();
	exit = false;
}

// Destructora
SDLApplication::~SDLApplication() {
	delete(gameStateMachine);
	Node::clearNodeMap();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Ejecuta el juego
void SDLApplication::run() {
	gameStateMachine->pushState(new MainMenuScene());



	uint32_t frameTime, debugCounter;
	startTime = SDL_GetTicks();
	debugCounter = 0;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	while (!exit) {
		InputHandler::instance()->refresh();
		
		frameTime = SDL_GetTicks() - startTime;
		
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();



		update();

		if (frameTime >= DELAY_TIME) {
			
			deltaTime = frameTime;
			debugCounter += getDeltaTime();
			startTime = SDL_GetTicks();
			
			render();
		}
		
		std::cout << debugCounter << " " << SDL_GetTicks() << " " << (float)debugCounter / (float)SDL_GetTicks() << std::endl;
		
		handleInput();
	}
	gameStateMachine->clearStates();
}

// Dibuja el juego en pantalla
void SDLApplication::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Actualiza todas las entidades del juego
void SDLApplication::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Actualiza el juego en funci�n al evento actual
void SDLApplication::handleInput() {
	gameStateMachine->currentState()->handleInput();
}

// Devuelve la Texture pedida
Texture* SDLApplication::getTexture(TextureName texture) { return &SDLUtils::instance()->images().at(texture); }

// Pausa el juego
void SDLApplication::pauseGame() { /*_game->gameStateMachine->pushState(new PauseMenuState(_game));*/ }

// Reanuda el juego
void SDLApplication::resumeGame() { SDLApplication::popGameState(); }

// Elimina el estado en la cima de la pila
void SDLApplication::popGameState() { SDLApplication::instance()->gameStateMachine->popState(); }

// Cierra el juego
void SDLApplication::quitGame() { SDLApplication::instance()->exit = true; }


