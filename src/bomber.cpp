#include "bomber.h"
#include <cstdlib>      
#include <vector>

Bomber::Bomber(Icon icon, Position pos)
    : GameObject(icon, pos), _cd(rand() % 15 + 10) {}

/* ----------- 每幀更新 ----------- */
void Bomber::update() {
    if (_cd > 0) --_cd;


        int dir = rand() % 4;

    switch (dir) {
        case 0: _pos.x()++; break;
        case 1: _pos.x()--; break;
        case 2: _pos.y()++; break;
        case 3: _pos.y()--; break;
    }                
}
std::vector<Position> Bomber::getOccupiedArea() const {
    return { _pos };
}

/* ----------- 爆炸：產生十字火焰 ----------- */
void Bomber::explodeNow(std::vector<Flame>& flames) const {
    constexpr int R = 3;               
    Position p = getPosition();
    for (int r = 0; r <= R; ++r) {
        flames.push_back({ {p.x()+r, p.y()} });
        flames.push_back({ {p.x()-r, p.y()} });
        flames.push_back({ {p.x(),   p.y()+r} });
        flames.push_back({ {p.x(),   p.y()-r} });
    }
    flames.push_back({p});            
}


void Bomber::resetTimer() {
    _cd = rand() % 15 + 10;
}

