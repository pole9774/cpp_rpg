#include "statblock.h"

StatBlock::StatBlock() {
    strength = 0;
    intelligence = 0;
}

StatBlock::StatBlock(unsigned strength_param, unsigned int intelligence_param) {
    strength = strength_param;
    intelligence = intelligence_param;
}

unsigned int StatBlock::getStrength() {
    return strength;
}

unsigned int StatBlock::getIntelligence() {
    return intelligence;
}

void StatBlock::increaseStats(unsigned int strength_param, unsigned int intelligence_param) {
    strength += strength_param;
    intelligence += intelligence_param;
}
