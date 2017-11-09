#ifndef BALL_H 
#define BALL_H 

#include <SDL.h> 
#include <vector> 
#include "Constants.h" 
#include "Paddle.h" 
#include "Brick.h" 
#include "Vector2.h" 
#include "BrickManager.h" 

/* similar to the paddle and brick classes, except, on construction, 
 * the ball waits for user input to move toward where the mouse clicks 
 */
class Ball 
{
	public: 
		// get a paddle position to start at 
		Ball( Paddle ); 
		
		// wait for a mouse click, then calc a launch vector from mousePos 
		void control( SDL_Event e ); 
		
		// if not launched, move with the paddle, else, bounce off the 
		// walls, and rebound from collided objects (paddle, bricks) 
		void update( Paddle, BrickManager & ); 
		
		void render( SDL_Renderer* ); 
		
		void reset(); 
		
	private: 
		// convert the launch vector into its normal
		// set the velocity to a scaled version of the normal vector 
		// add velocity to ballBox's x and y, then, if a collision exists, 
		// bounce off at an opposite angle 
		bool launch(); 
		
		// similar to launch, except the normal is calculated by 
		// the distance between the paddle and ball centers 
		void bounce( Paddle ); 
		
		bool multiCollision( BrickManager & ); 
		
		bool launching; 
		bool launched; 
		bool collision( SDL_Rect ); 
		SDL_Point ballCenter; 
		SDL_Rect ballBox; 
		SDL_Point velocity; 
		Vector2 normalVector; 
		
}; 

#endif 
