#include <vector>
#include <SDL2/SDL.h>

class Map{
    private:
        int width;
        int height;
        std::vector<bool> Matrix;
    public:
        Map(int p_width, int p_height);
        void assignCell(int x, int y, bool state); 
        void assignCellLine(int x1, int y1, int x2, int y2, int state);
        bool getCell(int x, int y);
        void reset();
        void update(int x, int y, Map *prev);
        void updateAll(Map *prev);
        void copy(Map *source);
        void draw(SDL_Renderer *renderer);
};
