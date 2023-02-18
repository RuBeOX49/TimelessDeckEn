#include "Image.h"
#include "../core/GameObject.h"
#include "../scenes/GameState.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr), cameraTransform(nullptr) {}


// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		cameraTransform = gStt->getCamera()->getComponent<Transform>();
	}
}

// Dibuja en pantalla la textura en el rect�ngulo del transform
void Image::render() const {
	texture->render(getRect());
}

//Devuelve el rect dependiendo de la c�mara
SDL_Rect Image::getRect() const{
	SDL_Rect rect = transform->getRect();

	if (cameraTransform != nullptr) {
		//Dependiendo de la posici�n de la c�mara
		rect.x += cameraTransform->getRect().x;
		rect.y += cameraTransform->getRect().y;
	}
	
	return rect;
}

// Hace que el GameObject se renderice en funci�n a la ventana, no a la c�mara
void Image::attachToCamera() {
	cameraTransform = nullptr;
}