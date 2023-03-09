#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>


// Este componente maneja el comportamiento de los objetos Slash creados, 
class HitboxStatusComponent : public Component {
public:
	enum Status {
		CONFUSED,
		BURNED
	};

	static const int id = _HITBOX_STATUS_COMPONENT;
	// Recibe un grupo de objetos con el que debe colisionar la hitbox, y una duraci�n y un estado que debe aplicar
	HitboxStatusComponent(Status stts, float drt) : duration(drt), status(stts)	{}

	inline void initComponent() override
	{
		gObj->getComponent<ColliderComponent>()->addFunction(statusFunction());
	}

private:
	float duration;
	Status status;

	CallBackCol statusFunction()
	{
		return [&](GameObject* trgt) {
			//trgt->getComponent<StatusComponent>()->confuse(duration);
		};
	}
};