#ifndef BRICKMANAGER_H 
#define BRICKMANAGER_H 

#include <SDL.h> 
#include <vector> 
#include <string> 
#include <fstream> 
#include "Brick.h" 

using namespace std; 


/* The brick manager is in charge of editing the game's brick config 
 * it has methods for adding/removing bricks, de/activating bricks, 
 * saving/loading brick configs via file IO, and there's which holds 
 * all bricks created by the brick manager 
 * 
 * Also, I'm using the words "blocks" and "bricks" interchangeably in 
 * this document 
 * 
 * I could see myself using BrickManager as a parent class for a 
 * tile editing system, which I'll get to that soon enough 
 */
class BrickManager 
{
	public: 
		// allocate memory for a bricks[] array (start as size 0) 
		BrickManager(); 
		
		// toggle for pausing ("freezing") the game 
		// right-click to add bricks to the grid 
		// left-click to remove bricks 
		// can't add bricks that would overlap existing bricks 
		void control( SDL_Event e ); 
		
		// does essentially nothing, but useful for testing memory issues 
		void update(); 
		
		// add brick to custom position (center-focused) 
		void add( int, int ); 
		
		// calls the block's destructor 
		void setActive( int, bool ); 
		
		// removes a block the blocks vector, given an index  
		void remove( int ); 
		
		// returns the size of the blocks vector 
		int getNumBricks(); 
		
		// allows status-checks for individual blocks in the blocks vector 
		Brick getBrick( int ) const; 
		
		// removes all blocks in the blocks vector 
		void reset(); 
		
		// renders all blocks (rectangles) in the blocks vector 
		void render( SDL_Renderer* ); 
		
		// getter for the "frozen" property 
		bool isFrozen() const; 
		
		// self explanatory 
		void toggleFreeze(); 
		
		// saves brick coordinates to a created file named grid.cfg 
		void saveBricks(); 
		
		// creates a few rows of bricks to break 
		void loadDefaultBricks(); 
		
	private: 
		// creates the points for the gridLocations vector 
		void setGridPoints(); 
		
		// adds a brick based on the grid points and mouse coordinates
		void addGridBrick( int, int ); 
		
		void addBrickSet( string ); 
		
		int frozen; 
		SDL_Event previousState; 
		vector< Brick > bricks; 
		vector< SDL_Point > gridLocations; 
		
}; 

#endif 
