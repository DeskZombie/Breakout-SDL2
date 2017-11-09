#include "Button.h" 
#include "Constants.h" 

// should find a way to inherit this from a base class because 
// BrickManager uses the same function 
Button::Button( int x, int y, string buttonText, TTF_Font* font ) 
{
	buttonBox = { x, y, BUTTON_WIDTH, BUTTON_HEIGHT }; 
	
	active = true; 
}

void Button::loadButtonTexture( SDL_Renderer* renderer, string text, TTF_Font* font ) 
{
	// try to load the text 
	// if the string isn't empty and the font isn't null 
	if( text != "" && font != NULL )
	{
		SDL_Color black = { 0, 0, 0, 255 }; 
		buttonText = text; 
		// load the font through the buttonTexture 
		buttonTexture.loadFromRenderedText( renderer, text, black, font ); 
		
	}
}

bool Button::control( SDL_Event e )
{
	// check if the button's active before checking input 
	if( !active ) 
		return false; 
	bool buttonWasClicked = false; 
	if( e.type == SDL_MOUSEBUTTONDOWN ) 
	{
		SDL_Point mousePos; 
		SDL_GetMouseState( &mousePos.x, &mousePos.y ); 
		
		if( SDL_PointInRect( &mousePos, &buttonBox ) ) 
		{
			buttonWasClicked = true; 
		}
		else 
			buttonWasClicked = false; 
	}
	else
		buttonWasClicked = false; 
	return buttonWasClicked; 
}

void Button::render( SDL_Renderer* renderer ) 
{
	// as with control(), first check if the button is active 
	if( !active ) 
		return; 
	SDL_SetRenderDrawColor( renderer, 30, 150, 10, 255 ); 
	SDL_RenderFillRect( renderer, &buttonBox ); 
	buttonTexture.render( buttonBox.x + buttonBox.w/2 - buttonTexture.getWidth()/2, 
						  buttonBox.y + buttonTexture.getHeight()/2, renderer ); 
}

void Button::setActive( bool isActive ) 
{
	active = isActive; 
} 



