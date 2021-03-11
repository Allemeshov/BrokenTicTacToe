//
// Created by Alexander on 26.02.2021.
//

#include "Graphics.h"

Graphics *Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

Graphics *Graphics::GetInstance() {
    if (sInstance == nullptr)
        sInstance = new Graphics();

    return sInstance;
}

void Graphics::Release() {
    delete sInstance;
    sInstance = nullptr;

    sInitialized = false;
}

bool Graphics::Initialized() {
    return sInitialized;
}

Graphics::Graphics() {
    mWindow = nullptr;
    mRenderer = nullptr;

    sInitialized = Init();
}

Graphics::~Graphics() {
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;

    SDL_Quit();
}

bool Graphics::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization error: %s/n", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Broken Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        printf("SDL Window error: %s/n", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (mRenderer) {
        printf("SDL Renderer error: %s/n", SDL_GetError());
        return false;
    }

    return true;
}

void Graphics::Wait(int milliseconds) {
    if (milliseconds > 0)
        SDL_Delay(milliseconds);
}

void Graphics::Render() {
    SDL_RenderPresent(mRenderer);
}

void Graphics::DrawGrid() {
    int offSet = (SCREEN_WIDTH - 3) / 3;

//    printf("1 done.");
//    Render();
//    Wait(3000);

    int x = offSet, y = offSet;

    //Clearing render
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 0);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
//    SDL_RenderPresent(mRenderer);


    //start drawing

    //drawing first vertical line
    SDL_RenderDrawLine(mRenderer, x, 0, x, 600);

    //drawing first horizontal line
    SDL_RenderDrawLine(mRenderer, 0, y, 600, y);

    //drawing second vertical line
    x += offSet;
    SDL_RenderDrawLine(mRenderer, x, 0, x, 600);

    //drawing second horizontal line
    y += offSet;
    SDL_RenderDrawLine(mRenderer, 0, y, 600, y);

//    Render();
}

void Graphics::drawCircle(int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(mRenderer, xc + x, yc + y);
    SDL_RenderDrawPoint(mRenderer, xc - x, yc + y);
    SDL_RenderDrawPoint(mRenderer, xc + x, yc - y);
    SDL_RenderDrawPoint(mRenderer, xc - x, yc - y);
    SDL_RenderDrawPoint(mRenderer, xc + y, yc + x);
    SDL_RenderDrawPoint(mRenderer, xc - y, yc + x);
    SDL_RenderDrawPoint(mRenderer, xc + y, yc - x);
    SDL_RenderDrawPoint(mRenderer, xc - y, yc - x);
//    Render();
}

void Graphics::circleBres(int xc, int yc) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x) {
        // for each pixel we will
        // draw all eight pixels
        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
//         SDL_Delay(30);
    }
}

void Graphics::DrawNought(int cellX, int cellY) {
    int offSet = (SCREEN_WIDTH - 3) / 3;
    int x = offSet / 2 + cellX * (offSet + 1);
    int y = offSet / 2 + cellY * (offSet + 1);

    circleBres(x, y);
}

void Graphics::DrawCross(int cellX, int cellY) {
    int offSet = (SCREEN_WIDTH - 3) / 3;
    int x = offSet / 4 + cellX * (offSet + 1);
    int y = offSet / 4 + cellY * (offSet + 1);

    SDL_RenderDrawLine(mRenderer, x, y + 100, x + 100, y);
    SDL_RenderDrawLine(mRenderer, x, y, x + 100, y + 100);
}

void Graphics::SetMyColor(int red, int blue, int green, int alpha) {
    SDL_SetRenderDrawColor(mRenderer, red, blue, green, alpha);
}

void Graphics::StripeWinLine(int i) {
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    int offSet = (SCREEN_WIDTH - 3) / 3;
    int x, y;
    switch (i) {
        case 0:
        case 1:
        case 2: {
            y = offSet / 2 + offSet * i;
            SDL_RenderDrawLine(mRenderer, 0, y, SCREEN_WIDTH, y);
            break;
        }
        case 3:
        case 4:
        case 5: {
            x = offSet / 2 + offSet * (i - 3);
            SDL_RenderDrawLine(mRenderer, x, 0, x, SCREEN_HEIGHT);
            break;
        }
        case 6: {
            SDL_RenderDrawLine(mRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
        }
        case 7: {
            SDL_RenderDrawLine(mRenderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 0);
            break;
        }
    }
    Render();
}
