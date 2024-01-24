#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <map.h>

int WIDTH = 800, HEIGHT = 600;
float SCALE = 10;


int main( int argc, char *argv[]){
    Map map(WIDTH / SCALE, HEIGHT / SCALE);
    Map mapPrev(WIDTH / SCALE, HEIGHT / SCALE);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

    SDL_RenderSetScale(renderer, SCALE, SCALE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);



    SDL_Event event;
    bool running = true;
    bool pause = true;
    bool mouseDown = false;
    uint8_t mouseButton = 0;
    int prevMouseX = -1;
    int prevMouseY = -1;
    while(running){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                running = false;
            else if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_p)
                    pause = !pause;
                else if(event.key.keysym.sym == SDLK_r)
                    map.reset();
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP){
                mouseButton = event.button.button;
                if(event.button.state == SDL_PRESSED && mouseDown == false)
                    mouseDown = true;
                else if(event.button.state == SDL_RELEASED && mouseDown == true){
                    mouseDown = false;
                    prevMouseX = -1;
                    prevMouseY = -1;
                }
            }
        }
        if(mouseDown && (mouseButton == SDL_BUTTON_LEFT || mouseButton == SDL_BUTTON_RIGHT)){
            bool mode = mouseButton == SDL_BUTTON_LEFT ? 1 : 0; 
            int mouseX;
            int mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX >= 0 && mouseX < WIDTH && mouseY >= 0 && mouseY < HEIGHT){ 
                map.assignCell(mouseX / SCALE, mouseY / SCALE, mode);
                if(prevMouseX >= 0 && prevMouseY >= 0){
                    map.assignCellLine(prevMouseX / SCALE, prevMouseY / SCALE, mouseX / SCALE, mouseY / SCALE, mode);
                }
                prevMouseX = mouseX;
                prevMouseY = mouseY;
            }
        }
        if(!pause){
            mapPrev.copy(&map);
            map.updateAll(&mapPrev);    
        }
        map.draw(renderer);
        SDL_Delay(30);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
