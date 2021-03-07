//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_FIELD_H
#define BROKENTICTACTOE_FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graphics.h"

class Field {
    //props
private:
    struct FreeCell {
        int x;
        int y;
    };

    int field[3][3] = {{0, 0, 0},
                       {1, 1, 1},
                       {0, 1, 0}};

    static Field *sInstance;
    static Graphics *mGraphics;

    void DrawSign(int signCode, int x, int y);

    void FillGrid();

public:
    const int Nought = 0;
    const int Cross = 1;

    int CheckCell(int x, int y);

    bool CheckFinishGame(int *winner);

    void CalcCoords(int xMouse, int yMouse, int *xCell, int *yCell);

    static Field *GetInstance();

    void SetCell(int signCode, int x, int y);

    static void Release();

    void OutputMe();

    static void Wait(int milliseconds);

    bool IsInitialized();

    void ClearMe();

    void RandCross();

    void RandNought();

private:
    Field();

    ~Field();

};

#endif //BROKENTICTACTOE_FIELD_H
