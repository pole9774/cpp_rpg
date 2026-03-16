#pragma once

#include <string>
#include <string_view>
#include <memory>

class ItemDelegate {

    public:
        ItemDelegate(std::string_view name);
        virtual ~ItemDelegate() = default;

        std::string_view getName() const;

        virtual const char* getType() const = 0;
        virtual void print(std::ostream& os) const = 0;

    private:
        std::string name;
};

class Potion : public ItemDelegate {

    public:
        Potion(std::string_view name_param, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned quantity_param);

        const char* getType() const override;

        unsigned int getHpHealAmount() const;
        unsigned int getMpHealAmount() const;
        unsigned int getQuantity() const;

        void decreseQuantity();

        void print(std::ostream& os) const override;

    private:
        unsigned int hp_heal;
        unsigned int mp_heal;
        unsigned int quantity;
};

enum class ARMORSLOT { HEAD, CHEST, ARMS, LEGS, NUM_SLOTS };

class Armor : public ItemDelegate {

    public:
        Armor(std::string_view name_param, int strength_bonus_param, int intelligence_bonus_param, int defence_bonus_param, ARMORSLOT slot_param);

        const char* getType() const override;

        ARMORSLOT getSlot() const;

        unsigned int getStrengthBonus() const;
        unsigned int getIntelligenceBonus() const;
        unsigned int getDefenceBonus() const;

        void print(std::ostream& os) const override;

    private:
        ARMORSLOT slot;
        unsigned int strength_bonus;
        unsigned int intelligence_bonus;
        unsigned int defence_bonus;
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };

class Weapon : public ItemDelegate {

    public:
        Weapon(std::string_view name_param, WEAPONSLOT slot_param);

        const char* getType() const override;

        WEAPONSLOT getSlot() const;

        void print(std::ostream& os) const override;

    private:
        WEAPONSLOT slot;
};

class Item {

    public:
        Item() = delete;
        Item(std::unique_ptr<ItemDelegate> d);
        ~Item() = default;

        ItemDelegate* getData();
        const ItemDelegate* getData() const;

        void print(std::ostream& os) const;

    private:
        std::unique_ptr<ItemDelegate> data;
};
