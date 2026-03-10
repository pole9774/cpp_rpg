#pragma once

#include <vector>
#include "buff.h"

class StatBlock {

    public:
        StatBlock();

        StatBlock(unsigned strength_param, unsigned int intelligence_param);

        unsigned int getBaseStrength();
        unsigned int getBaseIntelligence();

        unsigned int getStrength();
        unsigned int getIntelligence();

        void addBuff(const Buff &new_buff);
        bool removeBuff(std::string_view buff_name);

    protected:
        void increaseStats(unsigned int strength_param, unsigned int intelligence_param);

    private:
        unsigned int strength;
        unsigned int intelligence;

        int total_strength_buff;
        int total_intelligence_buff;

        std::vector<Buff> buffs;

        void recalculate_buffs();
};
