#include <algorithm>
#include "statblock.h"

StatBlock::StatBlock() {
    strength = 0;
    intelligence = 0;
    defence = 0;
    total_strength_buff = 0;
    total_intelligence_buff = 0;
    total_defence_buff = 0;
    total_armor_strength = 0;
    total_armor_intelligence = 0;
    total_armor_defence = 0;
}

StatBlock::StatBlock(unsigned strength_param, unsigned int intelligence_param) {
    strength = strength_param;
    intelligence = intelligence_param;
    defence = 0;
    total_strength_buff = 0;
    total_intelligence_buff = 0;
    total_defence_buff = 0;
    total_armor_strength = 0;
    total_armor_intelligence = 0;
    total_armor_defence = 0;
}

unsigned int StatBlock::getBaseStrength() {
    return strength;
}

unsigned int StatBlock::getBaseIntelligence() {
    return intelligence;
}

unsigned int StatBlock::getBaseDefence() {
    return defence;
}

unsigned int StatBlock::getStrength() {
    int tmp_strength = strength + total_strength_buff + total_armor_strength;
    return (tmp_strength >= 0) ? tmp_strength : 0;
}

unsigned int StatBlock::getIntelligence() {
    int tmp_intelligence = intelligence + total_intelligence_buff + total_armor_intelligence;
    return (tmp_intelligence >= 0) ? tmp_intelligence : 0;
}

unsigned int StatBlock::getDefence() {
    int tmp_defence = defence + total_defence_buff + total_armor_defence;
    return (tmp_defence >= 0) ? tmp_defence : 0;
}

void StatBlock::increaseStats(unsigned int strength_param, unsigned int intelligence_param) {
    strength += strength_param;
    intelligence += intelligence_param;
}

void StatBlock::recalculateBuffs() {
    total_strength_buff = 0;
    total_intelligence_buff = 0;
    total_defence_buff = 0;

    for (auto &buff : buffs) {
        total_strength_buff += buff.getStrengthBuff();
        total_intelligence_buff += buff.getIntelligenceBuff();
        total_defence_buff += buff.getDefenceBuff();
    }
}

void StatBlock::addBuff(const Buff &new_buff) {
    for (auto &buff : buffs) {
        if (new_buff.getName() == buff.getName()) return;
    }

    buffs.push_back(new_buff);
    recalculateBuffs();
}

bool StatBlock::removeBuff(std::string_view buff_name) {
    auto it = std::find_if(buffs.begin(), buffs.end(), 
        [&](const Buff& b) { return b.getName() == buff_name; });

    if (it == buffs.end()) return false;

    buffs.erase(it);
    recalculateBuffs();

    return true;
}

const std::vector<Buff>& StatBlock::getBuffs() const {
    return buffs;
}

void StatBlock::buffTurnPassed() {
    bool changed = false;

    for (auto it = buffs.begin(); it != buffs.end(); ) {
        it->decreaseDuration();
        if (it->getDuration() == 0) {
            it = buffs.erase(it);
            changed = true;
        } else {
            ++it;
        }
    }

    if (changed) {
        recalculateBuffs();
    }
}

void StatBlock::modArmorStrength(int str_param) {
    total_armor_strength += str_param;
}

void StatBlock::modArmorIntelligence(int int_param) {
    total_armor_intelligence += int_param;
}

void StatBlock::modArmorDefence(int def_param) {
    total_armor_defence += def_param;
}
