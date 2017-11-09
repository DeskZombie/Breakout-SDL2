#include <cmath> 
#include <iostream> 
#include "Ball.h" 
#include "BrickManager.h" 

// TODO: fix the ball getting stuck in the paddle on horizontal motion-collision 
// check out update() or bounce() for this 

// TODO: test for miscalculations in bounce() 
// the ball occasionally bounces in the wrong direction 

// TODO: make my own dynamic array for the BoxManager class 
// look at multiCollision 

using namespace std; 

Ball::Ball( Paddle paddle ) 
{
	launched = false; 
	launching = false; 
	ballBox = { paddle.getPaddleBox().x + paddle.getPaddleBox().w/2, 
				paddle.getPaddleBox().y - BALL_HEIGHT, 
				BALL_WIDTH, BALL_HEIGHT }; 
	velocity = { 0, 0 }; 
}

void Ball::control( SDL_Event e ) 
{
	if( !launched && e.type == SDL_MOUSEBUTTONDOWN ) 
	{
		this->launch(); 
	}
}

void Ball::update( Paddle paddle, BrickManager &brickManager ) 
{
	if( !launched ) 
	{
		// center the ball above the paddle 
		ballBox = { paddle.getPaddleBox().x + paddle.getPaddleBox().w/2 - BALL_WIDTH/2, 
					   paddle.getPaddleBox().y - BALL_HEIGHT, 
					   BALL_WIDTH, BALL_HEIGHT }; 
	}
	else 
	{
		ballBox.x += velocity.x; 
		if( ballBox.x < 0 || ballBox.x + ballBox.w > WINDOW_WIDTH || 
			this->collision( paddle.getPaddleBox() ) || 
			this->multiCollision( brickManager ) ) 
		{
			velocity.x *= -1; 
			ballBox.x += velocity.x; 
		}
		
		
		ballBox.y += velocity.y; 
		if( ballBox.y < 0 || ballBox.y + ballBox.h > WINDOW_HEIGHT || 
			this->collision( paddle.getPaddleBox() ) || 
			this->multiCollision( brickManager ) ) 
		{
			if( this->collision( paddle.getPaddleBox() ) ) 
			{
				this->bounce( paddle ); 
				//ballBox.y += velocity.y; 
				//std::cout << "bounce\t"; 
			}
			else 
			{
				velocity.y *= -1; 
				//ballBox.y += velocity.y; 
				//std::cout << "wall\t"; 
				
			} 
			// destroy brick if ball collides with it 
			
			
			ballBox.y += velocity.y; 
		}
		
	}
	ballCenter = { ballBox.x + BALL_WIDTH/2, ballBox.y + BALL_HEIGHT/2 }; 
}

void Ball::render( SDL_Renderer* renderer ) 
{
	SDL_SetRenderDrawColor( renderer, BAL_COLOR.r, BAL_COLOR.g, BAL_COLOR.b, BAL_COLOR.a ); 
	SDL_RenderFillRect( renderer, &ballBox ); 
	
	// render the center 
	// SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); 
	// SDL_RenderDrawPoint( renderer, ballCenter.x, ballCenter.y ); 
}

void Ball::reset() 
{
	launched = false; 
}

bool Ball::launch() 
{
	SDL_Point mousePos; 
	
	// get mouse position 
	SDL_GetMouseState( &mousePos.x, &mousePos.y ); 
	
	// create vector: delta_x = mousePos.x - ballCenter.x 
	// 				  delta_y = mousePos.y - ballCenter.y 
	normalVector.x = mousePos.x - ballCenter.x; 
	normalVector.y = mousePos.y - ballCenter.y; 
	
	// normalize the vector by dividing it by its magnitude 
	float magnitude = hypot( normalVector.x, normalVector.y ); 
	normalVector.x /= magnitude; 
	normalVector.y /= magnitude; 
		
	// scale the normal vector to be at target speed 
	velocity.x = normalVector.x * BALL_VELOCITY; 
	velocity.y = normalVector.y * BALL_VELOCITY; 
	
	// update these values so a collision doesn't register 
	ballBox.x += velocity.x; 
	ballBox.y += velocity.y; 
	ballCenter = { ballBox.x + BALL_WIDTH/2, ballBox.y + BALL_WIDTH/2 }; 
	
	launched = true; 
}

void Ball::bounce( Paddle paddle ) 
{
	SDL_Point paddleCenter = { paddle.getPaddleBox().x + PADDLE_WIDTH/2, 
							   paddle.getPaddleBox().y + PADDLE_HEIGHT/2 }; 
	// calculate the displacement vector between paddleCenter and ballCenter 
	normalVector.x =  ballCenter.x - paddleCenter.x; 
	normalVector.y =  ballCenter.y - paddleCenter.y; 
	
	// normalize the vector by dividing by its magnitude 
	float magnitude = hypot( normalVector.x, normalVector.y ); 
	normalVector.x /= magnitude; 
	normalVector.y /= magnitude; 
		
	// scale the normal vector by the ball's target speed 
	velocity.x = normalVector.x * BALL_VELOCITY; 
	velocity.y = normalVector.y * BALL_VELOCITY; 
		
}

bool Ball::collision( SDL_Rect collidedObject ) 
{
	// define sides of ball & sides of <other rectangle> 
	int aL, bL; 
	int aR, bR; 
	int aT, bT; 
	int aB, bB; 
	
	// define ball sides 
	aL = ballBox.x; 
	aR = ballBox.x + ballBox.w; 
	aT = ballBox.y; 
	aB = ballBox.y + ballBox.h; 
	
	// collisions w/ paddle first, so define paddle sides 
	bL = collidedObject.x; 
	bR = collidedObject.x + collidedObject.w; 
	bT = collidedObject.y; 
	bB = collidedObject.y + collidedObject.h; 
	
	// perform separating axis test 
	if( aL >= bR ) 
		return false; 
	if( aR <= bL ) 
		return false; 
	if( aT >= bB ) 
		return false; 
	if( aB <= bT ) 
		return false; 
	
	return true; 
	
}

bool Ball::multiCollision( BrickManager &brickManager ) 
{
	// check all brick boxes 
	for( int i = 0; i < brickManager.getNumBricks(); i++ ) 
	{
		// if the ball box collided with the brick box 
		if( this->collision( brickManager.getBrick( i ).getBrickBox() ) && 
			brickManager.getBrick( i ).isActive() ) 
		{
			// there was a collision (obviously) 
			brickManager.setActive( i, false ); 
			return true; 
		} 
	}
	// otherwise, there was no collision 
	return false; 
}





