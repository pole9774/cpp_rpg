#include "pointwell.h"

PointWell::PointWell() {
    current_value = 1;
    max_value = 1;
}

PointWell::PointWell(unsigned int current_param, unsigned int max_param) {
    if (current_param > max_param) {
        current_value = max_param;
        max_value = max_param;
    } else {
        current_value = current_param;
        max_value = max_param;
    }
}

bool PointWell::setMax(unsigned int new_max) {
    if (new_max < 1) {
        return false;
    }

    max_value = new_max;

    if (current_value > max_value) {
        current_value = max_value;
    }

    return true;
}

const unsigned int PointWell::getMax() const {
    return max_value;
}

void PointWell::reduceCurrent(unsigned int value) {
    if (value > current_value) {
        current_value = 0;
        return;
    }

    current_value -= value;
}

void PointWell::increaseCurrent(unsigned int value) {
    if (current_value + value > max_value) {
        current_value = max_value;
        return;
    }

    current_value += value;
}

const unsigned int PointWell::getCurrent() const {
    return current_value;
}
