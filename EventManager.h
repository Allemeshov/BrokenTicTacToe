//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_EVENTMANAGER_H
#define BROKENTICTACTOE_EVENTMANAGER_H
#include <SDL.h>
#include <iostream>
#pragma once

class EventManager {
    //props
private:
    static EventManager *sInstance;

    SDL_Event gameEvent;

public:

    int Quited = 0;
    int LBM = 1;
    int RBM = 2;
    int Spaced = 3;
    int QB = 4;
    int EB = 5;

    static EventManager *GetInstance();

    int GetNewEvent(int *xMouse, int *yMouse);

    //constructs
private:
    EventManager();
    ~EventManager();
};

#endif //BROKENTICTACTOE_EVENTMANAGER_H
