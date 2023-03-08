#include "SwordSlashBehaviour.h"
#include "../../scenes/GameState.h"
SwordSlashBehaviour:: SwordSlashBehaviour(int dmg, grpId Target)
{
	myGroup = Target;
	damage = dmg;
	actualObject = 0;
}
void SwordSlashBehaviour::initComponent()
{
	hitRegistry.assign(gStt->getEntitiesByGroup(myGroup).size(), false);
}
// Funci�n a realizar cuando choca
CallBackCol SwordSlashBehaviour::swordAttack()
{
	return [&](GameObject* trgt) {
		//Comprueba si ya ha colisionado anteriormente con el mismo objeto
		if (!hitRegistry[actualObject]) {
			cout << "hizo damages" << endl;
			//Hace el da�o y lo a�ade a la lista de ya colisionados
			trgt->getComponent<HealthComponent>()->receiveDamage(damage);
			hitRegistry[actualObject] = true;
		}
		actualObject++;
		if (actualObject >= hitRegistry.size())actualObject = 0; // Evita atacar a objetos ya colisionados
	};
}