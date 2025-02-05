#pragma once

#include "GameState.h"
#include "../gameObjects/Node Objects/Map.h"

class MapScene : public GameState {
private:
	Button* exitButton;
	Button* inventoryButton;
	Transform* camTr;
	int camYLimit;
	GameObject* background;
	GameObject* background2;
	GameObject* markPoint;

public:
	MapScene();

	void goToTutorial();
	void goToBoss();

	void handleInput() override;
	void update() override;

	// Mover la camara a la altura de los siguientes al current
	void moveCamera();

	void resetSelectedButton();

	// Creamos el enlace entre nodos
	void createConections(vector<vector<Node*>> const& nodes, vector<vector<Vector2D>> const& nodesPos, vector<int> const& nodesPerHeight, int alt);
};