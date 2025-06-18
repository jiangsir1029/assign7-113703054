#ifndef FLAME_H
#define FLAME_H

#include "unit.h"

struct Flame {
    Position pos;
    int timer;

    Flame(Position p, int t = 3) : pos(p), timer(t) {}
};

#endif

