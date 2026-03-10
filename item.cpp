#include "item.h"

ItemDelegate::ItemDelegate(std::string_view name) : name(name) {}

Item::Item(std::unique_ptr<ItemDelegate> d) : data(std::move(d)) {}

std::string_view ItemDelegate::getName() const {
    return name;
}

Potion::Potion(std::string_view name_param, unsigned int hp_heal_param, unsigned quantity_param)
    : ItemDelegate(name_param), hp_heal(hp_heal_param), quantity(quantity_param) {}

const char* Potion::getType() const {
    return "potion";
}

unsigned int Potion::getHealAmount() const {
    return hp_heal;
}

unsigned int Potion::getQuantity() const {
    return quantity;
}

void Potion::decreseQuantity() {
    quantity--;
}

ItemDelegate* Item::getData() {
    return data.get();
}

const ItemDelegate* Item::getData() const {
    return data.get();
}

void Potion::print(std::ostream& os) const {
    os << getName()
       << " type=" << getType()
       << " heal=" << hp_heal
       << " qty=" << quantity;
}

void Item::print(std::ostream& os) const {
    if (data) data->print(os);
    else os << "<empty item>";
}
