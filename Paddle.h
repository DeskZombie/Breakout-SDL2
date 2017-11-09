#ifndef PADDLE_H 
#define PADDLE_H 

#include <SDL.h> 

class Paddle
{
	public: 
		// set position 
		Paddle(); 
		
		// gets input (left & right keys) 
		void control(); 
		
		void update(); 
		
		// display 
		void render( SDL_Renderer* ); 
		
		SDL_Rect getPaddleBox() const; 
		
		void reset(); 
		
	private:
		SDL_Point paddleCenter; 
		SDL_Rect paddleBox; 
		SDL_Point velocity; 
		
}; 

#endif 
