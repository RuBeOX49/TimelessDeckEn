#include "NodeButtonComponent.h"

// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
NodeButtonComponent::NodeButtonComponent(list<battleType>::iterator* _it, CallBack* _f, nodeState const* _nState) :
ButtonComponent(_f, nullptr), it(_it), nState(_nState) {}

// Actualiza el estado del bot�n
void NodeButtonComponent::update() {
	ButtonComponent::update();
	if (*nState == _LOCKED_NODE) state = OnLocked;
	else if (*nState == _COMPLETED_NODE) state = OnCompleted;
}

// Actualiza la animaci�n del bot�n seg�n el estado
void NodeButtonComponent::updateAnimation() {
	if (state == OnLocked) {
		changeStateAnim(ONLOCKED);
	}
	else if (state == OnCompleted) {
		changeStateAnim(ONCOMPLETED);
	}
	else ButtonComponent::updateAnimation();
}

// Ejecuta el callback del bot�n si este est� disponible
void NodeButtonComponent::onClick() {
	if (!(state == OnLocked || state == OnCompleted)) {
		BattleNode::lastType = it;
		ButtonComponent::onClick();
	}
}