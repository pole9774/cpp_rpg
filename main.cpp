#include <iostream>
#include <random>
#include <string>
#include <limits>
#include "playercharacter.h"
#include "itemmanager.h"
#include "monster.h"

static char readCommandChar() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return '\0';
    }
    if (line.empty()) {
        return '\n';   
    }
    return line[0];
}

char the_map[12][13] = {
    "xxxxxxxxxxxx",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "x          x",
    "xxxxxxxxxxxx"
};

ItemManager item_manager;

int monsters_defeated = 0;

struct Player {
    Player(std::unique_ptr<PlayerCharacterDelegate> charclass)
        : us(std::move(charclass)) {}

    Player() = delete;

    bool isAlive() {
        return (us.getCurrentHP() > 0);
    }

    PlayerCharacter us;
    int prev_xpos = 3;
    int prev_ypos = 3;
    int xpos = 3;
    int ypos = 3;
};

struct Fightable {
    Fightable(std::string_view name_param, int hp_param, int damage_param)
        : monster(name_param, hp_param, damage_param) {
        exp_worth = (hp_param + damage_param) * 4;
    }

    Fightable() = delete;

    bool isAlive() {
        return (monster.getCurrentHP() > 0);
    }
    
    Monster monster;
    int xpos = 5;
    int ypos = 5;
    int exp_worth = 0;
};

void displayCharacterInfo(Player &player) {
    player.us.print(std::cout);
    item_manager.printEquippedArmor(player.us, std::cout);
    item_manager.printEquippedWeapons(player.us, std::cout);
}

bool combatAbility(Player &player, Fightable &enemy) {
    bool done = false;
    bool action_used = false;
    bool show_nomp_message = false;
    int selected_ability = 0;

    while (!done && !action_used) {
        system("CLS");
        auto ability_list = player.us.getAbilities();

        std::cout << "Abilities:\n";
        int ability_index = 0;
        for (const auto &ability : ability_list) {
            if (ability_index == selected_ability) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            ability.print(std::cout);
            std::cout << "\n";
            ability_index++;
        }

        if (show_nomp_message) {
            std::cout << "\nNot enough MP to use the selected ability.\n";
            show_nomp_message = false;
        }

        std::cout << "\ndone (d), up (w), down (s), use (e): ";
        char c = readCommandChar();

        switch (c) {
            case 'd':
                done = true;
                break;
            case 'w':
                selected_ability--;
                if (selected_ability < 0) {
                    selected_ability = 0;
                }
                break;
            case 's':
                selected_ability++;
                if (selected_ability > (ability_list.size() - 1)) {
                    selected_ability = ability_list.size() - 1;
                }
                break;
            case 'e':
                if (player.us.getCurrentMP() >= ability_list[selected_ability].getMpCost()) {
                    player.us.consumeMP(ability_list[selected_ability].getMpCost());
                    if (ability_list[selected_ability].getTarget() == TARGET::SELF) {
                        player.us.heal(ability_list[selected_ability].getHpEffect(player.us.getStrength(), player.us.getIntelligence()));
                    } else {
                        enemy.monster.takeDamage(ability_list[selected_ability].getHpEffect(player.us.getStrength(), player.us.getIntelligence()));
                    }
                    action_used = true;
                } else {
                    show_nomp_message = true;
                }
                break;
            default:
                break;
        }
    }

    return action_used;
}

bool combatInventory(Player &player) {
    bool done = false;
    bool action_used = false;
    int selected_item = 0;

    while (!done && !action_used) {
        system("CLS");
        auto item_ids_list = player.us.getBackpack();

        std::cout << "Inventory:\n";
        int item_index = 0;
        for (const auto &item_id : item_ids_list) {
            if (item_index == selected_item) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            item_manager.printItem(item_id, std::cout);
            std::cout << "\n";
            item_index++;
        }

        std::cout << "\ndone (d), up (w), down (s), use/equip (e): ";
        char c = readCommandChar();

        switch (c) {
            case 'd':
                done = true;
                break;
            case 'w':
                selected_item--;
                if (selected_item < 0) {
                    selected_item = 0;
                }
                break;
            case 's':
                selected_item++;
                if (selected_item > (item_ids_list.size() - 1)) {
                    selected_item = item_ids_list.size() - 1;
                }
                break;
            case 'e':
                if (item_ids_list.size() > 0) {
                    if (item_manager.getType(item_ids_list[selected_item]) == "potion") {
                        action_used = item_manager.useItem(item_ids_list[selected_item], &(player.us));
                    } else if (item_manager.getType(item_ids_list[selected_item]) == "weapon") {
                        action_used = item_manager.equipWeapon(item_ids_list[selected_item], &(player.us));
                    } else if (item_manager.getType(item_ids_list[selected_item]) == "armor") {
                        action_used = item_manager.equipArmor(item_ids_list[selected_item], &(player.us));
                    }

                    if (selected_item == (item_ids_list.size() - 1) && selected_item > 0) {
                        selected_item--;
                    }
                }
                break;
            default:
                break;
        }
    }

    return action_used;
}

