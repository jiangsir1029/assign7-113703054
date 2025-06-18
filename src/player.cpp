#include "player.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

Player::Player(Icon icon, Position pos) : GameObject(icon, pos) {}

void Player::update(){
    // 玩家 update 其實不做事，因為移動會由 controller 控制
}
