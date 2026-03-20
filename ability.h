#pragma once

#include <iostream>
#include <string>

enum class TARGET { SELF, ENEMY };

class Ability {

    public:
        Ability(std::string_view name_param, unsigned int mp_cost_param, unsigned int hp_effect_param, TARGET target_param);

        std::string_view getName() const;

        unsigned int getMpCost() const;
        unsigned int getHpEffect() const;
        TARGET getTarget() const;

        void print(std::ostream& os) const;

    private:
        std::string name;
        unsigned int mp_cost;
        unsigned int hp_effect;
        TARGET target;
};