void openInventory(Player &player) {
    bool done = false;
    int selected_item = 0;
    
    while (!done) {
        system("CLS");
        auto item_ids_list = player.us.getBackpack();

        std::cout << "Inventory:\n";
        int item_index = 0;
        for (const auto &item_id : item_ids_list) {
            if (item_index == selected_item) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            item_manager.printItem(item_id, std::cout);
            std::cout << "\n";
            item_index++;
        }

        std::cout << "\ndone (d), up (w), down (s), use/equip (e): ";
        char c = readCommandChar();

        switch (c) {
            case 'd':
                done = true;
                break;
            case 'w':
                selected_item--;
                if (selected_item < 0) {
                    selected_item = 0;
                }
                break;
            case 's':
                selected_item++;
                if (selected_item > (item_ids_list.size() - 1)) {
                    selected_item = item_ids_list.size() - 1;
                }
                break;
            case 'e':
                if (item_ids_list.size() > 0) {
                    if (item_manager.getType(item_ids_list[selected_item]) == "potion") {
                        item_manager.useItem(item_ids_list[selected_item], &(player.us));
                    } else if (item_manager.getType(item_ids_list[selected_item]) == "weapon") {
                        item_manager.equipWeapon(item_ids_list[selected_item], &(player.us));
                    } else if (item_manager.getType(item_ids_list[selected_item]) == "armor") {
                        item_manager.equipArmor(item_ids_list[selected_item], &(player.us));
                    }

                    if (selected_item == (item_ids_list.size() - 1) && selected_item > 0) {
                        selected_item--;
                    }
                }
                break;
            default:
                break;
        }
    }
}

ItemId dropRandomItem() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 100);
    int tmp = dist(gen);

    ItemId created_item = kInvalidItemId;

    if (tmp <= 8) {
        created_item = item_manager.createArmor("basic helm", 1, 0, 4, ARMORSLOT::HEAD);
    } else if (tmp <= 16) {
        created_item = item_manager.createArmor("basic courasse", 2, 0, 6, ARMORSLOT::CHEST);
    } else if (tmp <= 24) {
        created_item = item_manager.createArmor("basic gloves", 1, 0, 3, ARMORSLOT::ARMS);
    } else if (tmp <= 32) {
        created_item = item_manager.createArmor("basic pants", 1, 0, 5, ARMORSLOT::LEGS);
    } else if (tmp <= 40) {
        created_item = item_manager.createWeapon("dagger", 4, WEAPONSLOT::MELEE);
    } else if (tmp <= 48) {
        created_item = item_manager.createWeapon("shortbow", 3, WEAPONSLOT::RANGED);
    } else if (tmp <= 90) {
        created_item = item_manager.createPotion("small heal", 5, 0, 1);
    }

    return created_item;
}

Fightable replaceEnemy() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 4);
    int tmp = dist(gen);
    unsigned int scaling = (monsters_defeated / 4) + 1;

    if (tmp == 1) {
        Fightable goblin("goblin", 5 * scaling, 1 * scaling);
        return goblin;
    } else if (tmp == 2) {
        Fightable orc("orc", 6 * scaling, 2 * scaling);
        return orc;
    } else if (tmp == 3) {
        Fightable zombie("zombie", 7 * scaling, 1 * scaling);
        return zombie;
    } else {
        Fightable dragon("dragon", 10 * scaling, 3 * scaling);
        return dragon;
    }
}

