#pragma once

#include <map>
#include "GameControl.h"
#include "../components/General Components/Image.h"

struct ButtonData {
	std::map<int, ButtonData>::iterator pos[4];
	int supPos[4];
	Image* buttonIm;
};
enum direction : int {
	d_x = 0, d_y
};
enum way : int {
	u = 0, d, l, r
};

class ButtonNavigator {
private:
	typedef std::map<int, ButtonData> button_map;
	std::map<int, button_map> matrix[2];
	ButtonData currentButton;
	ButtonData defaultButton;

	GameControl& gmCtrl_;
	bool unlockedMovement_;

	// Selecciona el bot�n adjacente al actual en la direcci�n indicada
	bool changePos(way w);
public:
	// Constructora
	ButtonNavigator();
	// Selecciona el bot�n encima del actual
	void up();
	// Selecciona el bot�n debajo del actual
	void down();
	// Selecciona el bot�n a la derecha del actual
	void left();
	// Selecciona el bot�n a la izquierda del actual
	void right();


	// A�ade un bot�n al sistema de navegaci�n entre estos, recibe su componente Imagen
	ButtonData insert(Image* im, float horMul = 1.0f, float verMul = 1.0f);
	std::pair<button_map::iterator, bool> insertBorder(direction dir, int x, int y, ButtonData bd, SDL_Rect orr);
	void erase(Image* im);

	// Recibe un bot�n y lo asigna como el por defecto
	void setDefaultButton(ButtonData bd);
	// Recibe un bot�n y lo asigna como el actual
	void setCurrentButton(ButtonData bd);
	// Selecciona el bot�n por defecto
	void selectDefaultButton();
	// Bloquea la navegacion entre botones
	void lockMovement();
	// Desbloquea la navegaci�n entre botones
	void unlockMovement();
	// Comprueba si la imagen pasada es la del bot�n actual
	inline bool isCurrentButton(Image* im) { return im == currentButton.buttonIm; }
};

