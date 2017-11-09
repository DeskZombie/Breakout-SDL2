#ifndef BRICK_H 
#define BRICK_H 

#include <SDL.h> 
#include "Constants.h" 

// basically a class like Paddle, but motionless (goes downward later) 
class Brick
{
	public: 
		// like Paddle(), but takes a position 
		Brick( int x, int y ); 
		
		~Brick(); 
		
		void update(); 
		
		void render( SDL_Renderer* ); 
		
		SDL_Rect getBrickBox() const; 
		
		void setActive( bool ); 
		
		bool isActive() const; 
		
		void setColor( Uint8, Uint8, Uint8, Uint8 ); 
		
	private: 
		SDL_Point brickCenter; 
		SDL_Rect brickBox; 
		SDL_Point velocity; 
		SDL_Color brkColor; 
		bool active; 
		
}; 

#endif 
