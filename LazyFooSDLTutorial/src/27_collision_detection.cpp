/*
* author: Tonia Sanzo
*
* Lesson 27: Collision Detection
*/
//// Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <string>
//#include <sstream>
//#include <cmath>
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
//    // Creates image from font string
//    //bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
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
//// The box that will move around the screen
//class Box {
//public:
//    // The dimensions of the box
//    static const int BOX_WIDTH = 128;
//    static const int BOX_HEIGHT = 64;
//
//
//    // Maximum axis velocity of the box, and the rotation speed
//    // of the box in radians
//    static const int BOX_VEL = 10;
//    const double BOX_ROTATION = M_PI / 12.0;
//
//    // Initializes the variables
//    Box();
//
//    // Takes key presses and adjusts the box velocity
//    void handleEvent(SDL_Event &e);
//
//    // Moves the box
//    void move(SDL_Rect &wall);
//
//    // Shoes the box on the screen
//    void render(int frame);
//
//private:
//    SDL_Rect fish_frames[4];
//
//    // The X and Y offsets of the box
//    int mX, mY;
//
//    // The velocity of the box
//    int mVel;
//    double radians;
//
//    // Boxes collision box
//    SDL_Rect mCollider;
//};
//
//// The application time based timer
//class LTimer {
//public:
//    // Initializes variables
//    LTimer();
//
//    // The various clock actions
//    void start();
//    void stop();
//    void pause();
//    void unpause();
//
//    // Get's the timer's time
//    Uint32 getTicks();
//
//    // Checks the status of the timer
//    bool isStarted();
//    bool isPaused();
//
//private:
//    // The clock time when the timer started
//    Uint32 mStartTicks;
//
//    // The ticks stored when the timer was paused
//    Uint32 mPausedTicks;
//
//    // The timer status
//    bool mPaused;
//    bool mStarted;
//};
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Rendered texture
//LTexture gFishTexture;
//LTexture gPondTexture;
//
//// Screen dimensions
//const int SCREEN_WIDTH = 1220;
//const int SCREEN_HEIGHT = 900;
//
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
////// Load a font texture
////bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
////    // Get rid of preexisting texture
////    free();
////
////    // Render text surface
////    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
////    if (textSurface == NULL) {
////        printf("Unable to render text surface!  SDL_ttfError: %s\n", TTF_GetError());
////    }
////    else {
////        // Create texture from surface pixels
////        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
////        if (mTexture == NULL) {
////            printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
////        }
////        else {
////            // Get image dimensions
////            mWidth = textSurface->w;
////            mHeight = textSurface->h;
////        }
////
////        // Get rid of old surface
////        SDL_FreeSurface(textSurface);
////    }
////
////    // Return success
////    return mTexture != NULL;
////}
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
//    SDL_Rect renderQuad = { x , y, mWidth * scale, mHeight * scale };
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
//LTimer::LTimer() {
//    // Initialize the variables
//    mStartTicks = 0;
//    mPausedTicks = 0;
//
//    mPaused = false;
//    mStarted = false;
//}
//
//void LTimer::start() {
//    // Startthe timer
//    mStarted = true;
//
//    // Unpause the timer
//    mPaused = false;
//
//    // Get the current clock time
//    mStartTicks = SDL_GetTicks();
//    mPausedTicks = 0;
//}
//
//void LTimer::stop() {
//    // Stop the timer
//    mStarted = false;
//
//    // Unpause the timer
//    mPaused = false;
//
//    // Clear tick variables
//    mStartTicks = 0;
//    mPausedTicks = 0;
//}
//
//void LTimer::pause() {
//    // If the timer is running and isn't already paused
//    if (mStarted && !mPaused) {
//        mPaused = true;
//
//        // Calculate the paused ticks
//        mPausedTicks = SDL_GetTicks() - mStartTicks;
//        mStartTicks = 0;
//    }
//}
//
//void LTimer::unpause() {
//    // If the timer is running and paused
//    if (mStarted && mPaused) {
//        // Unpause the timer
//        mPaused = false;
//
//        // Reset the starting ticks
//        mStartTicks = SDL_GetTicks() - mPausedTicks;
//
//        // Reset the paused ticks
//        mPausedTicks = 0;
//    }
//}
//
//Uint32 LTimer::getTicks() {
//    // The actual timer time
//    Uint32 time = 0;
//
//    // If the timer is running
//    if (mStarted) {
//        // If the timer is paused
//        if (mPaused) {
//            time = mPausedTicks;
//        }
//        else {
//            // Returnthe current time minus the start time
//            time = SDL_GetTicks() - mStartTicks;
//        }
//    }
//
//    return time;
//}
//
//bool LTimer::isStarted() {
//    // Timer is running and paused or unpaused
//    return mStarted;
//}
//
//bool LTimer::isPaused() {
//    // Timer is running and paused
//    return mPaused && mStarted;
//}
//
//// Getters for height, width, and scale
//int LTexture::getHeight() { return mHeight; }
//int LTexture::getWidth() { return mWidth; }
//int LTexture::getScale() { return scale; }
//
//Box::Box() {
//    // Initializes the offsets
//    mX = mY = 0;
//
//    // Initialize the fishes frames
//    for (int i = 0; i < 4; ++i) {
//        fish_frames[i].x = i * BOX_WIDTH;
//        fish_frames[i].y = 0;
//        fish_frames[i].w = BOX_WIDTH;
//        fish_frames[i].h = BOX_HEIGHT;
//    }
//
//    // Initialize the box frames
//    mCollider.w = BOX_WIDTH;
//    mCollider.h = BOX_HEIGHT;
//
//    // Initialize the velocity and rotation
//    mVel = radians = 0;
//}
//
//void Box::handleEvent(SDL_Event &e) {
//    // If a key was pressed 
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
//        //Adjust the velocity and radians
//        switch (e.key.keysym.sym) {
//        case SDLK_UP:
//            mVel += BOX_VEL;
//            break;
//        case SDLK_DOWN:
//            mVel -= BOX_VEL / 2;
//            break;
//        case SDLK_RIGHT:
//            radians += BOX_ROTATION;
//            break;
//        case SDLK_LEFT:
//            radians -= BOX_ROTATION;
//            break;
//        default:;   /* null */
//        }
//    }
//
//    // make sure radians in the range 0 - 2pi
//    if (radians > 2 * M_PI)
//        radians -= 2 * M_PI;
//    else if (radians < 0)
//        radians += 2 * M_PI;
//}
//
//
//bool checkCollision(SDL_Rect a, SDL_Rect b){
//    // The sides of the rectangles
//    int leftA = a.x, leftB = b.x, rightA = a.x + a.w, rightB = b.x + b.w;
//    int topA = a.y, topB = b.y, botA = a.y + a.h, botB = b.y + b.h;
//
//    // If any of the sides are outside of B return false
//    if (botA <= topB || botB <= topA || rightA <= leftB || rightB <= leftA)
//        return false;
//
//    // If nont of the sides from A are outside B
//    return true;
//}
//
//void Box::move(SDL_Rect& wall) {
//    // Move the fish depending on the radians and velocity
//    mX += cos(radians) * static_cast<double>(mVel);
//    mCollider.x = mX;
//    mY += sin(radians) * static_cast<double>(mVel);
//    mCollider.y = mY;
//
//    // If the fish went to far in the x axis
//    if ((mX < 0) || (mX + BOX_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, wall)) {
//        // Move back
//        mX -= cos(radians) * static_cast<double>(mVel);
//        mCollider.x = mX;
//    }
//    // If the fish went to far in the y axis
//    if ((mY < 0) || (mY + BOX_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, wall)) {
//        mY -= sin(radians) * static_cast<double>(mVel);
//        mCollider.y = mY;
//    }
//}
//
//void Box::render(int frame) {
//    // Show the fish
//    gFishTexture.render(mX, mY, &fish_frames[frame], (radians * 180) / M_PI, NULL, SDL_FLIP_NONE);
//}
//
//// Initialize the SDL subsystems
//bool init()
//{
//    //Initialization flag
//    bool success = true;
//
//    //Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
//            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
//                // Initialize SDL_ttf
//                if (TTF_Init() == -1) {
//                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
//    // Load koi texture
//    if (!gFishTexture.loadFromFile("assets/koi_fish.png")) {
//        printf("Failed to load fish texture image!\n");
//        success = false;
//    }
//
//    // Load pond texture
//    if (!gPondTexture.loadFromFile("assets/pond_floor.png")) {
//        printf("Failed to load pond texture image!\n");
//        success = false;
//    }
//    else {
//        gPondTexture.updateScale(3);
//    }
//
//
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gFishTexture.free();
//    gPondTexture.free();
//
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    // Quit SDL subsystems
//    TTF_Quit();
//    IMG_Quit();
//    SDL_Quit();
//}
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
//            // Fish
//            Box box;
//
//            // The frames per second timer
//            LTimer fishframeTimer;
//
//            // Start counting frames per second
//            int currFrame = 0;
//            fishframeTimer.start();
//
//            // Set the wall
//            SDL_Rect wall;
//            wall.x = 300;
//            wall.y = 40;
//            wall.w = 40;
//            wall.h = 400;
//
//            // While application is running
//            while (!quit)
//            {
//                // Handle events on queue
//                while (SDL_PollEvent(&e) != 0) {
//                    // User requests quit
//                    if (e.type == SDL_QUIT) {
//                        quit = true;
//                    }
//
//                    // handle input for the fish
//                    box.handleEvent(e);
//                }
//
//                // move the fish
//                box.move(wall);
//
//                // upate the current fish frame every .9 second
//                if (fishframeTimer.getTicks() > 900) {
//                    ++currFrame;
//                    fishframeTimer.start();
//                    if (currFrame == 4)
//                        currFrame = 0;
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                //Render screen
//                gPondTexture.render(0, 0);
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
//                SDL_RenderDrawRect(gRenderer, &wall);
//                box.render(currFrame);
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