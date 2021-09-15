#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( string path );

//The window we'll be rendering to
SDL_Window* win = NULL;
	
//The surface contained by the window
SDL_Surface* scrSurf = NULL;

//The images that correspond to a keypress
SDL_Surface* keyPressSurf[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* currentSurf = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error: " << "\n" << SDL_GetError() ;
		success = false;
	}
	else
	{
		//Create window
		win = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( win == NULL )
		{
			cout << "Window could not be created! SDL Error: "<< "\n" << SDL_GetError() ;
			success = false;
		}
		else
		{
			//Get window surface
			scrSurf = SDL_GetWindowSurface( win );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	keyPressSurf[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "C:\\Users\\ericw\\Desktop\\game2_sdl\\res\\press.bmp" );
	if( keyPressSurf[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		cout << "Failed to load default image!" << "\n" ;
		success = false;
	}

	//Load up surface
	keyPressSurf[ KEY_PRESS_SURFACE_UP ] = loadSurface( "C:\\Users\\ericw\\Desktop\\game2_sdl\\res\\up.bmp" );
	if( keyPressSurf[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		cout << "Failed to load up image!" << "\n" ;
		success = false;
	}

	//Load down surface
	keyPressSurf[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "C:\\Users\\ericw\\Desktop\\game2_sdl\\res\\down.bmp" );
	if( keyPressSurf[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		cout << "Failed to load down image!" << "\n" ;
		success = false;
	}

	//Load left surface
	keyPressSurf[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "C:\\Users\\ericw\\Desktop\\game2_sdl\\res\\left.bmp" );
	if( keyPressSurf[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		cout << "Failed to load left image!" << "\n" ;
		success = false;
	}

	//Load right surface
	keyPressSurf[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "C:\\Users\\ericw\\Desktop\\game2_sdl\\res\\right.bmp" );
	if( keyPressSurf[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		cout << "Failed to load right image!" << "\n" ;
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( keyPressSurf[ i ] );
		keyPressSurf[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( win );
	win = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface( string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		cout << "Unable to load image" << "! SDL Error: " << "\n" << path.c_str() << SDL_GetError() ;
	}

	return loadedSurface;
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize!" << "\n" ;
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!" << "\n" ;
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							currentSurf = keyPressSurf[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

				SDL_BlitSurface( currentSurf, NULL, scrSurf, NULL );
							
				SDL_UpdateWindowSurface( win );
			}
		}
	}

	close();

	return 0;
}