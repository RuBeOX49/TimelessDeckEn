#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"
#include "../managers/MapManager.h"
class MapScene : public GameState {
private:
public:
	MapScene(SDLApplication* _game);
};

#endif