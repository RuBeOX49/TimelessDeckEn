#include "ChestNode.h"

ChestNode::ChestNode(Vector2D const& pos) : Node(CHEST_NODE_TEXTURE_KEY, pos) {}

CallBack* ChestNode::loadNode() const{
	return MapScene::cofre;
}