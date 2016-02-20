#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                     SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//sends the user and password to the server
void LogIn();

//Checks if the button is clicked
bool buttonClicked(int Mx, int My, int x, int y, int w, int h);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;


//user and password for the login
std::string username;
std::string password;

const int usernameBox_X = 290;
const int usernameBox_Y = 205;

const int passwordBox_X = 290;
const int passwordBox_Y = 240;

//290 280 ... 360 300
const int login_X = 290;
const int login_Y = 280;
const int login_W = 70;
const int login_H = 20;

int writingX = usernameBox_X;
int writingY = usernameBox_Y;
bool writing = true;
bool passwordWriting = false;

//Scene textures
//LTexture gInputTextTexture;
LTexture usernameTexture;
LTexture passwordTexture;
LTexture backgroundTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		//printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Login", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "sans.ttf", 12 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render the prompt
		SDL_Color textColor = { 0, 0, 0, 0xFF };

	}

	return success;
}

void close()
{
	//Free loaded images
//	gInputTextTexture.free();
	backgroundTexture.free();
	usernameTexture.free();
	passwordTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool buttonClicked(int Mx, int My, int x, int y, int w, int h)
{
    if(Mx < x)
        return false;
    if(Mx > x + w)
        return false;
    if(My < y)
        return false;
    if(My > y + h)
        return false;

    return true;
}

void LogIn()
{
    std::cout << "Sending:\nUsername:  "<<username<<"\nPassword:  "<<password<<std::endl;

}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 0xFF };

			//The current input text.
			std::string inputText = "";
			//gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
			backgroundTexture.loadFromFile("loginBack.png");

			//Enable text input
			SDL_StartTextInput();

			//While application is running
			while( !quit )
			{
				//The rerender text flag
				bool renderText = false;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{

				    //mouse coordinates
				    int Mx;
				    int My;

				    SDL_GetMouseState(&Mx, &My);

				    //std::cout<< Mx <<" : "<<My<<std::endl;


					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Special key input
					else if( e.type == SDL_KEYDOWN )
					{
						//Handle backspace
						if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 && writing == true)
						{
							//lop off character

                            inputText.pop_back();
                            renderText = true;

                            if(passwordWriting && password.length() > 0)
                            {
                                password.pop_back();
                            }
						}
						else if( e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2  && writing == true)
                        {

                        }
                        else if(e.key.keysym.sym == SDLK_TAB)
                        {
                            if(passwordWriting)
                            {
                                passwordWriting = false;
                                inputText = username;
                            }
                            else if(!passwordWriting)
                            {
                                passwordWriting = true;
                                inputText = "";
                                for(int i = 0; i < password.length(); i++)
                                {
                                    inputText.push_back('*');
                                }
                            }
                        }
					}
					//Special text input event
					else if( e.type == SDL_TEXTINPUT && inputText.length() < 15  && writing == true)
					{
						//Not copy or pasting
						if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
						{
							if(!passwordWriting)
                            {
                                //Append character
                                inputText += e.text.text;
                                renderText = true;
                            }
                            else
                            {
                                password += e.text.text;
                                inputText += '*';
                                renderText = true;
                            }
						}
					}

					if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            if(buttonClicked(Mx, My, login_X, login_Y, login_W, login_H) == true)
                            {
                                LogIn();
                            }

                            if(buttonClicked(Mx, My, 285, 200, 135, 25))
                            {
                                passwordWriting = false;
                                inputText = username;
                            }

                            if(buttonClicked(Mx, My, 285, 240, 135, 25))
                            {
                                passwordWriting = true;
                                inputText = "";
                                for(int i = 0; i < password.length(); i++)
                                {
                                    inputText.push_back('*');
                                }
                            }
                        }
                    }


				}


                if(!passwordWriting)
                {
                    username = inputText;
                    //std::cout << username <<std::endl;
                    usernameTexture.loadFromRenderedText( username.c_str(), textColor );
                }
                else if (passwordWriting)
                {
                    //std::cout << password <<std::endl;
                    passwordTexture.loadFromRenderedText( inputText.c_str(), textColor);
                }



				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render text textures
                backgroundTexture.render(0, 0);
                if(username.length() > 0)
                    usernameTexture.render(usernameBox_X, usernameBox_Y);
                if(password.length() > 0)
                    passwordTexture.render(passwordBox_X, passwordBox_Y);
				//gInputTextTexture.render( writingX, writingY);


				//Update screen
				SDL_RenderPresent( gRenderer );
			}

			//Disable text input
			SDL_StopTextInput();
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
