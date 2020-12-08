/*
* author: Tonia Sanzo
*
* Lesson 21: Sound Effects and Music
*/
//// Using SDL, SDL_image, SDL_mixer, stardard IO, and strings
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <stdio.h>
//#include <string>
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// The music that wil lbe played
//Mix_Music *gMusic = NULL;
//
//// The sound effects that will be used
//Mix_Chunk *gScratch = NULL;
//Mix_Chunk *gHigh = NULL;
//Mix_Chunk *gMedium = NULL;
//Mix_Chunk *gLow = NULL;
//
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// Texture wrapper class
//class LTexture {
//public:
//    // Initialize variables
//    LTexture();
//
//    // Deallocates memory
//    ~LTexture();
//
//    // Loads image at specified path
//    bool loadFromFile(std::string path);
//
//    // Deallocates texture
//    void free();
//
//    // Set color modulation
//    void setColor(Uint8 red, Uint8 green, Uint8 blue);
//
//    // Set blending
//    void setBlendMode(SDL_BlendMode blending);
//
//    // Set alpha modulation
//    void setAlpha(Uint8 alpha);
//
//    // Renders texture at given point
//    void render(int x, int y, SDL_Rect *clip = NULL);
//
//    // Gets image dimensions
//    int getWidth();
//    int getHeight();
//
//private:
//    // The actual hardware texture
//    SDL_Texture *mTexture;
//
//    // Image dimensions
//    int mWidth;
//    int mHeight;
//};
//
//// LTexture constructor
//LTexture::LTexture() {
//    // Initialize
//    mTexture = NULL;
//    mWidth = 0;
//    mHeight = 0;
//}
//
//// LTexture destructor
//LTexture::~LTexture() {
//    // Deallocate texture
//    free();
//}
//
//// Load LTexture from a file
//bool LTexture::loadFromFile(std::string path) {
//    // Get rid of preexisting texture
//    free();
//
//    // The final texture
//    SDL_Texture *newTexture = NULL;
//
//    // Load image at specified path
//    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
//    if (!loadedSurface) {
//        printf("unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//    }
//    else {
//        // Color key image
//        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//        // Create texture from surface pixels
//        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//        if (!newTexture) {
//            printf("Unable to create texture from %s! SDL Error: %s\n:", path.c_str(), SDL_GetError());
//        }
//        else {
//            // Get image dimensions
//            mWidth = loadedSurface->w;
//            mHeight = loadedSurface->h;
//        }
//
//        // Get rid of old loaded surface
//        SDL_FreeSurface(loadedSurface);
//    }
//
//    // Return success
//    mTexture = newTexture;
//    return mTexture != NULL;
//}
//
//// Deallocate the texture
//void LTexture::free() {
//    // Free texture if it exists
//    if (mTexture) {
//        SDL_DestroyTexture(mTexture);
//        mTexture = NULL;
//        mWidth = 0;
//        mHeight = 0;
//    }
//}
//
//// Define whether this texture can blend
//void LTexture::setBlendMode(SDL_BlendMode blending) {
//    // Set blending function
//    SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//// Define the texture's opacity
//void LTexture::setAlpha(Uint8 alpha) {
//    // Modulate texture alpha
//    SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//// Modulate the texture's color
//void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
//    // Modulate texture
//    SDL_SetTextureColorMod(mTexture, red, green, blue);
//}
//
//// Render texture
//void LTexture::render(int x, int y, SDL_Rect *clip) {
//    // Set Rendering space and render to screen
//    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//    // Set clip rendering dimensions
//    if (clip != NULL) {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }
//
//    // Render to screen
//    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
//}
//
//// Getters for height and width
//int LTexture::getHeight() { return mHeight; }
//int LTexture::getWidth() { return mWidth; }
//
//LTexture gPromptTexture;
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Load prompt texture
//    if (!gPromptTexture.loadFromFile("assets/prompt.png")) {
//        printf("Failed to load prompt texture!\n");
//        success = false;
//    }
//
//    // Load music
//    gMusic = Mix_LoadMUS("assets/lfk.wav");
//    if (gMusic == NULL) {
//        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
//        success = true;
//    }
//
//    // Load sound effects
//    gScratch = Mix_LoadWAV("assets/scratch.wav");
//    if (gScratch == NULL)
//    {
//        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//        success = false;
//    }
//
//    gHigh = Mix_LoadWAV("assets/high.wav");
//    if (gHigh == NULL)
//    {
//        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//        success = false;
//    }
//
//    gMedium = Mix_LoadWAV("assets/medium.wav");
//    if (gMedium == NULL)
//    {
//        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//        success = false;
//    }
//
//    gLow = Mix_LoadWAV("assets/low.wav");
//    if (gLow == NULL)
//    {
//        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gPromptTexture.free();
//
//    //Free the sound effects
//    Mix_FreeChunk(gScratch);
//    Mix_FreeChunk(gHigh);
//    Mix_FreeChunk(gMedium);
//    Mix_FreeChunk(gLow);
//    gScratch = NULL;
//    gHigh = NULL;
//    gMedium = NULL;
//    gLow = NULL;
//
//    //Free the music
//    Mix_FreeMusic(gMusic);
//    gMusic = NULL;
//
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    // Quit SDL subsystems
//    Mix_Quit();
//    IMG_Quit();
//    SDL_Quit();
//
//}
//
//bool init()
//{
//    //Initialization flag
//    bool success = true;
//
//    //Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
//    {
//        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//        success = false;
//    }
//    else
//    {
//        //Create window
//        gWindow = SDL_CreateWindow("Tonia Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//        if (gWindow == NULL)
//        {
//            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//            success = false;
//        }
//        else
//        {
//            // Create renderer for the window
//            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
//            if (gRenderer == NULL) {
//                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
//                success = false;
//            }
//            else {
//                // Initialize renderer color
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//
//                // Initialize PNG loading
//                int imgFlags = IMG_INIT_PNG;
//                if (!(IMG_Init(imgFlags) & imgFlags)) {
//                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
//                    success = false;
//                }
//
                //// Initialize SDL_mixer
                //// 44100 - The sound frequency and this number is the standard frequency on most systems.
                //// MIX_DEFAULT_FORMAT - determines the sample format, this is the default option
                //// 2 - We are using 2 channels for stereo
                //// 2048 - this is the sample size, the size of the chunks we use when playing sound
                //if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                //    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                //    success = false;
                //}
