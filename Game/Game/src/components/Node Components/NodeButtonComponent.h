#pragma once
#include "../General Components/ButtonComponent.h"
#include "../../gameObjects/Node Objects/Node.h"

class NodeButtonComponent : public ButtonComponent {
private:
	nodeState const& nState;
	float horMul;
public:
	// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
	NodeButtonComponent(CallBack _f, nodeState const& _nState, float navigatorHorMul);

	void initComponent() override;

	// Actualiza la animaci�n del bot�n seg�n el estado
	virtual void updateAnimation();

	// Ejecuta el callback del bot�n si este est� disponible
	virtual void onClick();
};
