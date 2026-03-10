#include <iostream>
#include "playercharacter.h"
#include "itemmanager.h"

int main() {

    ItemManager item_manager;
    PlayerCharacter p1(std::make_unique<Warrior>());

    ItemId potion1_id = item_manager.createPotion("small heal", 5, 2);
    ItemId potion2_id = item_manager.createPotion("medium heal", 8, 4);
    ItemId potion3_id = item_manager.createPotion("special heal", 1, 4);

    p1.addToBackpack(potion1_id);
    p1.addToBackpack(potion2_id);

    std::cout
        << p1.getClassName()
        << " - level: " << p1.getLevel() << "\n"
        << "- EXP: " << p1.getEXP() << " / " << p1.getEXPToNextLevel() << "\n"
        << "- HP: " << p1.getCurrentHP() << " / " << p1.getMaxHP() << "\n"
        << "- STR: " << p1.getStrength() << "\n"
        << "- INT: " << p1.getIntelligence() << "\n";

    item_manager.printBackpack(p1, std::cout);

    std::cout << "\n------------------------------\n\n";

    for (int i = 0; i < 10; i++) {

        if (i < 9) {
            p1.gainExp(i * 1000);
            std::cout << "* [ Gained " << i * 1000 << " exp ] *\n";
        }
        
        if (i == 2) {
            p1.takeDamage(5);
            std::cout << "* [ Taken 5 damage ] *\n";
        }

        if (i == 4) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, heal = 8 ] *\n";
        }

        if (i == 5) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, heal = 8 ] *\n";
        }

        if (i == 6) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, heal = 8 ] *\n";
        }

        if (i == 7) {
            item_manager.useItem(potion2_id, &p1);
            std::cout << "* [ Used potion2, heal = 8 ] *\n";
        }

        std::cout
            << p1.getClassName()
            << " - level: " << p1.getLevel() << "\n"
            << "- EXP: " << p1.getEXP() << " / " << p1.getEXPToNextLevel() << "\n"
            << "- HP: " << p1.getCurrentHP() << " / " << p1.getMaxHP() << "\n"
            << "- STR: " << p1.getStrength() << "\n"
            << "- INT: " << p1.getIntelligence() << "\n";

        item_manager.printBackpack(p1, std::cout);

        std::cout << "\n------------------------------\n\n";
    }

    return 0;
}
