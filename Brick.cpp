#include "Brick.h" 
#include "Constants.h" 

Brick::Brick( int x, int y ) 
{
	active = true; 
	brkColor = BRK_COLOR_ACTIVE; 
	brickCenter = { x - BRICK_WIDTH/2, y - BRICK_HEIGHT/2 }; 
	brickBox = { brickCenter.x, brickCenter.y, 
				 BRICK_WIDTH, BRICK_HEIGHT }; 
	velocity = { 0, 0 }; 
}

Brick::~Brick()
{
	brkColor = BRK_COLOR_INACTIVE; 
	active = false; 
}

void Brick::update() 
{
	
}

void Brick::render( SDL_Renderer* renderer ) 
{
	SDL_SetRenderDrawColor( renderer, brkColor.r, brkColor.g, brkColor.b, brkColor.a ); 
	SDL_RenderFillRect( renderer, &brickBox ); 
}

SDL_Rect Brick::getBrickBox() const 
	{ return brickBox; } 

void Brick::setActive( bool activeSetting )
{
	active = activeSetting; 
}

bool Brick::isActive() const 
	{ return active; } 

void Brick::setColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) 
{
	brkColor = { r, g, b, a }; 
}




