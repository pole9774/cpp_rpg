#pragma once

#include <memory>
#include "constants.h"
#include "statblock.h"
#include "pointwell.h"

class PlayerCharacterDelegate : public StatBlock {

    public:
        PlayerCharacterDelegate();

        void gainExp(unsigned int gained_exp);

        unsigned int getLevel();

        unsigned int getEXP();

        unsigned int getEXPToNextLevel();

        virtual void levelUp() = 0;
        virtual std::string getClassName() = 0;

        PointWell HP;

    protected:
        unsigned int level;
        unsigned int exp;
        unsigned int exp_to_next_level;

        bool checkLevelUp();
};

class Cleric : public PlayerCharacterDelegate {

    public:
        Cleric();

        std::string getClassName() override;

    private:
        void levelUp() override;
};

class Warrior : public PlayerCharacterDelegate {

    public:
        Warrior();

        std::string getClassName() override;

    private:
        void levelUp() override;
};

class Wizard : public PlayerCharacterDelegate {

    public:
        Wizard();

        std::string getClassName() override;

    private:
        void levelUp() override;
};

class PlayerCharacter {

    public:
        PlayerCharacter() = delete;
        PlayerCharacter(std::unique_ptr<PlayerCharacterDelegate> pc);
        ~PlayerCharacter() = default;

        void gainExp(unsigned int gained_exp) { pcclass->gainExp(gained_exp); }
        unsigned int getLevel() { return pcclass->getLevel(); }
        unsigned int getEXP() { return pcclass->getEXP(); }
        unsigned int getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
        std::string getClassName() { return pcclass->getClassName(); }
        unsigned int getCurrentHP() { return pcclass->HP.getCurrent(); }
        unsigned int getMaxHP() { return pcclass->HP.getMax(); }
        unsigned int getStrength() { return pcclass->getStrength(); }
        unsigned int getIntelligence() { return pcclass->getIntelligence(); }
        void takeDamage(unsigned int damage) { pcclass->HP.reduceCurrent(damage); }
        void heal(unsigned int amount) { pcclass->HP.increaseCurrent(amount); }

    private:
        std::unique_ptr<PlayerCharacterDelegate> pcclass;
};
