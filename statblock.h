#pragma once

#include <vector>
#include "buff.h"

class StatBlock {

    public:
        StatBlock();

        StatBlock(unsigned strength_param, unsigned int intelligence_param);

        unsigned int getBaseStrength();
        unsigned int getBaseIntelligence();
        unsigned int getBaseDefence();

        unsigned int getStrength();
        unsigned int getIntelligence();
        unsigned int getDefence();

        void addBuff(const Buff &new_buff);
        bool removeBuff(std::string_view buff_name);

        void modArmorStrength(int str_param);
        void modArmorIntelligence(int int_param);
        void modArmorDefence(int def_param);

        void buffTurnPassed();

    protected:
        void increaseStats(unsigned int strength_param, unsigned int intelligence_param);

    private:
        unsigned int strength;
        unsigned int intelligence;
        unsigned int defence;

        int total_strength_buff;
        int total_intelligence_buff;
        int total_defence_buff;

        int total_armor_strength;
        int total_armor_intelligence;
        int total_armor_defence;

        std::vector<Buff> buffs;

        void recalculateBuffs();
};
