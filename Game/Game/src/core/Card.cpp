#include "../cards/Cards.h"

//Devuelve la carta correspondiente al id
Card Card::getCard(CardId type) {

	// cleon says: pod�is sacar un elemento random de un vector, y el elemento que sea una lambda
	switch (type)
	{
	case gun:
		return GunCard();
	case sword:
		return SwordCard();
	case laserShades:
		return LaserShadesCard();
	default:
		break;
	}
}