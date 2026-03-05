#pragma once

class StatBlock {

    public:
        StatBlock();

        StatBlock(unsigned strength_param, unsigned int intelligence_param);

        unsigned int getStrength();

        unsigned int getIntelligence();

    protected:
        void increaseStats(unsigned int strength_param, unsigned int intelligence_param);

    private:
        unsigned int strength;
        unsigned int intelligence;
};
