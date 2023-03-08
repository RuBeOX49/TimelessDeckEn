#pragma once
#include "../Component.h"

// Este componente sirve para manejar todos los eventos relacionados con la vida del objeto
// Como su muerte o su curaci�n
class HealthComponent : public Component {
private:
	int lifePoints;
	int maxLife;
	int modifiedMaxLife;
	bool player;
	float invTime;
	float time;
public:
	static const int id = _HEALTH;
	HealthComponent(int Maxlife, bool player = false);
	//Delete del padre
	void receiveDamage(int damage);
	virtual void update();
	void heal(int heal);
	void die();
	// Devuelve el valor actual de la vida
	inline int getLife()
	{
		return lifePoints;
	}
	void multiplyLife(double multiplier);
	/*void timeDamage()*/
};
