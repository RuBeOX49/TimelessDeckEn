#include "HeatlhComponent.h"
#include"../core/GameObject.h"
// Al construirse, adopta el gameObject y su manager como propios
// Tambi�n define la vida m�xima del objeto
HealthComponent::HealthComponent(int life)
{
	maxLife = modifiedMaxLife = lifePoints = life;
}
// Resta el da�o a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage)
{
	lifePoints -= damage;
	if (lifePoints <= 0) die();
}
// Cura al objeto el valor puesto
void HealthComponent::heal(int heal)
{
	if (lifePoints + heal <= modifiedMaxLife) lifePoints += heal;
	else lifePoints = modifiedMaxLife;
}
void HealthComponent::die()
{
	cout << "MUERTE" << endl; //Para pruebas
	lifePoints = modifiedMaxLife;
	/*gObj->setAlive(false);*/
}
// Devuelve el valor actual de la vida
int HealthComponent::getLife()
{
	return lifePoints;
}
// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	int lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida m�xima actual
}
