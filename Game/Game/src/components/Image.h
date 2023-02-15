#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_

#include "Component.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

class Image : public Component {
private:
	Texture* texture;
	Transform* transform;
public:
	static const int id = _IMAGE;
	// Constructor que recibe una textura
	// Para a�adir una textura a�adir su archivo en resources/images y a�adirla al fichero src/data/textures.txt
	// El formato es: NombreTextura rutaTextura nFramesVerticales nFramesHorizontales
	// Por ejemplo: Player Game/resources/images/player.png 1 1
	// Para asignar la textura en el constructor llamar al m�todo de SDLApplication getTexture(string textureName)
	// Por ejemplo: sdlAppPointer->getTexture("Player");
	Image(Texture* _texture);
	// Inicializa el componente y asigna su puntero a transform
	virtual void initComponent();
	// Dibuja en pantalla la textura en el rect�ngulo del transform
	virtual void render() const;
};
#endif // !IMAGE_H_
