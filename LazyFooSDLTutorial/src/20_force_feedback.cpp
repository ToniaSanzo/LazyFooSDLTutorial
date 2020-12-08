/*
* author: Tonia Sanzo
*
* Lesson 20: Force Feedback
*/
//#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <stdio.h>
//#include <time.h>
//#include <cmath>
//
//enum LButtonSprite {
//    BUTTON_SPRITE_MOUSE_OUT = 0,
//    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
//    BUTTON_SPRITE_MOUSE_DOWN = 2,
//    BUTTON_SPRITE_MOUSE_UP = 3,
//    BUTTON_SPRITE_TOTAL = 4
//};
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
//    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);
//
//    // Gets image dimensions
//    int getWidth();
//    int getHeight();
//    int getScale();
//
//    // Set image scale
//    void updateScale(int sc);
//private:
//    // The actual hardware texture
//    SDL_Texture *mTexture;
//
//    // Image dimensions
//    int mWidth;
//    int mHeight;
//    int scale;
//};
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Game Controller 1 handler with force
//// feedback
//SDL_Joystick *gGameController = NULL;
//SDL_Haptic *gControllerHaptic;
//
//// The sound effect that will be used
//Mix_Chunk *gThunder = NULL;
//
//// Texture
//LTexture gLightningTexture;
//SDL_Rect gSpriteClips[2];
//
//// Screen dimensions
//const int SCREEN_WIDTH = 426;
//const int SCREEN_HEIGHT = 640;
//
//// Analog joystick dead zone
//const int JOYSTICK_DEAD_ZONE = 8000;
//
//// LTexture constructor
//LTexture::LTexture() {
//    // Initialize
//    mTexture = NULL;
//    mWidth = 0;
//    mHeight = 0;
//    scale = 1;
//}
//
//// LTexture destructor
//LTexture::~LTexture() {
//    // Deallocate texture
//    free();
//}
//
//// Sets LTextures render scale
//void LTexture::updateScale(int sc) {
//    scale = sc;
//    mWidth *= sc;
//    mHeight *= sc;
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
//void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
//    // Set Rendering space and render to screen
//    SDL_Rect renderQuad = { x, y, mWidth * scale, mHeight * scale };
//
//    // Set clip rendering dimensions
//    if (clip != NULL) {
//        renderQuad.w = clip->w * scale;
//        renderQuad.h = clip->h * scale;
//    }
//
//    // Render to screen
//    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
//}
//
//// Getters for height, width, and scale
//int LTexture::getHeight() { return mHeight; }
//int LTexture::getWidth() { return mWidth; }
//int LTexture::getScale() { return scale; }
//
//// Initialize the SDL subsystems
//bool init()
//{
//    //Initialization flag
//    bool success = true;
//
//    //Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_AUDIO) < 0)
//    {
//        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//        success = false;
//    }
//    else
//    {
//        //Create window
//        gWindow = SDL_CreateWindow("Tonia Sanzo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
//                // Initialize SDL_mixer
//               if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//                    success = false;
//                }
//            }
//        }
//    }
//    return success;
//}
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Set texture filtering to linear
//    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
//    {
//        printf("Warning: Linear texture filtering not enabled!");
//    }
//
//    // Check for joysticks
//    if (SDL_NumJoysticks() < 1)
//    {
//        printf("Warning: No joysticks connected!\n");
//    }
//    else
//    {
//        //Load joystick
//        gGameController = SDL_JoystickOpen(0);
//        if (gGameController == NULL)
//        {
//            printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
//        }
//        else {
//            // Get controller haptic device
//            gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
//            if (gControllerHaptic == NULL) {
//                printf("Warning!: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
//            }
//            else {
//                // Get intialize rumble
//                if (SDL_HapticRumbleInit(gControllerHaptic) < 0) {
//                    printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
//                }
//            }
//        }
//    }
//
//    // Load textures
//    if (!gLightningTexture.loadFromFile("assets/lightning.png")) {
//        printf("Failed to load eagle texture!\n");
//        success = false;
//    }
//    else {
//        gSpriteClips[0].x = 0;
//        gSpriteClips[0].y = 0;
//        gSpriteClips[0].w = 426;
//        gSpriteClips[0].h = 640;
//
//        gSpriteClips[1].x = 426;
//        gSpriteClips[1].y = 0;
//        gSpriteClips[1].w = 426;
//        gSpriteClips[1].h = 640;
//    }
//
//    gThunder = Mix_LoadWAV("assets/lightning.wav");
//    if (!gThunder) {
//        printf("Failed to load thunder sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gLightningTexture.free();
//
//    // Free the sound effect
//    Mix_FreeChunk(gThunder);
//    gThunder = NULL;
//
//    // Close game controller with haptics
//    SDL_HapticClose(gControllerHaptic);
//    SDL_JoystickClose(gGameController);
//    gGameController = NULL;
//    gControllerHaptic = NULL;
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
//}
//
//
//int main(int argc, char *args[])
//{
//    // Start up SDL and create window
//    if (!init())
//    {
//        printf("Failed to initialize!\n");
//    }
//    else
//    {
//        // Load media
//        if (!loadMedia())
//        {
//            printf("Failed to load media!\n");
//        }
//        else
//        {
//            // Main loop flag
//            bool quit = false;
//
//            // Event handler
//            SDL_Event e;
//
//            // which image to play
//            int loopCycles = 0;
//
//
//            // While application is running
//            while (!quit)
//            {
//                // Handle events on queue
//                while (SDL_PollEvent(&e) != 0)
//                {
//                    // User requests quit
//                    if (e.type == SDL_QUIT)
//                    {
//                        quit = true;
//                    }
//                    else if (e.type == SDL_JOYBUTTONDOWN) {
//                        // Play rumble at 100% strength for 500 milliseconds
//                        if (SDL_HapticRumblePlay(gControllerHaptic, 1, 500) != 0) {
//                            printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
//                        }
//                        loopCycles = 1000;
//                        Mix_PlayChannel(-1, gThunder, 0);
//                    }
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0xEA, 0xEA, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                if (loopCycles != 0) {
//                    --loopCycles;
//                    gLightningTexture.render(0, 0, &gSpriteClips[0]);
//                }
//                else {
//                    gLightningTexture.render(0, 0, &gSpriteClips[1]);
//                }
//
//                // Update screen
//                SDL_RenderPresent(gRenderer);
//            }
//        }
//    }
//
//    //Free resources and close SDL
//
//    close();
//
//    return 0;
//}