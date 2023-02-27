#pragma once
#ifndef SHOPNODE_H_
#define SHOPNODE_H_

#include "Node.h"
class ShopScene;

class ShopNode : public Node {
	friend Node;
private:
	// Constructora, recibe posici�n del nodo en el mapa
	ShopNode(Vector2D const& pos);
public:
	// Devuelve un CallBack que abre la escena de tienda
	virtual CallBack loadNode() const;
};

#endif // !SHOPNODE_H_
