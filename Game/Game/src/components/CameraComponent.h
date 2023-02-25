#pragma once
#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
#include "../core/GameObject.h"
#include "Component.h"
#include "Transform.h"

class CameraComponent : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
	Vector2D followObjectInitialPosition;
public:
	// Identificador
	static const int id = _CAMERACOMPONENT;

	// Constructora
	CameraComponent() : transform(nullptr), followObjectTransform(nullptr) {}

	// Destructora
	~CameraComponent();

	// Inicializa el componente
	virtual void initComponent();

	// Sigue la posicion del followObject
	virtual void update();

	// Setea el objeto a seguir
	void setFollowObject(GameObject* followObject_);
};
#endif // !CAMERA_COMPONENT_H_
