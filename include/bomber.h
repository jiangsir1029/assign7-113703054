#pragma once
#include <vector>          // ✨ FIX
#include "gameObject.h"    // ✨ FIX 讓 compiler 找到基底
#include "flame.h"         // 需要 Flame 結構
#include "unit.h"          // Position 在這個檔案（你說的）

class Bomber : public GameObject {
public:
    /* 依你專案的 Icon 設計，如果 GameObject 本身已經有 Icon 就可忽略 */
    Bomber(Icon icon, Position pos);

    void update();                           // 先別加 override，通過編譯再說
    bool shouldExplode() const { return _cd == 0; }
    void explodeNow(std::vector<Flame>& flames) const;
    void resetTimer();                       // 重設倒數
std::vector<Position> getOccupiedArea() const;
private:
    int _cd;                                 // count-down
};

