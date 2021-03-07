//
// Created by Alexander on 26.02.2021.
//
#include "EventManager.h"

EventManager *EventManager::sInstance = NULL;

EventManager *EventManager::GetInstance() {
    if (sInstance == NULL)
        sInstance = new EventManager();

    return sInstance;
}
EventManager::EventManager() {
    std::cout << "Event manager constructed!\n";
}
EventManager::~EventManager() {
    std::cout << "Event manager destructed!\n";
}

int EventManager::GetNewEvent(int *xMouse, int *yMouse) {
    while (SDL_PollEvent(&gameEvent)) {
        if (gameEvent.type == SDL_QUIT)
            return Quited;
        if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_ESCAPE)
            return Quited;
        if (gameEvent.type == SDL_BUTTON_LEFT) {
            SDL_GetMouseState(xMouse, yMouse);
            return LBM;
        }
        if (gameEvent.type == SDL_BUTTON_RIGHT) {
            SDL_GetMouseState(xMouse, yMouse);
            return RBM;
        }
        if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_SPACE)
            return Spaced;
        if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_q)
            return QB;
        if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_e)
            return EB;
    }
    return -1;
}
