#include "itemmanager.h"

ItemId ItemManager::createPotion(std::string_view name, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned int quantity_param) {
    ItemId id = next_id++;
    items.emplace(id, std::make_unique<Item>(std::make_unique<Potion>(name, hp_heal_param, mp_heal_param, quantity_param)));
    return id;
}

Item* ItemManager::get(ItemId id) {
    auto it = items.find(id);
    return (it == items.end()) ? nullptr : it->second.get();
}

const Item* ItemManager::get(ItemId id) const {
    auto it = items.find(id);
    return (it == items.end()) ? nullptr : it->second.get();
}

bool ItemManager::destroy(ItemId id) {
    return items.erase(id) > 0;
}

bool ItemManager::useItem(ItemId id, PlayerCharacter *pc) {
    if (!pc) return false;

    Item* item = get(id);
    if (!item) return false;

    auto *potion = dynamic_cast<Potion*>(item->getData());

    if (potion) {
        pc->heal(potion->getHpHealAmount());
        pc->increaseMP(potion->getMpHealAmount());

        potion->decreseQuantity();

        if (potion->getQuantity() == 0) {
            pc->removeFromBackpack(id);
            destroy(id);
        }
    }

    return false;
}

void ItemManager::printBackpack(const PlayerCharacter& pc, std::ostream& os) const {
    const auto& ids = pc.getBackpack();

    os << "Backpack (" << ids.size() << "):\n";

    for (ItemId id : ids) {
        const Item* item = get(id);
        if (!item) {
            os << " - [id=" << id << "] <missing>\n";
            continue;
        }

        os << " - [id=" << id << "] ";
        item->print(os);
        os << "\n";
    }
}
