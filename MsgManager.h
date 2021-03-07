//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_MSGMANAGER_H
#define BROKENTICTACTOE_MSGMANAGER_H
#include <iostream>
#include <string>

class MsgManager {

private:

    static MsgManager *msgManagerInstance;

    std::string welcome;
    std::string congrats;
    std::string rules;

public:

    void Welcome();
    void Congrats(int winner);
    void Goodbye();

    static MsgManager *GetInstance();

private:
    MsgManager();
};

#endif //BROKENTICTACTOE_MSGMANAGER_H
