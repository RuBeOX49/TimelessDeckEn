#pragma once
#include "Hitbox.h"

class CustomHitbox : public Hitbox {
public:
    // CustomHitbox(const HitboxData& data); // Elimina esta l�nea
    void initCustomHitbox(const HitboxData& data); // A�ade esta l�nea

    virtual void update() override;
    void setUpdateFunction(std::function<void(GameObject*)> function);

private:
    std::function<void(GameObject*)> updateFunction;
};