#pragma once

#include "GameState.h"

class SDLApplication;
class GameOverScene : public GameState {
public:
	GameOverScene();
	
	// Crear un bot�n especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};