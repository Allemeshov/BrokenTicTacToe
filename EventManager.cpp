//
// Created by Alexander on 26.02.2021.
//
#include "EventManager.h"

EventManager *EventManager::eventManagerInstance = nullptr;

EventManager *EventManager::GetInstance() {
    if (eventManagerInstance == nullptr)
        eventManagerInstance = new EventManager();

    return eventManagerInstance;
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
        else if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_ESCAPE)
            return Quited;
        else if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_SPACE)
            return Spaced;
        else if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_q)
            return QB;
        else if (gameEvent.type == SDL_KEYUP && gameEvent.key.keysym.sym == SDLK_e)
            return EB;
        else if (gameEvent.button.button == SDL_BUTTON_LEFT) {
            SDL_GetMouseState(xMouse, yMouse);
            return LBM;
        } else if (gameEvent.button.button == SDL_BUTTON_RIGHT) {
            SDL_GetMouseState(xMouse, yMouse);
            return RBM;
        }
    }
    return -1;
}
