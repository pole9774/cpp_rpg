#pragma once

class PointWell {

    public:
        PointWell();
        PointWell(unsigned int current_param, unsigned int max_param);

        bool setMax(unsigned int new_max);

        const unsigned int getMax() const;

        void reduceCurrent(unsigned int value);

        void increaseCurrent(unsigned int value);

        const unsigned int getCurrent() const;

    private:
        unsigned int current_value;
        unsigned int max_value;
};
