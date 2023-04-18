#include "PauseMenuScene.h"
#include "../core/SDLApplication.h"

PauseMenuScene::PauseMenuScene() : GameState() {
	// Bot�n jugar
	createButton(PM_RESUME_BUTTON_POS, PM_RESUMEFRAME_BUTTON_POS, []() { SDLApplication::resumeGame(); }, RESUME)->setAsCurrentButton();

	// Bot�n options
	createButton(PM_INVENTORY_BUTTON_POS, PM_INVENTORYFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<InventoryScene>(); }, INVENTORY);

	// Bot�n album
	createButton(PM_OPTIONS_BUTTON_POS, PM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Bot�n salir
	createButton(PM_EXIT_BUTTON_POS, PM_EXITFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<MapScene>(); }, EXIT);
}

void PauseMenuScene::handleInput() {
	GameState::handleInput();
	if (gmCtrl_.pause()) {
		SDLApplication::resumeGame();
	}
}