﻿#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Node Objects/NodeButton.h"

MapScene::MapScene() {
	// MAPA
	map().reloadMap();
	vector<vector<Node*>> const& nodeMap = map().getNodeMap();
	vector<int> const& nodesPerHeight = map().getNodesPerWidth();
	int i = 0;
	for (auto& height : nodeMap) {
		int j = 0;
		for (Node* node : height) {
			if (node != nullptr) { 
				switch (nodesPerHeight[i]) {
				case 1:
					addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[2], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					
					break;
				case 2:
					if (j == 0) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[1], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					else addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[3], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					break;
				case 3:
					if (j == 0) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[0], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					else if (j == 1) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[2], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					else addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[4], (int)WIN_HEIGHT - NODE_DISTANCE - NODE_POSITION_Y * i));
					break;
				}

				++j;
			}
		}
		++i;
	}

	camera->getComponent<Transform>()->setY((- (int)WIN_HEIGHT / 2) + NODE_HEIGHT);

	// BOTONES
	// Botón options
	createButton(MS_OPTIONS_BUTTON_POS, MS_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón Inventario
	createButton(MS_INVENTORY_BUTTON_POS, MS_INVENTORYFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<InventoryScene>(); }, INVENTORY);

	// Botón salir
	createButton(MS_EXIT_BUTTON_POS, MS_EXITFRAME_BUTTON_POS, []() { SDLApplication::newScene<MainMenuScene>(); }, EXIT);
}

// Crear un bot�n especificado en la escena
void MapScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols)->attachToCamera();

	// Crear bot�n
	addGameObject<Button>(_cb, SDLApplication::instance(), _bPos, aI, frame);
}

// Mueve la camara a la altura de los siguientes al nodo actual
void MapScene::moveCamera() {
	Transform* tr = camera->getComponent<Transform>();
	float prevY = tr->getY();
	tr->setY(prevY + NODE_POSITION_Y);
}

void MapScene::createConections(vector<Node*> nodes, int numN) {
	// Miro cuantos nodos hay en la siguiente altura
	int maxIndSig = 0;
	for (int i = 0; i < MAX_NODES; i++) {
		auto c = nodes[i]->getNextInd();
		for (int j = 0; j < c.size(); j++) {
			if (j > maxIndSig) maxIndSig = j;
		}
	}

	// Creo conexiones recorriendo los nodos de la altura (hay 5 casos)
	for (int i = 0; i < MAX_NODES; i++) {
		for (int j = 0; j < maxIndSig; j++) {
			if (nodes[i] != nullptr) {
				// PRIMER CASO: MISMO NUMERO DE NODOS Y SE UNEN MISMAS POSICIONES
				if (maxIndSig == numN && nodes[i]->conectsWith(j) && i == j) {

				}
				// SEGUNDO CASO: DISTINTO NUMERO DE NODOS (por diferencia de uno) Y SE UNEN MISMAS POSICIONES
				else if (maxIndSig - numN == 1 && nodes[i]->conectsWith(j) && i == j) {

				}
				// TERCER CASO: DISTINTO NUMERO DE NODOS (por diferencia de 2) Y SE UNEN MISMAS POSICIONES
				else if (maxIndSig - numN == 2 && nodes[i]->conectsWith(j) && i == j) {

				}
				// CUARTO CASO: MISMO NUMERO DE NODOS Y SE UNEN DISTINTAS POSICIONES
				else if (maxIndSig == numN && nodes[i]->conectsWith(j) && i != j) {
					switch (i - j) {
						// UNION 0 -> 2
						case 2:
							
						break;
						// UNION 0->1 || 1->2
						case 1:

						break; 
						// UNION 1->0 || 2->1
						case -1:

						break; 
						// UNION 2->0
						case -2:

						break;
					}
				}
				// QUINTO CASO: DIFERENTE NUMERO DE NODOS Y SE UNEN DISTINTAS POSICIONES 
				else if (maxIndSig != numN && nodes[i]->conectsWith(j) && i != j) {
					switch (i - j) {
						// UNION 0->1 || 1->2
						case 1:

						break;
						// UNION 1->0 || 2->1
						case -1:

						break;
					}
				}
			}
		}
	}
}