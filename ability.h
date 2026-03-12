#pragma once

#include <string>

class Ability {

    public:
        Ability(std::string_view name_param, unsigned int mp_cost_param);

        std::string_view getName() const;

        unsigned int getMpCost() const;

    private:
        std::string name;
        unsigned int mp_cost;
};
