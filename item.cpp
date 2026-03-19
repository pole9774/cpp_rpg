#include "item.h"

ItemDelegate::ItemDelegate(std::string_view name_param) : name(name_param) {}

Item::Item(std::unique_ptr<ItemDelegate> d) : data(std::move(d)) {}

std::string_view ItemDelegate::getName() const {
    return name;
}

ItemDelegate* Item::getData() {
    return data.get();
}

const ItemDelegate* Item::getData() const {
    return data.get();
}

Potion::Potion(std::string_view name_param, unsigned int hp_heal_param, unsigned int mp_heal_param, unsigned quantity_param)
    : ItemDelegate(name_param), hp_heal(hp_heal_param), mp_heal(mp_heal_param), quantity(quantity_param) {}

Armor::Armor(std::string_view name_param, int strength_bonus_param, int intelligence_bonus_param, int defence_bonus_param, ARMORSLOT slot_param)
    : ItemDelegate(name_param), strength_bonus(strength_bonus_param), intelligence_bonus(intelligence_bonus_param), defence_bonus(defence_bonus_param), slot(slot_param) {}

Weapon::Weapon(std::string_view name_param, unsigned int base_damage_param, WEAPONSLOT slot_param)
    : ItemDelegate(name_param), base_damage(base_damage_param), slot(slot_param) {}

const char* Potion::getType() const {
    return "potion";
}

const char* Armor::getType() const {
    return "armor";
}

const char* Weapon::getType() const {
    return "weapon";
}

unsigned int Potion::getHpHealAmount() const {
    return hp_heal;
}

unsigned int Potion::getMpHealAmount() const {
    return mp_heal;
}

unsigned int Potion::getQuantity() const {
    return quantity;
}

void Potion::decreseQuantity() {
    quantity--;
}

void Potion::print(std::ostream& os) const {
    os << getName()
       << " type=" << getType()
       << " hp_heal=" << hp_heal
       << " mp_heal=" << mp_heal
       << " qty=" << quantity;
}

ARMORSLOT Armor::getSlot() const {
    return slot;
}

unsigned int Armor::getStrengthBonus() const {
    return strength_bonus;
}

unsigned int Armor::getIntelligenceBonus() const {
    return intelligence_bonus;
}

unsigned int Armor::getDefenceBonus() const {
    return defence_bonus;
}

void Armor::print(std::ostream& os) const {
    os << getName()
       << " type=" << getType()
       << " str_bonus=" << strength_bonus
       << " int_bonus=" << intelligence_bonus
       << " def_bonus=" << defence_bonus;
}

const unsigned int Weapon::getBaseDamage() const {
    return base_damage;
}

WEAPONSLOT Weapon::getSlot() const {
    return slot;
}

void Weapon::print(std::ostream& os) const {
    os << getName()
        << " type=" << getType()
        << " base_dmg=" << base_damage;
}

void Item::print(std::ostream& os) const {
    if (data) data->print(os);
    else os << "<empty item>";
}
