#pragma once
#include "GameState.h"
#include "../components/General Components/Transform.h"
#include "../components/General Components/Image.h"
#include "../components/General Components/Animator.h"
#include "../components/General Components/TextComponent.h"
#include "../gameObjects/UI/Button.h"

class MainMenuScene : public GameState {
private:
public:
	// Constructora
	MainMenuScene();
	// Crear un bot�n especificado en la escena
	Button* createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};