//
// Created by Alexander on 26.02.2021.
//

#include "GameManager.h"

GameManager *GameManager::gameManagerInstance = nullptr;
Field *GameManager::mField = nullptr;

GameManager *GameManager::GetInstance() {
    if (gameManagerInstance == nullptr)
        gameManagerInstance = new GameManager();

    return gameManagerInstance;
}

void GameManager::Release() {
    delete gameManagerInstance;
    gameManagerInstance = nullptr;

    Field::Release();
}

GameManager::GameManager() {
    mQuit = false;


    mField = Field::GetInstance();

    mEventManager = EventManager::GetInstance();

    msgManager = MsgManager::GetInstance();
}

GameManager::~GameManager() {
    Field::Release();
}

void GameManager::wait(int milliseconds) {
    Field::Wait(milliseconds);
}

void GameManager::Run() {
    msgManager->Welcome();

    wait(2000);
    int currEvent;
    int xMouse, yMouse;
    int xCell, yCell;
    bool isTriggered = true;
    int winner;

    // output field
    mField->OutputMe();
    while (!mQuit) {
        //listen to events
        currEvent = mEventManager->GetNewEvent(&xMouse, &yMouse);

        //determine the event
        if (currEvent == mEventManager->Quited) {
            mQuit = true;
            msgManager->Goodbye();
            continue;
        } else if (currEvent == mEventManager->LBM) {
            isTriggered = true;
            mField->CalcCoords(xMouse, yMouse, &xCell, &yCell);
            mField->SetCell(mField->Cross, xCell, yCell);
        } else if (currEvent == mEventManager->RBM) {
            isTriggered = true;
            mField->CalcCoords(xMouse, yMouse, &xCell, &yCell);
            mField->SetCell(mField->Nought, xCell, yCell);
        } else if (currEvent == mEventManager->Spaced) {
            isTriggered = true;
            mField->ClearMe();
        } else if (currEvent == mEventManager->QB) {
            isTriggered = true;
            mField->RandNought();
        } else if (currEvent == mEventManager->EB) {
            isTriggered = true;
            mField->RandCross();
        }

        if (isTriggered) {
            isTriggered = false;
            mField->OutputMe();
            mQuit = mField->CheckFinishGame(&winner);
            if (mQuit) {
                msgManager->Congrats(winner);

                wait(4000);
                break;
            }
        }

        wait(5);
    }
}