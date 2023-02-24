#include "ShopNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posici�n del nodo en el mapa
ShopNode::ShopNode(Vector2D const& pos) : Node(SHOP_NODE_TEXTURE_KEY, pos) {}

// Devuelve un CallBack que abre la escena de tienda
CallBack ShopNode::loadNode() const {
	return []() {
		SDLApplication::newScene<ShopScene>();
	};
}