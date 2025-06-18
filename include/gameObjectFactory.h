#include "gameObject.h"
#include "player.h"
#include "bomber.h"

struct SimpleGameObjectFactory {
    
    static GameObject* playerGameObject();
    static GameObject* randomGameObject();
};

