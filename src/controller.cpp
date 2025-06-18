#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"
#include "interactionHandler.h"
#include "flame.h"
#include "bomber.h"
#include "unit.h"

static struct termios old_termios, new_termios;

static void configure_terminal();
static void reset_terminal();
static int read_input();

Controller::Controller(View &view) : _view(view)
{

    _objs.emplace_back(SimpleGameObjectFactory::playerGameObject());

    for (int i = 0; i < 10; ++i)
        _objs.emplace_back(SimpleGameObjectFactory::randomGameObject());
}

void Controller::run()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    configure_terminal();

    int input = -1;
    clock_t start, end;

    while (true)
    {
        start = clock();

        input = read_input();
        if (input == 27)
            break;
        handleInput(input);

        handleBombExplosions_();

        _view.resetLatest();

        for (auto it = _flames.begin(); it != _flames.end();)
        {
            if (--it->timer <= 0)
                it = _flames.erase(it);
            else
                ++it;
        }

        InteractionHandler::handleInteractions(_objs, _flames, _view);

        for (GameObject *obj : _objs)
        {
            obj->update();
            _view.updateGameObject(obj);
        }

        handleFlameCollisions_();

        for (const Flame &flame : _flames)
            _view.drawFire(flame.pos);
        Position playerPos = _objs[0]->getPosition();

        for (GameObject *obj : _objs)
        {
            if (dynamic_cast<Bomber *>(obj) && obj->getPosition() == playerPos)
            {
                gameOver_ = true;
                break;
            }
        }

        if (!gameOver_)
        {
            for (const Flame &f : _flames)
            {
                if (f.pos == playerPos)
                {
                    gameOver_ = true;
                    break;
                }
            }
        }

        if (gameOver_)
        {
            _view.renderGameOver();
            break;
        }

        _view.render();

        end = clock();
        double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        if (time_taken < SPF)
        {
            int frameDelay = int((SPF - time_taken) * 1000);
            if (frameDelay > 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));
        }
    }
}

void Controller::handleInput(int keyInput)
{
    if (keyInput == -1)
        return;

    if (keyInput == 'w' || keyInput == 'W')
        _objs[0]->setDirection(UP);
    if (keyInput == 'a' || keyInput == 'A')
        _objs[0]->setDirection(LEFT);
    if (keyInput == 's' || keyInput == 'S')
        _objs[0]->setDirection(DOWN);
    if (keyInput == 'd' || keyInput == 'D')
        _objs[0]->setDirection(RIGHT);

    if (keyInput == '\t')
    {
    }
}

void Controller::update() {}

void Controller::handleBombExplosions_() {
    for (GameObject* ptr : _objs) {
        if (auto* b = dynamic_cast<Bomber*>(ptr);
            b && b->shouldExplode()) {
            b->explodeNow(_flames);
        }
    }
}   


void Controller::handleFlameCollisions_() {
    for (auto it = _objs.begin(); it != _objs.end(); ) {
    GameObject* obj = *it;   // pointer
    bool burned = false;
    for (const Flame& f : _flames) {
        if (f.pos == obj->getPosition()) {
            burned = true;
            break;
        }
    }
    if (burned) it = _objs.erase(it);
    else        ++it;
}
}

static void reset_terminal()
{
    std::printf("\e[m");    // reset colors
    std::printf("\e[?25h"); // show cursor
    std::fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

static void configure_terminal()
{
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;               // for later restore
    new_termios.c_lflag &= ~(ICANON | ECHO); // non-canonical, no echo
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    std::printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}

static int read_input()
{
    char buf[4096];
    int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

