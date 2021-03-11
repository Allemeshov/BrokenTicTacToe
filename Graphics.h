//
// Created by Alexander on 26.02.2021.
//

#ifndef BROKENTICTACTOE_GRAPHICS_H
#define BROKENTICTACTOE_GRAPHICS_H
#include <SDL.h>

class Graphics {

public:

    static const int SCREEN_WIDTH = 603;
    static const int SCREEN_HEIGHT = 603;

private:

    static Graphics *sInstance;
    static bool sInitialized;

    const int r = 50;

    SDL_Window *mWindow;
//    SDL_Surface *mBackBuffer;
    SDL_Renderer *mRenderer;


public:

    static Graphics *GetInstance();

    static bool Initialized();

    static void Release();

    void Render();

    void DrawGrid();

    void DrawNought(int x, int y);
    void DrawCross(int x, int y);

    void SetMyColor(int red, int blue, int green, int alpha);

    static void Wait(int milliseconds);

    void StripeWinLine(int i);

private:

    void drawCircle(int xc, int yc, int x, int y);
    void circleBres(int xc, int yc);



    Graphics();

    ~Graphics();

    bool Init();
};



#endif //BROKENTICTACTOE_GRAPHICS_H
