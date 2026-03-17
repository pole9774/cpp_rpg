#include "monster.h"

Monster::Monster(std::string_view name_param, unsigned int hp_param, unsigned int damage_param)
    : name(name_param), HP(hp_param, hp_param), damage(damage_param) {}

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

void Monster::print(std::ostream& os) const {
    os << "Monster: " << name << "\n"
        << "- HP: " << HP.getCurrent() << " / " << HP.getMax() << "\n"
        << "- Damage: " << damage << "\n";
}
