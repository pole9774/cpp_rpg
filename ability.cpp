#include "ability.h"

Ability::Ability(std::string_view name_param, unsigned int mp_cost_param, unsigned int hp_effect_param, TARGET target_param)
    : name(name_param), mp_cost(mp_cost_param), hp_effect(hp_effect_param), target(target_param) {}

std::string_view Ability::getName() const {
    return name;
}

unsigned int Ability::getMpCost() const {
    return mp_cost;
}

unsigned int Ability::getHpEffect() const {
    return hp_effect;
}

TARGET Ability::getTarget() const {
    return target;
}

void Ability::print(std::ostream& os) const {
    os << name << ": mp_cost=" << mp_cost << " hp_effect=" << hp_effect << " target=";
    if (target == TARGET::SELF) {
        os << "self";
    } else {
        os << "enemy";
    }
}
