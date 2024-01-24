#include <vector>
#include <SDL2/SDL.h>
#include <map.h>
#include <math.h>


Map::Map(int p_width, int p_height){
    width = p_width;
    height = p_height;
    Matrix.assign(width * height, 0);
}
void Map::assignCell(int x, int y, bool state){
    Matrix[x + y * width] = state;
}
void Map::assignCellLine(int x1, int y1, int x2, int y2, int state){
    if(x1 == x2 && y1 == y2)
        return;
    if(abs(x2 - x1) >= abs(y2 - y1)){
        double y = y1;
        int dir = (x2 - x1) > 0 ? 1 : -1;
        for(double x = x1; x != x2; x += dir){
            double realY = ((double)(y2 - y1) / (double)(x2 - x1)) * x + ((double)(y1 * x2 - y2 * x1) / (double)(x2 - x1));
            y = std::round(realY);
            this->assignCell(x, y, state);
        }
    }
    else{
        double x = x1;
        int dir = (y2 - y1) > 0 ? 1 : -1;
        for(double y = y1; y != y2; y += dir){
            double realX = ((double)(x2 - x1) / (double)(y2 - y1)) * y + ((double)(x1 * y2 - x2 * y1) / (double)(y2 - y1));
            x = std::round(realX);
            this->assignCell(x, y, state);
        }
    }
}
bool Map::getCell(int x, int y){
    return Matrix[x + y * width];
}
void Map::reset(){
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            this->assignCell(x, y, 0);
}
void Map::update(int x, int y, Map *prev){
    int dir[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int neighbourCount = 0;
    for(int i = 0; i < 8; i++){
        int newX = x + dir[i][0];
        int newY = y + dir[i][1];
        if((newX >= 0 && newX < width && newY >= 0 && newY < height) && prev->getCell(newX, newY))
            neighbourCount++;
    } 
    bool cellStatus = prev->getCell(x, y);
    if(cellStatus && !(neighbourCount >= 2 && neighbourCount <= 3))
        this->assignCell(x, y, 0);
    else if(!cellStatus && neighbourCount == 3)
        this->assignCell(x, y, 1);
}
void Map::updateAll(Map *prev){
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++){
            this->update(x, y, prev);
        }
}
void Map::copy(Map *source){
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            this->assignCell(x ,y, source->getCell(x, y));
}
void Map::draw(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            if(this->getCell(x, y))
                SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
}

