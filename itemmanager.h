#pragma once

#include <unordered_map>
#include "item.h"
#include "itemid.h"
#include "playercharacter.h"

class ItemManager {

    public:
        ItemId createPotion(std::string_view name_param, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned int quantity_param);
        ItemId createArmor(std::string_view name_param, int strength_bonus_param, int intelligence_bonus_param, int defence_bonus_param, ARMORSLOT slot_param);
        ItemId createWeapon(std::string_view name_param, WEAPONSLOT slot_param);

        Item* get(ItemId id);
        const Item* get(ItemId id) const;

        bool destroy(ItemId id);

        bool useItem(ItemId id, PlayerCharacter *pc);

        void addToBackPack(ItemId id, PlayerCharacter *pc);

        bool equipArmor(ItemId id, PlayerCharacter *pc);
        bool removeArmor(ItemId id, PlayerCharacter *pc);
        bool equipWeapon(ItemId id, PlayerCharacter *pc);
        bool removeWepon(ItemId id, PlayerCharacter *pc);

        void printBackpack(const PlayerCharacter& pc, std::ostream& os) const;
        void printEquippedArmor(const PlayerCharacter& pc, std::ostream& os) const;
        void printEquippedWeapons(const PlayerCharacter& pc, std::ostream& os) const;

    private:
        ItemId next_id = 1;
        std::unordered_map<ItemId, std::unique_ptr<Item>> items;
};
