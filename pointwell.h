#pragma once

class PointWell {

    public:
        PointWell();
        PointWell(unsigned int current_param, unsigned int max_param);

        bool setMax(unsigned int new_max);

        unsigned int getMax();

        void reduceCurrent(unsigned int value);

        void increaseCurrent(unsigned int value);

        unsigned int getCurrent();

    private:
        unsigned int current_value;
        unsigned int max_value;
};
