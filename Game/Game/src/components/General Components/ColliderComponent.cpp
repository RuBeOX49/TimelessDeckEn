#include"ColliderComponent.h"
#include "../../scenes/GameState.h"

ColliderComponent::ColliderComponent(CallBackCol myFunct, grpId list)
{
	myId = list;
	funct = myFunct;
}
void ColliderComponent::initComponent()
{
	others = gStt->getEntitiesByGroup(myId);
}
// Comprueba la colisi�n del objeto con la lista de colisionados
void ColliderComponent::hasCollided() {
	for (GameObject* other : others) {
		Transform* otherTr = other->getComponent<Transform>();
		Vector2D& pos1 = gObj->getComponent<Transform>()->getPos();
		float width1 = gObj->getComponent<Transform>()->getWidth();
		float height1 = gObj->getComponent<Transform>()->getHeight();
		float rot1 = gObj->getComponent<Transform>()->getRotation();
		Vector2D anch1 = gObj->getComponent<Transform>()->getAnchorPoint();
		Vector2D& pos2 = otherTr->getPos();
		float width2 = otherTr->getWidth();
		float height2 = otherTr->getHeight();
		float rot2 = otherTr->getRotation();
		Vector2D anch2 = otherTr->getAnchorPoint();

		// Si colisiona, realiza la funci�n
		if (Collisions::collidesWithRotation(pos1, width1, height1, rot1, anch1,
			pos2, width2, height2, rot2, anch2))
		{
			funct(other);
		}
	}
}