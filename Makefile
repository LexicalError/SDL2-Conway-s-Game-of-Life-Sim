SRC_DIR := src
OBJ_DIR := build/objects
APP_DIR := build/
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE_DIR := -I include
SDL_INCLUDES := -I lib/include
SDL_LINKS := -L lib/lib -lmingw32 -lSDL2main -lSDL2
CPPFLAGS := -Wall -g 

main.exe: $(OBJ_FILES)
	g++ -o $(APP_DIR)/$@ $^ $(SDL_LINKS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(SDL_INCLUDES) $(INCLUDE_DIR) -c -o $@ $<

# main.cpp: main.cpp
# 	g++ -Wall -g -c main.cpp-o main.o
# *.o: /build/*.o /main.o
# 	g++ -I /lib/include -L lib/lib  -lmingw32 -lSDL2main -lSDL2 -o main