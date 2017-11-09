#ifndef BUTTON_H 
#define BUTTON_H 

#include <SDL.h> 
#include <SDL_ttf.h> 
#include <vector> 
#include <iostream> 
#include <string> 
#include "../../LTexture.h" 

using namespace std; 

class Button 
{
	public: 
		// create a button at position (x, y)
		Button( int, int, string buttonText = "", TTF_Font* font = NULL ); 
		
		// load the button text 
		void loadButtonTexture( SDL_Renderer*, string text = "", TTF_Font* font = NULL ); 
		
		// if the button was pressed, return true, else return false 
		bool control( SDL_Event ); 
		
		void render( SDL_Renderer* ); 
		
		void setActive( bool ); 
		
	private: 
		bool active; 
		SDL_Rect buttonBox; 
		string buttonText; 
		LTexture buttonTexture; 
		
}; 

#endif 
