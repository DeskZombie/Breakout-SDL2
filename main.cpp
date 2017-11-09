#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_ttf.h> 
#include <iostream> 
#include <vector> 
#include "../../LTimer.h" 
#include "Constants.h" 
#include "Paddle.h" 
#include "Brick.h" 
#include "Ball.h" 
#include "BrickManager.h" 
#include "Button.h" 

using namespace std; 

// sdl functions
bool init();
bool loadMedia();
void close();

// game functions
bool checkCollision( SDL_Rect, SDL_Rect );

// sdl variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// font for the game 
TTF_Font* fairfax; 

// game variables
LTimer frameTimer;

int main( int argc, char* args[] )
{
	bool running = false;
	if( init() && loadMedia() )
		running = true;
	
	SDL_Event e;
	
	
	Paddle paddle; 
	
	BrickManager bManager; 
	
	Ball ball( paddle ); 
	
	Button startButton( (WINDOW_WIDTH - BUTTON_WIDTH)/2, 
						(WINDOW_HEIGHT - BUTTON_HEIGHT)/2 ); 
	
	Button menuButton( WINDOW_WIDTH*9/10 - BUTTON_WIDTH/2, 
					   WINDOW_HEIGHT * 9/10 - BUTTON_WIDTH/2 ); 
	
	Button restartButton( WINDOW_WIDTH/10 - BUTTON_WIDTH/2, 
						  WINDOW_HEIGHT*9/10 - BUTTON_WIDTH/2 ); 
	
	// start the game in menu state 
	bool menuState = true; 
	
	// load whatever other textures n stuff 
	startButton.loadButtonTexture( renderer, "Play", fairfax ); 
	menuButton.loadButtonTexture( renderer, "Menu", fairfax ); 
	restartButton.loadButtonTexture( renderer, "Restart", fairfax ); 
	
	
	while( running )
	{
		// *********************** pre-iterative logic **********************
		frameTimer.start();
		
		// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		
		
		
		
		// ************************** app-works and logic ***********************
		if( SDL_PollEvent( &e ) != 0 )
		{
			// MOUSEMOTION was slowing down the game, so it is removed here 
			SDL_FlushEvent( SDL_MOUSEMOTION ); 
			
			// check for Alt+f4's or x-click's 
			if( e.type == SDL_QUIT )
			{
				running = false;
			}
			
			// perform basic game functions only if outside of menu state 
			if( !menuState ) 
			{
				// if freeze is -1, play in normal game mode 
				if( !bManager.isFrozen() )
				{
					paddle.control(); 
					ball.control( e ); 
				}
				bManager.control( e ); 
				
				// if the menu button is pressed 
				if( menuButton.control( e ) ) 
				{
					// switch to the menu 
					menuState = true; 
					
				}
			}
			// perform menu functions 
			else if( menuState ) 
			{
				// if the start button is clicked, start the game 
				if( startButton.control( e ) ) 
					menuState = false; 
			}
		}
		
		SDL_SetRenderDrawColor( renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a ); 
		SDL_RenderClear( renderer ); 
		
		// perform basic game functions only if outside of menu state 
		if( !menuState ) 
		{
			if( !bManager.isFrozen() ) 
			{
				paddle.update(); 
				ball.update( paddle, bManager ); 
				bManager.update(); 
			} 
			
			
			
			paddle.render( renderer  ); 
			bManager.render( renderer ); 
			ball.render( renderer ); 
			menuButton.render( renderer ); 
			
		} 
		// perform menu functions 
		else if( menuState ) 
		{
			startButton.render( renderer ); 
		}
		
		SDL_RenderPresent( renderer ); 
		
		// ************************ post-iterative logic *******************		
		Uint32 ticksOnThisFrame = frameTimer.getTicks();
		if( ticksOnThisFrame < TICKS_PER_FRAME )
		{
			SDL_Delay( TICKS_PER_FRAME - ticksOnThisFrame );
		}
		
		// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		
	}
	close();
	
	return 0;
}

bool init()
{
	bool success = false;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "sdl init failed" << endl;
	}
	else
	{
		window = SDL_CreateWindow( "breakout", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			cout << "window failed" << endl;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				cout << "renderer failed" << endl;
			}
			else
			{
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
				if( !IMG_Init( IMG_INIT_PNG ) ) 
				{
					cout << "IMG failed" << endl; 
				}
				else 
				{
					if( TTF_Init() == -1 ) 
					{
						cout << "TTF failed" << endl; 
					}
					else
					{
						success = true; 
					}
				}
			}
		}
	}

	srand( time( 0 ) ); 


	return success;
}

bool loadMedia()
{
	bool success = true;
	
	fairfax = TTF_OpenFont( "Fairfax.ttf", 36 ); 
	if( fairfax == NULL ) 
	{
		cout << "Fairfax font failed" << endl; 
		success = false; 
	}
	
	
	return success;
}

void close()
{
	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	SDL_DestroyWindow( window );
	window = NULL;
	
	TTF_Quit(); 
	IMG_Quit(); 
	SDL_Quit();
}

