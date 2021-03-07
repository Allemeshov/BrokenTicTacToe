//
// Created by Alexander on 26.02.2021.
//

#include "Field.h"

Field *Field::sInstance = nullptr;
Graphics *Field::mGraphics = nullptr;

Field *Field::GetInstance() {
    if (sInstance == nullptr)
        sInstance = new Field();

    return sInstance;
}

void Field::Release() {
    delete sInstance;
    sInstance = nullptr;

    Graphics::Release();
}

Field::Field() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            field[i][j] = -1;
        }
    }

    mGraphics = Graphics::GetInstance();
};

Field::~Field() {
//    for (int i = 0; i < 3; ++i) {
//        delete[] &field[i];
//    }
//    delete[] &field;
};

void Field::Wait(int milliseconds) {
    Graphics::Wait(milliseconds);
}

bool Field::IsInitialized() {
    return Graphics::Initialized();
}

int Field::CheckCell(int x, int y) {
    if (x < 0 || x > 2)
        return -1;

    if (y < 0 || y > 2)
        return -1;

    return field[y][x];
}

void Field::DrawSign(int signCode, int x, int y) {
    if (signCode == Nought)
        mGraphics->DrawNought(x, y);
    else if (signCode == Cross)
        mGraphics->DrawCross(x, y);

//    mGraphics->Render();
}

void Field::SetCell(int signCode, int x, int y) {
    field[y][x] = signCode;
}

void Field::FillGrid() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            DrawSign(field[i][j], j, i);
        }
    }
}

void Field::OutputMe() {
    mGraphics->DrawGrid();
    FillGrid();
    mGraphics->Render();
}

void Field::CalcCoords(int xMouse, int yMouse, int *xCell, int *yCell) {
    int offSet = (Graphics::SCREEN_WIDTH - 3) / 3;

    //processing xCell
    if (xMouse < offSet) {
        *xCell = 0;
    } else if (xMouse < offSet * 2 + 1) {
        *xCell = 1;
    } else {
        *xCell = 2;
    }

    //processing yCell
    if (yMouse < offSet) {
        *yCell = 0;
    } else if (yMouse < offSet * 2 + 1) {
        *yCell = 1;
    } else {
        *yCell = 2;
    }
}

void Field::ClearMe() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            field[i][j] = -1;
        }
    }
}

void Field::RandCross() {
    FreeCell freeCells[9];

    int id = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (field[i][j] == -1) {
                freeCells[id].x = j;
                freeCells[id++].y = i;
            }
        }
    }

    if (id > 0) {
        id = rand() % id;
        FreeCell cellToFill = freeCells[id];
        field[cellToFill.y][cellToFill.x] = Cross;
    }
}

void Field::RandNought() {
    FreeCell freeCells[9];

    int id = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (field[i][j] == -1) {
                freeCells[id].x = j;
                freeCells[id].y = i;
                ++id;
            }
        }
    }

    if (id > 0) {
        id = rand() % id;
        FreeCell cellToFill = freeCells[id];
        field[cellToFill.y][cellToFill.x] = Nought;
    }
}

bool Field::CheckFinishGame(int *winner) {
    bool isFinished = true;

    int sign;
    //checking rows
    for (int i = 0; i < 3; ++i) {
        sign = field[i][0];
        if (sign == -1)
            break;
        for (int j = 1; j < 3; ++j) {
            isFinished = field[i][j] == sign && isFinished;
        }
        if (isFinished) {
            *winner = sign;
            return isFinished;
        }
    }

    //checking columns
    isFinished = true;
    for (int i = 0; i < 3; ++i) {
        sign = field[0][i];
        if (sign == -1)
            break;
        for (int j = 1; j < 3; ++j) {
            isFinished = field[j][i] == sign && isFinished;
        }
        if (isFinished) {
            *winner = sign;
            return isFinished;
        }
    }

    //checking main diagonal
    isFinished = true;
    sign = field[0][0];
    if (sign != -1) {
        for (int i = 1; i < 3; ++i) {
            isFinished = field[i][i] == sign && isFinished;
        }
        if (isFinished) {
            *winner = sign;
            return isFinished;
        }
    }

    //checking sub diagonal
    sign = field[2][0];
    if (sign != -1) {

        for (int i = 0; i < 3; ++i) {
            isFinished = field[2 - i][i] == sign && isFinished;
        }
        if (isFinished) {
            *winner = sign;
            return isFinished;
        }
    }

    bool fullPlaced = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fullPlaced = field[i][j] != -1;
        }
    }
    if (fullPlaced) {
        *winner = -1;
        return true;
    }

    return false;
}

