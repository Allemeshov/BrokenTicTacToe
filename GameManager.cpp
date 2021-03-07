//
// Created by Alexander on 26.02.2021.
//

#include "GameManager.h"

GameManager *GameManager::sInstance = nullptr;
Field *GameManager::mField = nullptr;

GameManager *GameManager::GetInstance() {
    if (sInstance == nullptr)
        sInstance = new GameManager();

    return sInstance;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;

    Field::Release();
}

GameManager::GameManager() {
    mQuit = false;


    mField = Field::GetInstance();

    mEventManager = EventManager::GetInstance();

    msgManager = MsgManager::GetInstance();
}

GameManager::~GameManager() {
    //TODO finish destructor
}

void GameManager::wait(int milliseconds) {
    Field::Wait(milliseconds);
}

void GameManager::Run() {
    msgManager->Welcome();

    wait(2000);
    int currEvent;
    while (!mQuit) {
        // output field
        mField->OutputMe();


        int xMouse, yMouse;
        int xCell, yCell;

        //listen to events
        currEvent = mEventManager->GetNewEvent(&xMouse, &yMouse);

        //determine the event
        if (currEvent == mEventManager->Quited) {
            mQuit = true;
            msgManager->Goodbye();
            continue;
        } else if (currEvent == mEventManager->LBM) {
            mField->CalcCoords(&xCell, &yCell);
            mField->SetCell(mField->Cross, xCell, yCell);
        } else if (currEvent == mEventManager->RBM) {
            mField->CalcCoords(&xCell, &yCell);
            mField->SetCell(mField->Nought, xCell, yCell);
        } else if (currEvent == mEventManager->Spaced) {
            mField->ClearMe();
        } else if (currEvent == mEventManager->QB) {
            mField->RandNought();
        } else if (currEvent == mEventManager->EB) {
            mField->RandCross();
        }

        mField->OutputMe();
    }
}