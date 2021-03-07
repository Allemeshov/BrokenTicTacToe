//
// Created by Alexander on 26.02.2021.
//

#include "Field.h"

Field *Field::sInstance = NULL;
Graphics *Field::mGraphics = NULL;

Field *Field::GetInstance() {
    if (sInstance == NULL)
        sInstance = new Field();

    return sInstance;
}

void Field::Release() {
    delete sInstance;
    sInstance = NULL;

    Graphics::Release();
}

Field::Field() {
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            field[i][j] = -1;
//        }
//    }

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

    mGraphics->Render();
}

void Field::SetCell(int signCode, int x, int y) {
    field[y][x] = signCode;
}

void Field::FillGrid() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            DrawSign(field[i][j], i, j);
        }
    }
}

void Field::OutputMe() {
    mGraphics->DrawGrid();
    FillGrid();
}

void Field::CalcCoords(int *xCell, int *yCell) {
    int offSet = (Graphics::SCREEN_WIDTH - 3) / 3;

    //processing xCell
    if (*xCell < offSet) {
        *xCell = 0;
    } else if (*xCell < offSet * 2 + 1) {
        *xCell = 1;
    } else {
        *xCell = 2;
    }

    //processing yCell
    if (*yCell < offSet) {
        *yCell = 0;
    } else if (*yCell < offSet * 2 + 1) {
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
    FreeCell freeCells[6];

    int id = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (field[i][j] == -1) {
                freeCells[id].x = j;
                freeCells[id++].y = i;
            }
        }
    }

    srand((unsigned) time(NULL));

    id = rand() % id;
    FreeCell cellToFill = freeCells[id];
    field[cellToFill.y][cellToFill.x] = Cross;
}

void Field::RandNought() {
    FreeCell freeCells[6];

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

    srand((unsigned) time(NULL));

    id = rand() % id;
    FreeCell cellToFill = freeCells[id];
    field[cellToFill.y][cellToFill.x] = Nought;
}

