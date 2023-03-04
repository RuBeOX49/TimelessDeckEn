#include "Node.h"

#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

// Constructora, recibe la clave de la textura
Node::Node(string tKey, Vector2D const& pos) : state(_LOCKED_NODE), nextNodes(), textureKey(tKey), position(pos) {}

// Asigna el estado del nodo a bloqueado
void Node::lock() {
	if (state != _COMPLETED_NODE) {
		state = _LOCKED_NODE;
	}
}

// Asigna el estado del nodo a desbloqueado
void Node::unlock() {
	if (state == _LOCKED_NODE) {
		state = _UNLOCKED_NODE;
	}
}

// Cambia el estado a completado y cambia los nodos desbloqueados
void Node::complete(vector<Node*>& unlockedNodes) {
	state = _COMPLETED_NODE;
	unlockNextNodes(unlockedNodes);
}

// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
void Node::unlockNextNodes(vector<Node*>& unlockedNodes) {
	for (Node* node : unlockedNodes) {
		node->lock();
	}

	unlockedNodes = nextNodes;
	for (Node* node : nextNodes) {
		node->unlock();
	}
}

// Asigna los siguientes nodos
void Node::setNextNodes(vector<Node*> const& nNodes) {
	nextNodes = nNodes;
}

// A�ade el nodo recibido a los siguientes nodos
void Node::addToNextNodes(Node* const& node) {
	nextNodes.push_back(node);
}
