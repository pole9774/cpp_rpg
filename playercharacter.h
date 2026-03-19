#pragma once

#include <memory>
#include <vector>
#include "constants.h"
#include "statblock.h"
#include "pointwell.h"
#include "itemid.h"
#include "item.h"
#include "ability.h"

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

        ItemId equipArmor(ItemId id, unsigned int slot);
        bool removeArmor(unsigned int slot);

        ItemId equipWeapon(ItemId id, unsigned int slot);
        bool removeWeapon(unsigned int slot);

        const ItemId* getEquippedArmor() const;
        const ItemId* getEquippedWeapons() const;

        void setMeleeWeaponDamage(unsigned int damage_param);
        void setRangedWeaponDamage(unsigned int damage_param);

        const unsigned int getMeleeWeaponDamage() const;
        const unsigned int getRangedWeaponDamage() const;

        virtual void levelUp() = 0;
        virtual std::string getClassName() = 0;

        void addAbility(Ability new_ability);
        const std::vector<Ability> getAbilities() const;

        PointWell HP;
        PointWell MP;

    protected:
        unsigned int level;
        unsigned int exp;
        unsigned int exp_to_next_level;

        unsigned int melee_weapon_damage;
        unsigned int ranged_weapon_damage;

        std::vector<ItemId> backpack;
        ItemId equipped_armor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
        ItemId equipped_weapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];

        std::vector<Ability> abilities;

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
        unsigned int getBaseDefence() { return pcclass->getBaseDefence(); }

        unsigned int getStrength() { return pcclass->getStrength(); }
        unsigned int getIntelligence() { return pcclass->getIntelligence(); }
        unsigned int getDefence() { return pcclass->getDefence(); }
        
        const std::vector<ItemId>& getBackpack() const { return pcclass->getBackpack(); }

        void addBuff(const Buff &new_buff) { pcclass->addBuff(new_buff); }
        bool removeBuff(std::string_view buff_name) { return pcclass->removeBuff(buff_name); }

        void addAbility(Ability new_ability) { pcclass->addAbility(new_ability); }
        const std::vector<Ability> getAbilities() const { return pcclass->getAbilities(); }

        const unsigned int meleeAttack() const;
        const unsigned int rangedAttack() const;

        void print(std::ostream& os) const;

    private:
        void addToBackpack(ItemId id) { pcclass->addToBackpack(id); }
        void removeFromBackpack(ItemId id) { pcclass->removeFromBackpack(id); }
        bool hasInBackpack(ItemId id) const { return pcclass->hasInBackpack(id); }

        ItemId equipArmor(ItemId id, unsigned int slot) { return pcclass->equipArmor(id, slot); }
        bool removeArmor(unsigned int slot) { return pcclass->removeArmor(slot); }

        ItemId equipWeapon(ItemId id, unsigned int slot) { return pcclass->equipWeapon(id, slot); }
        bool removeWeapon(unsigned int slot) { return pcclass->removeWeapon(slot); }

        const ItemId* getEquippedArmor() const { return pcclass->getEquippedArmor(); }
        const ItemId* getEquippedWeapons() const { return pcclass->getEquippedWeapons(); }

        void modArmorStrength(int str_param) { pcclass->modArmorStrength(str_param); }
        void modArmorIntelligence(int int_param) { pcclass->modArmorIntelligence(int_param); }
        void modArmorDefence(int def_param) { pcclass->modArmorDefence(def_param); }

        void setMeleeWeaponDamage(unsigned int damage_param) { pcclass->setMeleeWeaponDamage(damage_param); }
        void setRangedWeaponDamage(unsigned int damage_param) { pcclass->setRangedWeaponDamage(damage_param); }

        std::unique_ptr<PlayerCharacterDelegate> pcclass;

        friend class ItemManager;
};
