#include "ability.h"

Ability::Ability(std::string_view name_param, unsigned int mp_cost_param)
    : name(name_param), mp_cost(mp_cost_param) {}

std::string_view Ability::getName() const {
    return name;
}

unsigned int Ability::getMpCost() const {
    return mp_cost;
}
