#ifndef CONSTANTS_H 
#define CONSTANTS_H 

#include <SDL.h> 

const int WINDOW_WIDTH = 800; 
const int WINDOW_HEIGHT = 600; 
const SDL_Color BG_COLOR = { 100, 100, 100, 255 }; 

const int FRAME_RATE = 60; 
const int TICKS_PER_FRAME = 1000 / FRAME_RATE; 


const int PADDLE_WIDTH = 100; 
const int PADDLE_HEIGHT = 20; 
const int PADDLE_VELOCITY = 5; 
const SDL_Color PAD_COLOR = { 0, 0, 0, 255 }; 

const int BRICK_DIMENSION = 50; 
const int BRICK_WIDTH = BRICK_DIMENSION; 
const int BRICK_HEIGHT = 20; 
const int BRICK_VELOCITY = 5; 
const SDL_Color BRK_COLOR_ACTIVE = { 200, 0, 0, 255 }; 
const SDL_Color BRK_COLOR_INACTIVE = { 0, 0, 0, 255 }; 

const int BALL_DIMENSION = 20; 
const int BALL_WIDTH = BALL_DIMENSION; 
const int BALL_HEIGHT = BALL_DIMENSION; 
const int BALL_VELOCITY = 5; 
const SDL_Color BAL_COLOR = { 50, 50, 50, 255 }; 

const int BUTTON_WIDTH = 90; 
const int BUTTON_HEIGHT = 60; 

#endif 
