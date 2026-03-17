#include "monster.h"

Monster::Monster(unsigned int hp_param, unsigned int damage_param)
    : HP(hp_param, hp_param), damage(damage_param) {}

const unsigned int Monster::getCurrentHP() const {
    return HP.getCurrent();
}

const unsigned int Monster::getMaxHP() const {
    return HP.getMax();
}

void Monster::takeDamage(unsigned int damage_param) {
    HP.reduceCurrent(damage_param);
}

const unsigned int Monster::attack() const {
    return damage;
}
