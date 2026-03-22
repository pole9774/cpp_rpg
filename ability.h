#pragma once

#include <iostream>
#include <string>

enum class TARGET { SELF, ENEMY };
enum class STAT_MODIFIER { NONE, STRENGTH, INTELLIGENCE };

class Ability {

    public:
        Ability(std::string_view name_param, unsigned int mp_cost_param, unsigned int hp_effect_param, TARGET target_param, STAT_MODIFIER modifier_param);

        std::string_view getName() const;

        unsigned int getMpCost() const;
        unsigned int getBaseHpEffect() const;
        unsigned int getHpEffect(unsigned int user_strength, unsigned int user_intelligence) const;
        TARGET getTarget() const;

        void print(std::ostream& os) const;

    private:
        std::string name;
        unsigned int mp_cost;
        unsigned int hp_effect;
        TARGET target;
        STAT_MODIFIER modifier;
};
