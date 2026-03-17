#pragma once

#include <iostream>
#include <string>

class Ability {

    public:
        Ability(std::string_view name_param, unsigned int mp_cost_param);

        std::string_view getName() const;

        unsigned int getMpCost() const;

        void print(std::ostream& os) const;

    private:
        std::string name;
        unsigned int mp_cost;
};
