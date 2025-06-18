#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "gameObject.h"
#include "flame.h"
class Controller{

public:

    Controller(View&);
    void run();
	void handleBombExplosions_();   
	void handleFlameCollisions_();  
private:

    void handleInput(int);
    void update();   
    // Model
    std::vector<GameObject*> _objs;
        std::vector<Flame> _flames;
        bool gameOver_ = false;  

    // View
    View& _view;
};




#endif