//            }
//        }
//    }
//
//    return success;
//}
//
//int main(int argc, char *args[])
//{
//    //Start up SDL and create window
//    if (!init())
//    {
//        printf("Failed to initialize!\n");
//    }
//    else
//    {
//        //Load media
//        if (!loadMedia())
//        {
//            printf("Failed to load media!\n");
//        }
//        else
//        {
//            //Main loop flag
//            bool quit = false;
//
//            //Event handler
//            SDL_Event e;
//
//            // Modulation components
//            Uint8 a = 255;
//            Uint32 currTime, prevTime = SDL_GetTicks();
//            bool incOpac = false;
//
//            //While application is running
//            while (!quit)
//            {
//                currTime = SDL_GetTicks();
//                printf("%i : %i\n", currTime, prevTime);
//
//                // update opacity every 500 milliseconds
//                if ((currTime - prevTime) >= 10) {
//                    if (incOpac) {
//                        ++a;
//                        if (a == 255) incOpac = false;
//                    }
//                    else {
//                        --a;
//                        if (a == 0) incOpac = true;
//                    }
//                    prevTime = currTime;
//                }
//
//
//
//
//                //Handle events on queue
//                while (SDL_PollEvent(&e) != 0)
//                {
//                    //User requests quit
//                    if (e.type == SDL_QUIT)
//                    {
//                        quit = true;
//                    }
//                    // On keypress change rgb values
//                    else if (e.type == SDL_KEYDOWN) {
//                        switch (e.key.keysym.sym) {
//                        // Play high sound effect
//                        case SDLK_1:
//                            Mix_PlayChannel(-1, gHigh, 0);
//                            break;
//                        // Play medium sound effect
//                        case SDLK_2:
//                            Mix_PlayChannel(-1, gMedium, 0);
//                            break;
//                        // Play low sound effect
//                        case SDLK_3:
//                            Mix_PlayChannel(-1, gLow, 0);
//                            break;
//                        // Play scratchh sound effect
//                        case SDLK_4:
//                            Mix_PlayChannel(-1, gScratch, 0);
//                            break;
//                        case SDLK_9:
//                            // If there is no music playing
//                            if (Mix_PlayingMusic() == 0) {
//                                // Play the music
//                                Mix_PlayMusic(gMusic, -1);
//                            }
//                            // If music is being played
//                            else {
//                                // If the music is paused
//                                if (Mix_PausedMusic() == 1) {
//                                    // Resume the music
//                                    Mix_ResumeMusic();
//                                }
//                                // If the music is playing
//                                else {
//                                    // Pause the music
//                                    Mix_PauseMusic();
//                                }
//                            }
//                            break;
//                        case SDLK_0:
//                            // Stop the music
//                            Mix_HaltMusic();
//                            break;
//                        default:; // null statement  
//                        }
//                    }
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
//                SDL_RenderClear(gRenderer);
//
//                // Render background
//                gPromptTexture.render(0, 0);
//
//                // Update screen
//                SDL_RenderPresent(gRenderer);
//            }
//        }
//    }
//
//    //Free resources and close SDL
//    close();
//
//    return 0;
//}