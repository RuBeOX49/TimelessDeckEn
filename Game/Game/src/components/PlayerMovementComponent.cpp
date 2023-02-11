#include "PlayerMovementComponent.h"
#include "../sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	//A

	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Movimiento a la izquierda
		transform->setVel(Vector2D(-playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_a)) {
		transform->setVel(Vector2D());
	}
	//D

	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Movimiento a la derecha
		transform->setVel(Vector2D(playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_d)) {
	transform->setVel(Vector2D());
	}
	//W

	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		//Movimiento hacia arriba
		transform->setVel(Vector2D(0,-playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w)) {
		transform->setVel(Vector2D());
	}
	//S
	
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		//Movimiento abajo
		transform->setVel(Vector2D(0,playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s)) {
		transform->setVel(Vector2D());
	}
	//S+A

	if (InputHandler::instance()->isKeyDown(SDLK_s)&& InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Movimiento abajo izquierda
		transform->setVel(Vector2D(-playerSpeed, playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s) && InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Se levanta la s y se queda la a
		transform->setVel(Vector2D(-playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_a)&& InputHandler::instance()->isKeyDown(SDLK_s)) {
		//Se levanta la a y se queda la s
		transform->setVel(Vector2D(0, playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s) && InputHandler::instance()->isKeyUp(SDLK_a)) {
		//Se levantan ambas teclas
		transform->setVel(Vector2D());
	}
	//S+D

	if (InputHandler::instance()->isKeyDown(SDLK_s)&& InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Movimiento abajo derecha
		transform->setVel(Vector2D(playerSpeed, playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s) && InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Se levanta la s y se queda la d
		transform->setVel(Vector2D(playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_d)&& InputHandler::instance()->isKeyDown(SDLK_s)) {
		//Se levanta la d y se queda la s
		transform->setVel(Vector2D(0, playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s)&& InputHandler::instance()->isKeyUp(SDLK_d)) {
		//Se levantan ambas
		transform->setVel(Vector2D());
	}
	//W+D
	
	if (InputHandler::instance()->isKeyDown(SDLK_w)&& InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Movimiento arriba derecha
		transform->setVel(Vector2D(playerSpeed, -playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_d)&& InputHandler::instance()->isKeyDown(SDLK_w)) {
		//Se levanta la d y se queda la w
		transform->setVel(Vector2D(0, -playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w) && InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Se levanta la w y se queda la d
		transform->setVel(Vector2D(playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w)&& InputHandler::instance()->isKeyUp(SDLK_d)) {
		//Se levantan ambas
		transform->setVel(Vector2D());
	}
	//Pendant
	//W+A

	if (InputHandler::instance()->isKeyDown(SDLK_w)&& InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Movimiento arriba izquierda
		transform->setVel(Vector2D(-playerSpeed, -playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w) && InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Se levanta la w y se queda la a
		transform->setVel(Vector2D(-playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_a)&& InputHandler::instance()->isKeyDown(SDLK_w)) {
		//Se levanta la a y se queda la w
		transform->setVel(Vector2D(0, -playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w)&& InputHandler::instance()->isKeyUp(SDLK_a)) {
		//Se levantan ambas
		transform->setVel(Vector2D());
	}
	
}