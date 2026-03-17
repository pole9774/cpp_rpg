#pragma once

#include "pointwell.h"

class Monster {

    public:
        Monster(unsigned int hp_param, unsigned int damage_param);

        const unsigned int getCurrentHP() const;
        const unsigned int getMaxHP() const;

        void takeDamage(unsigned int damage_param);

        const unsigned int attack() const;

    private:
        PointWell HP;
        unsigned int damage;
};
