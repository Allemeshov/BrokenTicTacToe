//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_GAMEMANAGER_H
#define BROKENTICTACTOE_GAMEMANAGER_H

#include <SDL.h>
#include "EventManager.h"
#include "Field.h"
#include "MsgManager.h"

class GameManager {
    //props
private:

    static GameManager *gameManagerInstance;

    MsgManager *msgManager;

    EventManager *mEventManager;

    static Field *mField;

    bool mQuit;

//    SDL_Event mEvents;

public:

    static GameManager *GetInstance();

    static void Release();

    void Run();

private:

    void wait(int milliseconds);

    GameManager();

    ~GameManager();
};

#endif //BROKENTICTACTOE_GAMEMANAGER_H
