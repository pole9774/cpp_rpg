#include <iostream>
#include "playercharacter.h"
#include "itemmanager.h"
#include "monster.h"

int main() {

    ItemManager item_manager;
    PlayerCharacter p1(std::make_unique<Warrior>());
    Monster m1("goblin", 35, 5);

    ItemId helm1 = item_manager.createArmor("leather helm", 0, 0, 2, ARMORSLOT::HEAD);
    ItemId courasse1 = item_manager.createArmor("iron courasse", 1, 0, 6, ARMORSLOT::CHEST);
    ItemId gloves1 = item_manager.createArmor("magic gloves", 0, 2, 1, ARMORSLOT::ARMS);
    ItemId pants1 = item_manager.createArmor("leather pants", 0, 0, 2, ARMORSLOT::LEGS);

    ItemId pants2 = item_manager.createArmor("iron greeves", 2, 0, 5, ARMORSLOT::LEGS);

    item_manager.equipArmor(helm1, &p1);
    item_manager.equipArmor(courasse1, &p1);
    item_manager.equipArmor(gloves1, &p1);
    item_manager.equipArmor(pants1, &p1);

    ItemId potion1_id = item_manager.createPotion("small heal", 5, 0, 2);
    ItemId potion2_id = item_manager.createPotion("medium heal", 8, 0, 4);
    ItemId potion3_id = item_manager.createPotion("special potion", 1, 7, 4);

    Buff buff1 = Buff("golden vow", 3, 2, 0);
    Buff buff2 = Buff("flame grant me stength", 4, 1, 0);
    Buff buff3 = Buff("power within", 8, -2, 0);

    item_manager.addToBackPack(potion1_id, &p1);
    item_manager.addToBackPack(potion2_id, &p1);
    item_manager.addToBackPack(potion3_id, &p1);

    ItemId sword1 = item_manager.createWeapon("long sword", 5, WEAPONSLOT::MELEE);
    ItemId dagger1 = item_manager.createWeapon("dagger", 2, WEAPONSLOT::MELEE);
    ItemId bow1 = item_manager.createWeapon("shortbow", 3, WEAPONSLOT::RANGED);
    ItemId bow2 = item_manager.createWeapon("longbow", 4, WEAPONSLOT::RANGED);

    item_manager.equipWeapon(sword1, &p1);
    item_manager.equipWeapon(bow1, &p1);
    item_manager.equipWeapon(bow2, &p1);

    p1.print(std::cout);
    item_manager.printBackpack(p1, std::cout);
    item_manager.printEquippedArmor(p1, std::cout);
    item_manager.printEquippedWeapons(p1, std::cout);

    m1.print(std::cout);

    std::cout << "\n------------------------------\n\n";

    for (int i = 0; i < 10; i++) {

        std::cout << "--- i = " << i << " ---\n\n";

        if (i < 2) {
            p1.gainExp((i + 1) * 50);
            std::cout << "* [ Gained " << (i + 1) * 50 << " exp ] *\n";
            p1.takeDamage(m1.attack());
            std::cout << "* [ p1 attacked by goblin! ] *\n";
        }
        
        if (i == 2) {
            p1.consumeMP(9);
            std::cout << "* [ Consumed 9 MP ] *\n";
            item_manager.removeArmor(courasse1, &p1);
            std::cout << "* [ Removed courasse1 ] *\n";
        }

        if (i == 3) {
            p1.addBuff(buff1);
            std::cout << "* [ Buff added (+3 str, +2 int) ] *\n";
            p1.addBuff(buff2);
            std::cout << "* [ Buff added (+4 str, +1 int) ] *\n";
            item_manager.equipWeapon(dagger1, &p1);
            std::cout << "* [ Equipped dagger ] *\n";
            m1.takeDamage(p1.meleeAttack());
            std::cout << "* [ goblin melee attacked by p1! ] *\n";
        }

        if (i == 4) {
            p1.addBuff(buff3);
            std::cout << "* [ Buff added (+8 str, -2 int) ] *\n";
            item_manager.useItem(potion3_id, &p1);
            std::cout << "* [ Used potion3, hp_heal = 1, mp_heal = 7 ] *\n";
            item_manager.equipArmor(pants2, &p1);
            std::cout << "* [ Equipped pants2 (replacing pants1) ] *\n";
            m1.takeDamage(p1.rangedAttack());
            std::cout << "* [ goblin ranged attacked by p1! ] *\n";
        }

        if (i == 5) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, hp_heal = 8 ] *\n";
            p1.removeBuff("golden vow");
            std::cout << "* [ Buff removed (+3 str, +2 int) ] *\n";
        }

        if (i == 6) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, hp_heal = 8 ] *\n";
            p1.removeBuff("power within");
            std::cout << "* [ Buff removed (+8 str, -2 int) ] *\n";
        }

        if (i == 7) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, hp_heal = 8 ] *\n";
        }

        p1.print(std::cout);
        item_manager.printBackpack(p1, std::cout);
        item_manager.printEquippedArmor(p1, std::cout);
        item_manager.printEquippedWeapons(p1, std::cout);

        m1.print(std::cout);

        std::cout << "\n------------------------------\n\n";
    }

    return 0;
}
