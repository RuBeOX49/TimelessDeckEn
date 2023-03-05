#include "ShopNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posici�n del nodo en el mapa
ShopNode::ShopNode(Vector2D const& pos) : 
	Node(SHOP_NODE_TEXTURE_KEY, pos,
		[]() {
			SDLApplication::newScene<ShopScene>();
		}) {
}