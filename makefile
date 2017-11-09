OBJS = main.cpp ../../LTimer.cpp ../../LTexture.cpp Paddle.cpp  Brick.cpp Ball.cpp BrickManager.cpp Button.cpp 

OBJ_NAME = breakout 

CC = g++ 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11 

all:$(OBJS) 
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME) 
