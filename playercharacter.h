#pragma once

#include <memory>
#include <vector>
#include "constants.h"
#include "statblock.h"
#include "pointwell.h"
#include "itemid.h"

class PlayerCharacterDelegate : public StatBlock {

    public:
        PlayerCharacterDelegate();

        void gainExp(unsigned int gained_exp);
        unsigned int getLevel();
        unsigned int getEXP();
        unsigned int getEXPToNextLevel();

        void addToBackpack(ItemId id);
        void removeFromBackpack(ItemId id);
        bool hasInBackpack(ItemId id) const;

        const std::vector<ItemId>& getBackpack() const;

        virtual void levelUp() = 0;
        virtual std::string getClassName() = 0;

        PointWell HP;
        PointWell MP;

    protected:
        unsigned int level;
        unsigned int exp;
        unsigned int exp_to_next_level;

        std::vector<ItemId> backpack;

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
        void takeDamage(unsigned int damage) { pcclass->HP.reduceCurrent(damage); }
        void heal(unsigned int amount) { pcclass->HP.increaseCurrent(amount); }

        unsigned int getCurrentMP() { return pcclass->MP.getCurrent(); }
        unsigned int getMaxMP() { return pcclass->MP.getMax(); }
        void consumeMP(unsigned int damage) { pcclass->MP.reduceCurrent(damage); }
        void increaseMP(unsigned int amount) { pcclass->MP.increaseCurrent(amount); }

        unsigned int getBaseStrength() { return pcclass->getBaseStrength(); }
        unsigned int getBaseIntelligence() { return pcclass->getBaseIntelligence(); }
        unsigned int getStrength() { return pcclass->getStrength(); }
        unsigned int getIntelligence() { return pcclass->getIntelligence(); }

        void addToBackpack(ItemId id) { pcclass->addToBackpack(id); }
        void removeFromBackpack(ItemId id) { pcclass->removeFromBackpack(id); }
        bool hasInBackpack(ItemId id) const { return pcclass->hasInBackpack(id); }
        const std::vector<ItemId>& getBackpack() const { return pcclass->getBackpack(); }

        void addBuff(const Buff &new_buff) { pcclass->addBuff(new_buff); }
        bool removeBuff(std::string_view buff_name) { return pcclass->removeBuff(buff_name); }

    private:
        std::unique_ptr<PlayerCharacterDelegate> pcclass;
};
