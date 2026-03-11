#pragma once

#include <unordered_map>
#include "item.h"
#include "itemid.h"
#include "playercharacter.h"

class ItemManager {

    public:
        ItemId createPotion(std::string_view name, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned int quantity_param);

        Item* get(ItemId id);
        const Item* get(ItemId id) const;

        bool destroy(ItemId id);

        bool useItem(ItemId id, PlayerCharacter *pc);

        void printBackpack(const PlayerCharacter& pc, std::ostream& os) const;

    private:
        ItemId next_id = 1;
        std::unordered_map<ItemId, std::unique_ptr<Item>> items;
};
