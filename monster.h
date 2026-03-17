#pragma once

#include <iostream>
#include "pointwell.h"

class Monster {

    public:
        Monster(std::string_view name_param, unsigned int hp_param, unsigned int damage_param);

        const unsigned int getCurrentHP() const;
        const unsigned int getMaxHP() const;

        void takeDamage(unsigned int damage_param);

        const unsigned int attack() const;

        void print(std::ostream& os) const;

    private:
        std::string name;
        PointWell HP;
        unsigned int damage;
};
