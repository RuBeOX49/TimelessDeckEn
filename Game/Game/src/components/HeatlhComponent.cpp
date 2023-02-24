#include "HeatlhComponent.h"
#include"../core/GameObject.h"
#include "../scenes/BattleScene.h"
#include "RangeBehavior.h"
#include "MeleeBehaviour.h"

// Al construirse, adopta el gameObject y su manager como propios
// Tambi�n define la vida m�xima del objeto
HealthComponent::HealthComponent(int life)
{
	maxLife = modifiedMaxLife = lifePoints = life;
}
// Resta el da�o a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage)
{
	cout << "ouch" << endl;
	lifePoints -= damage;
	if (lifePoints <= 0) die();
}
// Cura al objeto el valor puesto
void HealthComponent::heal(int heal)
{
	if (lifePoints + heal <= modifiedMaxLife) lifePoints += heal;
	else lifePoints = modifiedMaxLife;
}
// Al llegar la vida a 0, el objetose dispone a morir
// En el caso del jugador, termina la partida
void HealthComponent::die()
{
	auto sc = dynamic_cast<BattleScene*>(gStt);
	if (gObj->hasComponent<CardComponent>()) {
		sc->OnPlayerDies();
	}
	gObj->setAlive(false);
}

// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	float lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida m�xima actual
}