void enterFightSequence(Player &player, Fightable &enemy) {
    enum class FightOptions { NONE, ATTACK, INVENTORY, ABILITY };

    while (player.isAlive() && enemy.isAlive()) {
        FightOptions action_taken = FightOptions::NONE;

        while (action_taken == FightOptions::NONE) {
            system("CLS");

            std::cout << "Player vs Monster\n\n";
            displayCharacterInfo(player);
            std::cout << "\n---------------------\n\n";
            enemy.monster.print(std::cout);

            std::cout << "\nmeele attack (m), ranged attack (r), inventory (i), ability (a): ";
            char action = readCommandChar();

            switch (action) {
                case 'm':
                    action_taken = FightOptions::ATTACK;
                    enemy.monster.takeDamage(player.us.meleeAttack());
                    break;
                case 'r':
                    action_taken = FightOptions::ATTACK;
                    enemy.monster.takeDamage(player.us.rangedAttack());
                    break;
                case 'i':
                    action_taken = (combatInventory(player)) ? FightOptions::INVENTORY : FightOptions::NONE;
                    break;
                case 'a':
                    action_taken = (combatAbility(player, enemy)) ? FightOptions::ABILITY : FightOptions::NONE;
                    break;
                default:
                    break;
            }
        }

        if (enemy.isAlive()) {
            int enemy_damage = enemy.monster.attack() - player.us.getDefence();
            if (enemy_damage < 1) {
                enemy_damage = 1;
            }
            player.us.takeDamage(enemy_damage);
        }

        player.us.buffTurnPassed();
    }

    system("CLS");
    std::cout << "Player vs Monster\n\n";
    displayCharacterInfo(player);
    std::cout << "\n---------------------\n\n";
    enemy.monster.print(std::cout);

    if (player.isAlive()) {
        std::cout << "\nYou won against the monster!\n";
        player.us.gainExp(enemy.exp_worth);
        std::cout << "You gained " << enemy.exp_worth << " exp!\n";
        monsters_defeated++;
        ItemId item_drop = dropRandomItem();
        if (item_drop != kInvalidItemId) {
            item_manager.addToBackPack(item_drop, &(player.us));
            std::cout << "You received ";
            item_manager.printItem(item_drop, std::cout);
            std::cout << "! (added to the backpack)\n";
        }
        enemy = replaceEnemy();
    } else {
        std::cout << "You were defeated by the monster...\n";
    }

    std::cout << "\nPress Enter to continue\n";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void movePlayerOnMap(Player &player, Fightable &enemy) {
    if (player.xpos == player.prev_xpos && player.ypos == player.prev_ypos) {
        return;
    }

    if (the_map[player.xpos][player.ypos] == 'M') {
        enterFightSequence(player, enemy);
        the_map[player.prev_xpos][player.prev_ypos] = ' ';
        player.xpos = 3;
        player.ypos = 3;
        player.prev_xpos = 3;
        player.prev_ypos = 3;
        enemy.xpos = 5;
        enemy.ypos = 5;
        the_map[player.xpos][player.ypos] = 'P';
        the_map[enemy.xpos][enemy.ypos] = 'M';
    } else {
        if (the_map[player.xpos][player.ypos] != 'x') {
            the_map[player.xpos][player.ypos] = 'P';
            the_map[player.prev_xpos][player.prev_ypos] = ' ';
            player.prev_xpos = player.xpos;
            player.prev_ypos = player.ypos;
        } else {
            player.xpos = player.prev_xpos;
            player.ypos = player.prev_ypos;
        }
    }
}

void showMap() {
    system("CLS");
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 13; j++) {
            std::cout << the_map[i][j];
        }
        std::cout << "\n";
    }
}

int main() {

    std::cout << "Choose a class: \n"
        << "1 = Cleric    2 = Warrior    3 = Wizard\n";

    int choice = 0;

    while (choice == 0) {
        std::cin >> choice;
        if (choice < 1 || choice > 3) {
            choice = 0;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::unique_ptr<PlayerCharacterDelegate> chosen_class;

    switch (choice) {
        case 1:
            chosen_class = std::make_unique<Cleric>();
            break;
        case 2:
            chosen_class = std::make_unique<Warrior>();
            break;
        case 3:
            chosen_class = std::make_unique<Wizard>();
            break;
        default:
            return -1;
    }

    Player main_character(std::move(chosen_class));

    Fightable current_monster = replaceEnemy();

    the_map[main_character.xpos][main_character.ypos] = 'P';
    the_map[current_monster.xpos][current_monster.ypos] = 'M';

    showMap();

    for (;;) {
        std::cout << "\n";
        displayCharacterInfo(main_character);
        std::cout << "\nMonsters defeated: " << monsters_defeated << "\n";

        std::cout << "\nmove (wasd), inventory (i): ";
        char c = readCommandChar();

        switch (c) {
            case 'w':
                main_character.xpos--;
                break;
            case 's':
                main_character.xpos++;
                break;
            case 'a':
                main_character.ypos--;
                break;
            case 'd':
                main_character.ypos++;
                break;
            case 'i':
                openInventory(main_character);
                break;
            default:
                break;
        }

        movePlayerOnMap(main_character, current_monster);

        if (main_character.isAlive()) {
            showMap();
        } else {
            break;
        }
    }

    return 0;
}
