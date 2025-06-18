#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.h"

class Player : public GameObject {
public:
    Player(Icon icon, Position pos);

    void update() override;
};

#endif
