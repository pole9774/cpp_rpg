#include <iostream>
#include "playercharacter.h"

int main() {

    PlayerCharacter p1(std::make_unique<Warrior>());

    for (int i = 0; i < 10; i++) {
        std::cout
            << p1.getClassName()
            << " - level: " << p1.getLevel() << "\n"
            << "- EXP: " << p1.getEXP() << " / " << p1.getEXPToNextLevel() << "\n"
            << "- HP: " << p1.getCurrentHP() << " / " << p1.getMaxHP() << "\n"
            << "- STR: " << p1.getStrength() << "\n"
            << "- INT: " << p1.getIntelligence() << "\n";
        
        if (i < 9) {
            p1.gainExp(i * 1000);
        }
    }

    return 0;
}
