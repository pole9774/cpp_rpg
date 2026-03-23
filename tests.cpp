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
    CHECK(p_warrior.getClassName() == "warrior");
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

TEST_CASE("Warrior_armor") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());
    ItemManager item_manager;

    ItemId helm1 = item_manager.createArmor("basic helm", 1, 0, 4, ARMORSLOT::HEAD);
    ItemId courasse1 = item_manager.createArmor("basic courasse", 2, 0, 6, ARMORSLOT::CHEST);
    ItemId gloves1 = item_manager.createArmor("basic gloves", 1, 0, 3, ARMORSLOT::ARMS);
    ItemId pants1 = item_manager.createArmor("basic pants", 1, 0, 5, ARMORSLOT::LEGS);

    item_manager.addToBackPack(helm1, &p_warrior);
    item_manager.addToBackPack(courasse1, &p_warrior);
    item_manager.addToBackPack(gloves1, &p_warrior);
    item_manager.addToBackPack(pants1, &p_warrior);

    auto backpack = p_warrior.getBackpack();

    CHECK(backpack.size() == 4);
    CHECK(backpack.at(0) == helm1);
    CHECK(backpack.at(1) == courasse1);
    CHECK(backpack.at(2) == gloves1);
    CHECK(backpack.at(3) == pants1);

    item_manager.equipArmor(helm1, &p_warrior);
    item_manager.equipArmor(courasse1, &p_warrior);
    item_manager.equipArmor(gloves1, &p_warrior);
    item_manager.equipArmor(pants1, &p_warrior);

    auto backpack2 = p_warrior.getBackpack();

    CHECK(backpack2.size() == 0);

    auto equipped_armor = p_warrior.getEquippedArmor();

    CHECK(equipped_armor[(unsigned int)ARMORSLOT::HEAD] == helm1);
    CHECK(equipped_armor[(unsigned int)ARMORSLOT::CHEST] == courasse1);
    CHECK(equipped_armor[(unsigned int)ARMORSLOT::ARMS] == gloves1);
    CHECK(equipped_armor[(unsigned int)ARMORSLOT::LEGS] == pants1);

    CHECK(p_warrior.getBaseStrength() == WARRIOR_BASESTR);
    CHECK(p_warrior.getStrength() == (WARRIOR_BASESTR + 5));
    CHECK(p_warrior.getBaseIntelligence() == WARRIOR_BASEINT);
    CHECK(p_warrior.getIntelligence() == (WARRIOR_BASEINT + 0));
    CHECK(p_warrior.getBaseDefence() == 0);
    CHECK(p_warrior.getDefence() == (0 + 18));

    ItemId courasse2 = item_manager.createArmor("magic courasse", 1, 2, 5, ARMORSLOT::CHEST);

    item_manager.equipArmor(courasse2, &p_warrior);
    item_manager.removeArmor(helm1, &p_warrior);

    auto backpack3 = p_warrior.getBackpack();

    CHECK(backpack3.size() == 2);
    CHECK(backpack3.at(0) == courasse1);
    CHECK(backpack3.at(1) == helm1);

    auto equipped_armor2 = p_warrior.getEquippedArmor();

    CHECK(equipped_armor2[(unsigned int)ARMORSLOT::HEAD] == kInvalidItemId);
    CHECK(equipped_armor2[(unsigned int)ARMORSLOT::CHEST] == courasse2);
    CHECK(equipped_armor2[(unsigned int)ARMORSLOT::ARMS] == gloves1);
    CHECK(equipped_armor2[(unsigned int)ARMORSLOT::LEGS] == pants1);

    CHECK(p_warrior.getBaseStrength() == WARRIOR_BASESTR);
    CHECK(p_warrior.getStrength() == (WARRIOR_BASESTR + 3));
    CHECK(p_warrior.getBaseIntelligence() == WARRIOR_BASEINT);
    CHECK(p_warrior.getIntelligence() == (WARRIOR_BASEINT + 2));
    CHECK(p_warrior.getBaseDefence() == 0);
    CHECK(p_warrior.getDefence() == (0 + 13));
}

TEST_CASE("Warrior_weapons") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());
    ItemManager item_manager;

    CHECK(p_warrior.meleeAttack() == WARRIOR_BASESTR);
    CHECK(p_warrior.rangedAttack() == WARRIOR_BASESTR);

    ItemId sword1 = item_manager.createWeapon("sword", 6, WEAPONSLOT::MELEE);
    ItemId bow1 = item_manager.createWeapon("shortbow", 4, WEAPONSLOT::RANGED);

    item_manager.equipWeapon(sword1, &p_warrior);
    item_manager.equipWeapon(bow1, &p_warrior);

    auto equipped_weapons = p_warrior.getEquippedWeapons();

    CHECK(equipped_weapons[(unsigned int)WEAPONSLOT::MELEE] == sword1);
    CHECK(equipped_weapons[(unsigned int)WEAPONSLOT::RANGED] == bow1);

    CHECK(p_warrior.meleeAttack() == WARRIOR_BASESTR + 6);
    CHECK(p_warrior.rangedAttack() == WARRIOR_BASESTR + 4);

    ItemId bow2 = item_manager.createWeapon("longbow", 7, WEAPONSLOT::RANGED);

    item_manager.removeWepon(sword1, &p_warrior);
    item_manager.equipWeapon(bow2, &p_warrior);

    auto backpack = p_warrior.getBackpack();

    CHECK(backpack.size() == 2);
    CHECK(backpack.at(0) == sword1);
    CHECK(backpack.at(1) == bow1);

    auto equipped_weapons2 = p_warrior.getEquippedWeapons();

    CHECK(equipped_weapons2[(unsigned int)WEAPONSLOT::MELEE] == kInvalidItemId);
    CHECK(equipped_weapons2[(unsigned int)WEAPONSLOT::RANGED] == bow2);

    CHECK(p_warrior.meleeAttack() == WARRIOR_BASESTR);
    CHECK(p_warrior.rangedAttack() == WARRIOR_BASESTR + 7);
}

