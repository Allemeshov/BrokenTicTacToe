//
// Created by Alexander on 26.02.2021.
//

#include "MsgManager.h"

/*
 * «Сломанные крестики-нолики». Квадратное окно с белым фоном выглядит как сетка 3*3.
 * При клике ЛКМ по клетке в ней появляется крестик, при ПКМ – нолик.
 * Если в клетке уже стояла другая фигура, то она заменяется.
 * Клавиша пробел очищает поле.
 * Клавиша Q предлагает компьютеру поставить в случайную клетку «нолик», а клавиша E – крестик.
 * */

MsgManager *MsgManager::msgManagerInstance = nullptr;
MsgManager *MsgManager::GetInstance() {
    if(msgManagerInstance == nullptr)
        msgManagerInstance = new MsgManager();

    return msgManagerInstance;
}


MsgManager::MsgManager() {
    welcome = "\nHello!\n\nThis is...\n\tBROKEN TIC-TAC-TOE\n\n";
    congrats = "\nGood game, well played! ";
    rules = "Rules are quite simple:\n\t1. You have a square field 3x3 where you can place your figures: Cross or Nought.\n\t2. Hover the cell and press left key button to place Cross or right one for Nought.\n\t3. If in this cell already was a symbol it's not a problem because it'll be replaced!\n\t4. Press SPACE to clear the field.\n\t5. Press Q to make computer place a random Nought and E for Cross.\n";
}

void MsgManager::Welcome() {
    std::cout << welcome;
}

void MsgManager::Goodbye() {
    std::cout << "\n\nIt was a nice game! See you soon.\n\n";
}

void MsgManager::Congrats(int winner) {
    std::cout << congrats;
    if (winner == 0)
        std::cout << "Winner is Nought!";
    else if(winner == 1)
        std::cout << "Winner is Cross!";
    else
        std::cout << "This is Draw!";
}