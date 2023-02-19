#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "../scenes/MapScene.h"
using namespace std;

enum nodeState {
	_LOCKED_NODE = 0,
	_UNLOCKED_NODE,
	_COMPLETED_NODE
};

class Node {
private:
	nodeState state;
	vector<Node*> nextNodes;
	string textureKey;
	Vector2D position;

	static vector<Node*> nodeMap;
	
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Desbloquea los siguientes nodos
	void unlockNextNodes();
protected:
	// Constructora, recibe la clave de la textura
	Node(string tKey, Vector2D const& pos);
public:
	// Asigna los siguientes nodos
	void setNextNodes(vector<Node*> const& nNodes);
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete();
	// Carga el nodo correspondiente
	virtual CallBack* loadNode() const = 0;
	// Devuelve la clave de la textura del nodo
	inline const string& getTextureKey() const { return textureKey; }
	// Devuelve la posici�n asignada al nodo
	inline const Vector2D& getPosition() const { return position; }

	// M�TODOS EST�TICOS

	// Inicializa el mapa completo de Nodos
	static void initializeNodeMap();
	// Devuelve una referencia al mapa completo de Nodos
	static inline const vector<Node*> const& getNodeMap() { return nodeMap; }
	// Vac�a el mapa completo de Nodos
	static void clearNodeMap();
};

#endif // NODE_H_
