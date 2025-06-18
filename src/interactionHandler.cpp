#include "interactionHandler.h"
#include "bomber.h"
#include "flame.h"
#include "player.h"

void InteractionHandler::handleInteractions(std::vector<GameObject*>& objects, std::vector<Flame>& flames, View& view) {
    // 玩家撞炸彈or炸彈撞炸彈
    for (int i = 0; i < objects.size(); ++i) {
        for (int j = i + 1; j < objects.size(); ++j) {
            GameObject* a = objects[i];
            GameObject* b = objects[j];

            if (a->getPosition() == b->getPosition()) {
                Bomber* bomberA = dynamic_cast<Bomber*>(a);
                Bomber* bomberB = dynamic_cast<Bomber*>(b);
                Player* playerA = dynamic_cast<Player*>(a);
                Player* playerB = dynamic_cast<Player*>(b);

                if ((bomberA && playerB) || (playerA && bomberB)) {
                    if (bomberA) bomberA->explodeNow(flames);
                    if (bomberB) bomberB->explodeNow(flames);
                }

                if (bomberA && bomberB) {
                    bomberA->explodeNow(flames);
                    bomberB->explodeNow(flames);
                }
            }
        }
    }

	//火燒觸動炸彈
    for (const Flame& flame : flames) {
        for (GameObject* obj : objects) {
            Bomber* bomb = dynamic_cast<Bomber*>(obj);
            if (bomb) {
                for (const Position& p : bomb->getOccupiedArea()) {
                    if (p == flame.pos) {
                        bomb->explodeNow(flames);
                        break;
                    }
                }
            }
        }
        view.drawFire(flame.pos);
    }
}


