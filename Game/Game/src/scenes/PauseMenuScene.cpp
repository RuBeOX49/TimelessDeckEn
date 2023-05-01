#include "PauseMenuScene.h"
#include "../core/SDLApplication.h"

PauseMenuScene::PauseMenuScene() : GameState() {
	// Bot�n jugar
	createButton(PM_RESUME_BUTTON_POS, PM_RESUMEFRAME_BUTTON_POS, []() { SDLApplication::resumeGame(); }, RESUME)->setAsDefaultButton();

	// Bot�n Opciones
	createButton(PM_OPTIONS_BUTTON_POS, PM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Bot�n salir
	createButton(PM_EXIT_BUTTON_POS, PM_EXITFRAME_BUTTON_POS, []() { pD().loseSavedData(); SDLApplication::newScene<MainMenuScene>(); }, EXIT);
}

void PauseMenuScene::handleInput() {
	GameState::handleInput();
	if (gmCtrl_.pause()) {
		SDLApplication::resumeGame();
	}
}