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

Fightable replaceEnemy() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 4);
    int tmp = dist(gen);

    if (tmp == 1) {
        Fightable goblin("goblin", 6, 1);
        return goblin;
    } else if (tmp == 2) {
        Fightable orc("orc", 7, 1);
        return orc;
    } else if (tmp == 3) {
        Fightable zombie("zombie", 7, 1);
        return zombie;
    } else {
        Fightable dragon("dragon", 8, 1);
        return dragon;
    }
}

void enterFightSequence(Player &player, Fightable &enemy) {
    while (player.isAlive() && enemy.isAlive()) {
        system("CLS");

        std::cout << "Player vs Monster\n\n";
        player.us.print(std::cout);
        std::cout << "\n\n-------------------\n\n";
        enemy.monster.print(std::cout);

        std::cout << "\n\n\naction (a = attack): ";
        char action = '\0';
        while (action != 'a') {
            action = readCommandChar();
        }

        enemy.monster.takeDamage(player.us.meleeAttack());

        if (enemy.isAlive()) {
            player.us.takeDamage(enemy.monster.attack());
        }
    }

    if (player.isAlive()) {
        std::cout << "You won against the monster!\n";
        player.us.gainExp(enemy.exp_worth);
        monsters_defeated++;
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
        main_character.us.print(std::cout);
        std::cout << "\nMonsters defeated: " << monsters_defeated << "\n";

        std::cout << "\nmove (wasd): ";
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
