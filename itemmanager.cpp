#include "itemmanager.h"

ItemId ItemManager::createPotion(std::string_view name_param, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned int quantity_param) {
    ItemId id = next_id++;
    items.emplace(id, std::make_unique<Item>(std::make_unique<Potion>(name_param, hp_heal_param, mp_heal_param, quantity_param)));
    return id;
}

ItemId ItemManager::createArmor(std::string_view name_param, int strength_bonus_param, int intelligence_bonus_param, int defence_bonus_param, ARMORSLOT slot_param) {
    ItemId id = next_id++;
    items.emplace(id, std::make_unique<Item>(std::make_unique<Armor>(name_param, strength_bonus_param, intelligence_bonus_param, defence_bonus_param, slot_param)));
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

        return true;
    }

    return false;
}

bool ItemManager::equipArmor(ItemId id, PlayerCharacter *pc) {
    if (!pc) return false;

    Item* item = get(id);
    if (!item) return false;

    auto *armor = dynamic_cast<Armor*>(item->getData());

    if (armor) {
        ItemId replaced_id = pc->equipArmor(id, (unsigned int)(armor->getSlot()));
        pc->modArmorStrength(armor->getStrengthBonus());
        pc->modArmorIntelligence(armor->getIntelligenceBonus());
        pc->modArmorDefence(armor->getDefenceBonus());

        if (replaced_id != kInvalidItemId) {
            Item* replaced_item = get(replaced_id);
            auto *replaced_armor = dynamic_cast<Armor*>(replaced_item->getData());
            pc->modArmorStrength(-(replaced_armor->getStrengthBonus()));
            pc->modArmorIntelligence(-(replaced_armor->getIntelligenceBonus()));
            pc->modArmorDefence(-(replaced_armor->getDefenceBonus()));
        }

        return true;
    }

    return false;
}

bool ItemManager::removeArmor(ItemId id, PlayerCharacter *pc) {
    if (!pc) return false;

    Item* item = get(id);
    if (!item) return false;

    auto *armor = dynamic_cast<Armor*>(item->getData());

    if (armor) {
        if (pc->removeArmor((unsigned int)(armor->getSlot()))) {
            pc->modArmorStrength(-(armor->getStrengthBonus()));
            pc->modArmorIntelligence(-(armor->getIntelligenceBonus()));
            pc->modArmorDefence(-(armor->getDefenceBonus()));
            return true;
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

void ItemManager::printEquippedArmor(const PlayerCharacter& pc, std::ostream& os) const {
    const auto& ids = pc.getEquippedArmor();

    for (int i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (ids[i] == kInvalidItemId) {
            os << " - <empty slot>\n";
        } else {
            const Item* item = get(ids[i]);
            if (!item) {
                os << " - [id=" << ids[i] << "] <missing>\n";
                continue;
            }

            os << " - [id=" << ids[i] << "] ";
            item->print(os);
            os << "\n";
        }
    }
}
