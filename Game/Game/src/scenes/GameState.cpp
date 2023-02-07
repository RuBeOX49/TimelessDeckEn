#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState(SDLApplication* _game) : game(_game) {}

// Destructor
GameState::~GameState() {
    for (GameObject* object : stateScene) {
        delete(object);
    }
    for (Manager* manager : sceneManagers) {
        delete(manager);
    }
}

// Updates scene's objects
// Actualiza los objetos de la escea
void GameState::update() {
    for (GameObject* object : stateScene) {
        object->update();
    }
    for (Manager* manager : sceneManagers) {
        manager->update();
    }

    refresh();
}

// Draws the scene on screen
// Dibuja la escena en pantalla
void GameState::render() const {
    for (GameObject* object : stateScene) {
        object->render();
    }
    for (Manager* manager : sceneManagers) {
        manager->render();
    }
}

// Handles the event
// Maneja el evento actual
void GameState::handleEvent(SDL_Event event) {
    for (GameObject* object : stateScene) {
        object->handleEvent(event);
    }
    for (Manager* manager : sceneManagers) {
        manager->handleEvent(event);
    }
}


// Erases every not alive GameObject
// Borra todos los GameObject no vivos
void GameState::refresh() {
    for (Manager* manager : sceneManagers) {
        manager->refresh();
    }
    stateScene.erase(
        std::remove_if(stateScene.begin(), stateScene.end(), [](GameObject* e) {
            if (e->isAlive()) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }), //
        stateScene.end());
}