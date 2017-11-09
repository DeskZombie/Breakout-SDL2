#include "Paddle.h" 
#include "Constants.h" 
#include <iostream> 

// TODO: if window is resizable, paddleBox should be relative to WINDOW dimensions 

Paddle::Paddle()
{
	paddleBox = { WINDOW_WIDTH/2 - PADDLE_WIDTH/2, WINDOW_HEIGHT*7/8 - PADDLE_HEIGHT/2, 
				  PADDLE_WIDTH, PADDLE_HEIGHT }; 
	velocity = { 0, 0 }; 
}

void Paddle::control() 
{
	const Uint8* keyStates = SDL_GetKeyboardState( NULL ); 
	if( keyStates[ SDL_SCANCODE_LEFT ] ) 
		velocity.x = -PADDLE_VELOCITY; 
	else if( keyStates[ SDL_SCANCODE_RIGHT ] ) 
		velocity.x = PADDLE_VELOCITY; 
	else 
		velocity.x = 0; 
}

void Paddle::update()
{
	// update x position 
	paddleBox.x += velocity.x; 
	// if there's a wall collision, go back 
	if( paddleBox.x < 0 || paddleBox.x + paddleBox.w > WINDOW_WIDTH ) 
	{
		paddleBox.x -= velocity.x; 
	}
}

void Paddle::render( SDL_Renderer* renderer ) 
{
	SDL_SetRenderDrawColor( renderer, PAD_COLOR.r, PAD_COLOR.g, PAD_COLOR.b, PAD_COLOR.a ); 
	SDL_RenderFillRect( renderer, &paddleBox ); 
}

SDL_Rect Paddle::getPaddleBox() const 
	{ return paddleBox; } 

void Paddle::reset() 
{
	paddleBox = { WINDOW_WIDTH/2 - PADDLE_WIDTH/2, WINDOW_HEIGHT*7/8 - PADDLE_HEIGHT/2, 
				  PADDLE_WIDTH, PADDLE_HEIGHT }; 
}


