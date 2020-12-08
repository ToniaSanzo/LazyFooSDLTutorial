/*
* author: Tonia Sanzo
*
* Lesson 19: Gamepads and Joysticks
*/
//#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
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
//SDL_Joystick *gGameController = NULL;
//
//// Textures
//LTexture gEagleTexture;
//
//// Screen dimensions
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
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
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
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
//
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
//    }
//
//    // Load textures
//    if (!gEagleTexture.loadFromFile("assets/eagle.png")) {
//        printf("Failed to load eagle texture!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gEagleTexture.free();
//
//    // Close game controller
//    SDL_JoystickClose(gGameController);
//    gGameController = NULL;
//
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    // Quit SDL subsystems
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
//            // Normalized direction
//            int xDir = 0, yDir = 0;
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
//                    else if (e.type == SDL_JOYAXISMOTION) {
//                        // Motion on controller 0
//                        if (e.jaxis.which == 0) {
//                            // X axis motion
//                            if (e.jaxis.axis == 0) {
//                                // Left of dead zone
//                                if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
//                                    xDir = -1;
//                                }
//                                // Right of dead zone
//                                else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
//                                    xDir = 1;
//                                }
//                                else {
//                                    xDir = 0;
//                                }
//
//                            }
//                            // Y axis motion
//                            else if (e.jaxis.axis == 1) {
//                                // Below dead zone
//                                if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
//                                    yDir = -1;
//                                }
//                                // Above dead zone
//                                else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
//                                    yDir = 1;
//                                }
//                                else {
//                                    yDir = 0;
//                                }
//                            }
//                        }
//                    }
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0xEA, 0xEA, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Calculate angle
//                double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);
//                
//
//                // Correct angle
//                if (xDir == 0 && yDir == 0) {
//                    joystickAngle = 0;
//                }
//
//                // Render joystick
//                gEagleTexture.render((SCREEN_WIDTH - gEagleTexture.getWidth()) / 2, (SCREEN_HEIGHT - gEagleTexture.getHeight()) / 2, NULL, joystickAngle);
//
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