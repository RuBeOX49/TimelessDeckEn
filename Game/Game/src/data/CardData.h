#pragma once
#include "../sdlutils/Texture.h"

enum CardTime { _CardPast, _CardPresent, _CardFuture };

struct CardData {
    std::string name;
    std::string attackText;
    std::string abilityText;
    int damage;
    int maxUses;
    int mana;
    float downTime;
    Texture* texture;
    CardTime time;
};