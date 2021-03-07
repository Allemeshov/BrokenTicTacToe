//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_MSGMANAGER_H
#define BROKENTICTACTOE_MSGMANAGER_H
#include <iostream>
#include <string>
#pragma once

class MsgManager {

private:

    static MsgManager *sInstance;

    std::string welcome;
    std::string rules;

public:

    void Welcome();
    void Goodbye();

    static MsgManager *GetInstance();

private:
    MsgManager();
};

#endif //BROKENTICTACTOE_MSGMANAGER_H
