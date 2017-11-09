#include "BrickManager.h" 
#include <iostream> 

BrickManager::BrickManager() 
{
	frozen = -1; 
}

void BrickManager::control( SDL_Event e )
{
	if( e.type == SDL_KEYDOWN )
	{
		if( e.key.keysym.sym == SDLK_BACKQUOTE ) 
			frozen *= -1; 
	}
	// most of the functionality is in the "frozen" mode 
	// b/c adding/removing bricks should only take place 
	// when all other game objects aren't updating 
	if( this->isFrozen() ) 
	{
		// if a mouse button was pressed 
		if( e.type == SDL_MOUSEBUTTONDOWN ) 
		{
			// prepare a point variable for the mouse location 
			SDL_Point mouse; 
			
			// get the mouse location 
			SDL_GetMouseState( &mouse.x, &mouse.y ); 
			
			// if it was the left button, add a brick to the mouse's grid location 
			if( e.button.button == SDL_BUTTON_LEFT ) 
			{
				
				this->addGridBrick( mouse.x, mouse.y ); 
			}
			// if right button, remove the brick at mouse's location 
			else if( e.button.button == SDL_BUTTON_RIGHT ) 
			{
				// check each brick 
				for( int i = 0; i < bricks.size(); i++ ) 
				{
					SDL_Rect brickRect = bricks.at( i ).getBrickBox(); 
					// if the mouse is inside this brick's rectangle, remove the brick 
					if( SDL_PointInRect( &mouse, &brickRect ) ) 
					{
						this->remove( i ); 
					}
				}
			}
		} 
	}
}

void BrickManager::update() 
{
	for( int i = 0; i < bricks.size(); i++ ) 
	{
		bricks.at( i ).update(); 
	}
	
	bool activeBrickExists; 
	
	// check if there is at least one active brick 
	for( int i = 0; i < bricks.size(); i++ ) 
	{
		if( bricks.at( i ).isActive() ) 
		{
			activeBrickExists = true; 
			i = bricks.size();
		}
	}
	// if there isn't a single active brick, change the brick color  
	if( !activeBrickExists ) 
	{
		for( int i = 0; i < bricks.size(); i++ )
		{
			bricks.at( i ).setColor( 0, 255, 0, 255 ); 
		}
	}
}

void BrickManager::add( int positionX, int positionY ) 
{
	bricks.push_back( Brick( positionX, positionY ) ); 
}

void BrickManager::setActive( int index, bool activeSetting ) 
{
	if( !activeSetting ) 
		bricks.at( index ).~Brick(); 
	else 
		bricks.at( index ).setActive( activeSetting ); 
}

void BrickManager::remove( int index ) 
{
	bricks.erase( bricks.begin() + index ); 
}

int BrickManager::getNumBricks() 
	{ return bricks.size(); }

Brick BrickManager::getBrick( int index ) const 
	{ return bricks[ index ]; } 

void BrickManager::reset() 
{
	bricks.clear(); 
}

void BrickManager::render( SDL_Renderer* renderer ) 
{
	if( this->isFrozen() ) 
	{
		// render a tinted layer over non-brick items 
		SDL_Rect tint = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }; 
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 50 ); 
		SDL_RenderFillRect( renderer, &tint ); 
		
		// show the grid for adding bricks 
		this->setGridPoints(); 
		for( int i = 0; i < gridLocations.size(); i++ ) 
		{
			SDL_SetRenderDrawColor( renderer, 0, 255, 0, 127 ); 
			SDL_RenderDrawPoint( renderer, gridLocations.at( i ).x, gridLocations.at( i ).y ); 
			
		}
		
	}
	for( int i = 0; i < bricks.size(); i++ ) 
	{
		bricks[ i ].render( renderer ); 
	}
	
	
}

bool BrickManager::isFrozen() const 
{
	if( frozen < 0 ) 
		return false; 
	else if( frozen > 0 ) 
		return true; 
}

void BrickManager::toggleFreeze() 
{
	frozen *= -1; 
}

void BrickManager::setGridPoints() 
{
	// ensure that this gets called only once for efficiency's sake 
	static int callNumber; 
	
	if( callNumber < 1 ) 
	{
		
		for( int i = 0; i < WINDOW_HEIGHT; i += BRICK_HEIGHT ) 
		{
			for( int j = 0; j < WINDOW_WIDTH; j += BRICK_WIDTH ) 
			{
				gridLocations.push_back( SDL_Point() ); 
				gridLocations.back().x = j; 
				gridLocations.back().y = i; 
			}
		}
		callNumber++; 
	}
	
}

void BrickManager::addGridBrick( int x, int y ) 
{
	// these are the objects to be validated 
	SDL_Point testPoint = { x, y }; 
	SDL_Rect testRect; 
	
	// check for the rectangle that the point is in 
	for( int i = 0; i < gridLocations.size(); i++ ) 
	{
		testRect = { gridLocations.at( i ).x, 
					 gridLocations.at( i ).y, 
					 BRICK_WIDTH, BRICK_HEIGHT }; 
		// if the mouse falls inside this grid rectangle 
		// and there isn't already a rectangle there 
		if( SDL_PointInRect( &testPoint, &testRect ) ) 
		{
			// if this is the first brick being added 
			if( bricks.size() == 0 ) 
			{
				// add a new brick at the grid point (need the plus's for 
				// the offset since it's centered by default ) 
				this->add( gridLocations.at( i ).x + BRICK_WIDTH/2, 
						   gridLocations.at( i ).y + BRICK_HEIGHT/2 ); 
			}
			// else, ensure that a brick isn't being stacked 
			else 
			{
				bool canAdd = true; 
				
				for( int i = 0; i < bricks.size(); i++ ) 
				{
					SDL_Rect existingRect = bricks.at( i ).getBrickBox(); 
					
					
					// if the test point isn't in any of the currently 
					// existing bricks' rectangles 
					if( SDL_PointInRect( &testPoint, &existingRect ) ) 
					{
						// do not allow adding of a new brick 
						canAdd = false; 
						break; 
					}
					
				}
				if( canAdd ) 
				{
					this->add( gridLocations.at( i ).x + BRICK_WIDTH/2, 
							   gridLocations.at( i ).y + BRICK_HEIGHT/2 ); 
				}
			}
		}
	}
}

void BrickManager::saveBricks() 
{
	ofstream output; 
	
	// make the config file 
	output.open( "grid.cfg" ); 
	
	int brickIndex = 0; 
	
	cout << "saving grid locations" << endl; 
	for( int i = 0; i < bricks.size(); i++ ) 
	{
		output << "(" << bricks.at( i ).getBrickBox().x << "," << bricks.at( i ).getBrickBox().y << ")" << endl; 
	}
}

void BrickManager::loadDefaultBricks() 
{
	// go through the columns 
	for( int i = 0; i <= WINDOW_HEIGHT; i += BRICK_HEIGHT ) 
	{
		// go through the rows 
		for( int j = 0; j <= WINDOW_WIDTH; j += BRICK_WIDTH ) 
		{
			// add a brick at the point made by (j, i) 
			// add the brick width and height to j and i (respectively) 
			// to undo the offset (bricks are centered on their constructor params 
			this->add( j + BRICK_WIDTH/2, i + BRICK_HEIGHT/2 ); 
			
		}
		
	} 
	
}

void addBrickSet( string brickSpots )
{
	for( int i = 0; i < brickSpots.length(); i++ ) 
	{
		
	}
}

















