#include <algorithm>
#include "playercharacter.h"

PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0, 0), HP() {
    level = 1;
    exp = 0;
    exp_to_next_level = EXP_FOR_LEVEL2;
}

void PlayerCharacterDelegate::gainExp(unsigned int gained_exp) {
    exp += gained_exp;
    while (checkLevelUp()) {}
}

unsigned int PlayerCharacterDelegate::getLevel() {
    return level;
}

unsigned int PlayerCharacterDelegate::getEXP() {
    return exp;
}

unsigned int PlayerCharacterDelegate::getEXPToNextLevel() {
    return exp_to_next_level;
}

bool PlayerCharacterDelegate::checkLevelUp() {
    if (exp >= exp_to_next_level) {
        level++;
        levelUp();
        exp_to_next_level *= LEVELSCALAR;
        return true;
    }

    return false;
}

void PlayerCharacterDelegate::addToBackpack(ItemId id) {
    backpack.push_back(id);
}

void PlayerCharacterDelegate::removeFromBackpack(ItemId id) {
    backpack.erase(std::remove(backpack.begin(), backpack.end(), id), backpack.end());
}

bool PlayerCharacterDelegate::hasInBackpack(ItemId id) const {
    return std::find(backpack.begin(), backpack.end(), id) != backpack.end();
}

const std::vector<ItemId>& PlayerCharacterDelegate::getBackpack() const {
    return backpack;
}


// Cleric

Cleric::Cleric() : PlayerCharacterDelegate() {
    HP.setMax(CLERIC_BASEHP);
    HP.increaseCurrent(CLERIC_BASEHP);
    increaseStats(CLERIC_BASESTR, CLERIC_BASEINT);
}

std::string Cleric::getClassName() {
    return std::string("Cleric");
}

void Cleric::levelUp() {
    HP.setMax((unsigned int)(CLERIC_BASEHP / 2.0) + HP.getMax());
    HP.increaseCurrent((unsigned int)(CLERIC_BASEHP / 2.0));
    increaseStats(CLERIC_BASESTR, CLERIC_BASEINT);
}


// Warrior

Warrior::Warrior() : PlayerCharacterDelegate() {
    HP.setMax(WARRIOR_BASEHP);
    HP.increaseCurrent(WARRIOR_BASEHP);
    increaseStats(WARRIOR_BASESTR, WARRIOR_BASEINT);
}

std::string Warrior::getClassName() {
    return std::string("Warrior");
}

void Warrior::levelUp() {
    HP.setMax((unsigned int)(WARRIOR_BASEHP / 2.0) + HP.getMax());
    HP.increaseCurrent((unsigned int)(WARRIOR_BASEHP / 2.0));
    increaseStats(WARRIOR_BASESTR, WARRIOR_BASEINT);
}


// Wizard

Wizard::Wizard() : PlayerCharacterDelegate() {
    HP.setMax(WIZARD_BASEHP);
    HP.increaseCurrent(WIZARD_BASEHP);
    increaseStats(WIZARD_BASESTR, WIZARD_BASEINT);
}

std::string Wizard::getClassName() {
    return std::string("Wizard");
}

void Wizard::levelUp() {
    HP.setMax((unsigned int)(WIZARD_BASEHP / 2.0) + HP.getMax());
    HP.increaseCurrent((unsigned int)(WIZARD_BASEHP / 2.0));
    increaseStats(WIZARD_BASESTR, WIZARD_BASEINT);
}


PlayerCharacter::PlayerCharacter(std::unique_ptr<PlayerCharacterDelegate> pc)
    : pcclass(std::move(pc)) {}
