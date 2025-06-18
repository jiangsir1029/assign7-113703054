#ifndef INTERACTION_HANDLER_H
#define INTERACTION_HANDLER_H

#include "gameObject.h"
#include "bomber.h"
#include "player.h"
#include <vector>
#include "view.h"
#include "flame.h"
class InteractionHandler {
public:
	    static void handleInteractions(std::vector<GameObject*>& objects,
                                   std::vector<Flame>& flames,
								   View& view);//配合繪製火焰
};

#endif

