#pragma once

#include <string>

class Buff {
    public:
        Buff() = default;
        Buff(std::string_view name_param, int strength_buff_param, int intelligence_buff_param, int defence_buff_param);
        ~Buff() = default;

        std::string_view getName() const;
        int getStrengthBuff() const;
        int getIntelligenceBuff() const;
        int getDefenceBuff() const;

    private:
        std::string name;
        int strength_buff;
        int intelligence_buff;
        int defence_buff;
};
