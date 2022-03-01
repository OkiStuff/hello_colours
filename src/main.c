/**

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

Author: Frankie A. / cookieguy
Platform: Nintendo Switch (NX)
SDK: DevKitPro Open-Source libnx
**/


#include <stdlib.h>
#include <SDL.h>

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080



void draw_rectangle(SDL_Renderer *renderer, int x, int y)
{
    // R
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect r = {x, y, 64, 64};
    SDL_RenderFillRect(renderer, &r);

    // G
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect g = {x + 64, y, 64, 64};
    SDL_RenderFillRect(renderer, &g);

    // B
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect b = {x + 128, y, 64, 64};
    SDL_RenderFillRect(renderer, &b);
}

int main(void)
{
    SDL_Event event;
    SDL_Window *win;
    SDL_Renderer *renderer;
    
    int w,h;
    int color = 0;
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    win = SDL_CreateWindow("Hello Colours!", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!win)
    {
        SDL_Log("Failed to initialize SDL Context: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    for (int i = 0; i < 2; i++)
    {
        if (SDL_JoystickOpen(i) == NULL)
        {
            SDL_Log("Failed to get access to Joystick %i: %s", i, SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }

    int close = 0;
    
    while (!close)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_JOYBUTTONDOWN:
                if (event.jbutton.which == 0)
                {
                    if (event.jbutton.button == 10) close = 1;
                    else if (event.jbutton.button == 1)
                    {
                        color++;
                        if (color >= 10) color = 0;
                    }
                }
                break;
            
            default:
                break;
            }

            switch (color)
            {
            case 0:
                SDL_SetRenderDrawColor(renderer, 255,255,255,255);
                break;
            
            case 1:
                SDL_SetRenderDrawColor(renderer, 84,84,84,255);
                break;

            case 2:
                SDL_SetRenderDrawColor(renderer, 255,0,0,255);
                break;

            case 3:
                SDL_SetRenderDrawColor(renderer, 255,153,51,255);
                break;

            case 4:
                SDL_SetRenderDrawColor(renderer, 0,48,143,255);
                break;

            case 5:
                SDL_SetRenderDrawColor(renderer, 0,128,255,255);
                break;

            case 6:
                SDL_SetRenderDrawColor(renderer, 102,255,102,255);
                break;

            case 7:
                SDL_SetRenderDrawColor(renderer, 255,255,51,255);
                break;

            case 8:
                SDL_SetRenderDrawColor(renderer, 255,204,255,255);
                break;

            case 9:
                SDL_SetRenderDrawColor(renderer, 178,102,255,255);
                break;
            
            case 10:
                SDL_SetRenderDrawColor(renderer, 255, 102,255,255);
                break;

            default:
                break;
            }
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}