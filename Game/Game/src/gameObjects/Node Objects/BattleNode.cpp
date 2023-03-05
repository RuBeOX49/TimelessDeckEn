#include "BattleNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posici�n del nodo en el mapa
BattleNode::BattleNode(Vector2D const& pos) : 
	Node(BATTLE_NODE_TEXTURE_KEY, pos, 
		[&]() {
			SDLApplication::newScene<BattleScene>(type);
		}), 

	type(battleType(SDLUtils::instance()->rand().nextInt(0, 3))) {
}