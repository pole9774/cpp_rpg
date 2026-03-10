#include "buff.h"

Buff::Buff(std::string_view name_param, int strength_buff_param, int intelligence_buff_param) {
    name = name_param;
    strength_buff = strength_buff_param;
    intelligence_buff = intelligence_buff_param;
}

std::string_view Buff::getName() const {
    return name;
}

int Buff::getStrengthBuff() const {
    return strength_buff;
}

int Buff::getIntelligenceBuff() const {
    return intelligence_buff;
}
