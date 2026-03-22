#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "playercharacter.h"
#include "itemmanager.h"

TEST_CASE("Warrior_creation") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());

    CHECK(p_warrior.getCurrentHP() == WARRIOR_BASEHP);
    CHECK(p_warrior.getCurrentMP() == WARRIOR_BASEMP);
    CHECK(p_warrior.getMaxHP() == WARRIOR_BASEHP);
    CHECK(p_warrior.getMaxMP() == WARRIOR_BASEMP);
    CHECK(p_warrior.getBaseStrength() == WARRIOR_BASESTR);
    CHECK(p_warrior.getStrength() == WARRIOR_BASESTR);
    CHECK(p_warrior.getBaseIntelligence() == WARRIOR_BASEINT);
    CHECK(p_warrior.getIntelligence() == WARRIOR_BASEINT);
    CHECK(p_warrior.getBaseDefence() == 0);
    CHECK(p_warrior.getDefence() == 0);
    CHECK(p_warrior.getLevel() == 1);
    CHECK(p_warrior.getEXP() == 0);
    CHECK(p_warrior.getEXPToNextLevel() == EXP_FOR_LEVEL2);
    CHECK(p_warrior.getClassName() == "Warrior");
}

TEST_CASE("Warrior_levelup") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());

    p_warrior.gainExp(100);

    CHECK(p_warrior.getEXP() == 100);
    CHECK(p_warrior.getLevel() == 2);
    CHECK(p_warrior.getEXPToNextLevel() == 200);
    CHECK(p_warrior.getCurrentHP() == 45);
    CHECK(p_warrior.getCurrentMP() == 7);
    CHECK(p_warrior.getMaxHP() == 45);
    CHECK(p_warrior.getMaxMP() == 7);
    CHECK(p_warrior.getBaseStrength() == 10);
    CHECK(p_warrior.getStrength() == 10);
    CHECK(p_warrior.getBaseIntelligence() == 4);
    CHECK(p_warrior.getIntelligence() == 4);

    p_warrior.gainExp(150);

    CHECK(p_warrior.getEXP() == 250);
    CHECK(p_warrior.getLevel() == 3);
    CHECK(p_warrior.getEXPToNextLevel() == 400);
    CHECK(p_warrior.getCurrentHP() == 60);
    CHECK(p_warrior.getCurrentMP() == 9);
    CHECK(p_warrior.getMaxHP() == 60);
    CHECK(p_warrior.getMaxMP() == 9);
    CHECK(p_warrior.getBaseStrength() == 15);
    CHECK(p_warrior.getStrength() == 15);
    CHECK(p_warrior.getBaseIntelligence() == 6);
    CHECK(p_warrior.getIntelligence() == 6);

    p_warrior.gainExp(150);

    CHECK(p_warrior.getEXP() == 400);
    CHECK(p_warrior.getLevel() == 4);
    CHECK(p_warrior.getEXPToNextLevel() == 800);
    CHECK(p_warrior.getCurrentHP() == 75);
    CHECK(p_warrior.getCurrentMP() == 11);
    CHECK(p_warrior.getMaxHP() == 75);
    CHECK(p_warrior.getMaxMP() == 11);
    CHECK(p_warrior.getBaseStrength() == 20);
    CHECK(p_warrior.getStrength() == 20);
    CHECK(p_warrior.getBaseIntelligence() == 8);
    CHECK(p_warrior.getIntelligence() == 8);
}

// TODO:
// - Warrior weapons
// - Warrior armor
// - Warrior potions
// - Warrior abilities
// - Warrior buffs
// - Repeat for other classes
// - Monster