TEST_CASE("Warrior_potions") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());
    ItemManager item_manager;

    ItemId potion1 = item_manager.createPotion("small heal", 5, 0, 3);
    ItemId potion2 = item_manager.createPotion("medium heal", 8, 0, 2);
    ItemId potion3 = item_manager.createPotion("big heal", 12, 0, 1);
    ItemId potion4 = item_manager.createPotion("magic heal", 0, 3, 1);

    item_manager.addToBackPack(potion1, &p_warrior);
    item_manager.addToBackPack(potion2, &p_warrior);
    item_manager.addToBackPack(potion3, &p_warrior);
    item_manager.addToBackPack(potion4, &p_warrior);

    p_warrior.takeDamage(25);
    CHECK(p_warrior.getCurrentHP() == 5);
    p_warrior.consumeMP(4);
    CHECK(p_warrior.getCurrentMP() == 1);

    auto backpack = p_warrior.getBackpack();
    CHECK(backpack.size() == 4);

    item_manager.useItem(potion3, &p_warrior);
    CHECK(p_warrior.getCurrentHP() == 17);
    auto backpack2 = p_warrior.getBackpack();
    CHECK(backpack2.size() == 3);

    item_manager.useItem(potion2, &p_warrior);
    CHECK(p_warrior.getCurrentHP() == 25);
    auto backpack3 = p_warrior.getBackpack();
    CHECK(backpack3.size() == 3);

    item_manager.useItem(potion1, &p_warrior);
    CHECK(p_warrior.getCurrentHP() == 30);
    auto backpack4 = p_warrior.getBackpack();
    CHECK(backpack4.size() == 3);

    item_manager.useItem(potion4, &p_warrior);
    CHECK(p_warrior.getCurrentMP() == 4);
    auto backpack5 = p_warrior.getBackpack();
    CHECK(backpack5.size() == 2);

    item_manager.useItem(potion2, &p_warrior);
    CHECK(p_warrior.getCurrentHP() == 30);
    auto backpack6 = p_warrior.getBackpack();
    CHECK(backpack6.size() == 1);
}

TEST_CASE("Warrior_abilities") {
    PlayerCharacter p_warrior = PlayerCharacter(std::make_unique<Warrior>());

    auto abilities = p_warrior.getAbilities();
    CHECK(abilities.size() == 1);
    CHECK(abilities.at(0).getName() == "light attack");
    CHECK(abilities.at(0).getMpCost() == 1);
    CHECK(abilities.at(0).getBaseHpEffect() == 2);
    CHECK(abilities.at(0).getHpEffect(p_warrior.getStrength(), p_warrior.getIntelligence()) == (2 + WARRIOR_BASESTR));
    CHECK(abilities.at(0).getTarget() == TARGET::ENEMY);

    p_warrior.gainExp(100);
    auto abilities2 = p_warrior.getAbilities();
    CHECK(p_warrior.getLevel() == 2);
    CHECK(abilities2.size() == 2);
    CHECK(abilities2.at(0).getName() == "light attack");
    CHECK(abilities2.at(1).getName() == "charged attack");
    CHECK(abilities2.at(1).getMpCost() == 2);
    CHECK(abilities2.at(1).getBaseHpEffect() == 3);
    CHECK(abilities2.at(1).getHpEffect(p_warrior.getStrength(), p_warrior.getIntelligence()) == (3 + 2 * WARRIOR_BASESTR));
    CHECK(abilities2.at(1).getTarget() == TARGET::ENEMY);

    p_warrior.gainExp(100);
    auto abilities3 = p_warrior.getAbilities();
    CHECK(p_warrior.getLevel() == 3);
    CHECK(abilities3.size() == 3);
    CHECK(abilities3.at(0).getName() == "light attack");
    CHECK(abilities3.at(1).getName() == "charged attack");
    CHECK(abilities3.at(2).getName() == "heal surge");
    CHECK(abilities3.at(2).getMpCost() == 3);
    CHECK(abilities3.at(2).getBaseHpEffect() == 9);
    CHECK(abilities3.at(2).getHpEffect(p_warrior.getStrength(), p_warrior.getIntelligence()) == 9);
    CHECK(abilities3.at(2).getTarget() == TARGET::SELF);
}

// TODO:
// - Warrior buffs
// - Repeat for other classes
// - Monster
