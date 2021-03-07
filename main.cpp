/*
 * «Сломанные крестики-нолики». Квадратное окно с белым фоном выглядит как сетка 3*3.
 * При клике ЛКМ по клетке в ней появляется крестик, при ПКМ – нолик.
 * Если в клетке уже стояла другая фигура, то она заменяется.
 * Клавиша пробел очищает поле.
 * Клавиша Q предлагает компьютеру поставить в случайную клетку «нолик», а клавиша E – крестик.
 * */

#include "GameManager.h"

int main() {

    GameManager *gm = GameManager::GetInstance();

    gm->Run();

    GameManager::Release();
    gm = nullptr;

    return 0;
}
