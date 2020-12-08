/*
* author: Tonia Sanzo
*
* Lesson 30: Scrolling
*/
//// Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <string>
//#include <sstream>
//#include <cmath>
//#include <vector>
//
//// A circle structure
//struct Circle {
//    int x, y;
//    int r;
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
//    void updateScale(double sc);
//private:
//    // The actual hardware texture
//    SDL_Texture *mTexture;
//
//    // Image dimensions
//    int mWidth;
//    int mHeight;
//    double scale;
//};
//
//// The fly that will move around the screen
//class Fly {
//public:
//    // The dimensions of the fly
//    static const int FLY_WIDTH = 117;
//    static const int FLY_HEIGHT = 66;
//
//
//    // Maximum axis velocity of the fly
//    static const int FLY_VEL = 10;
//
//    // Initializes the variables
//    Fly();
//
//    // Takes key presses and adjusts the box velocity
//    void handleEvent(SDL_Event &e);
//
//    // Moves the fly and checks collision
//    void move();
//
//    // Shows the fly on the screen
//    void render(int camX, int camY, int frame = 0);
//
//    // Getters for the flies position
//    inline int getX() { return mX; }
//    inline int getY() { return mY; }
//
//private:
//    SDL_RendererFlip flip = SDL_FLIP_NONE;
//
//    // The X and Y offsets of the fly
//    int mX, mY;
//
//    // The velocity of the fly
//    int mVelX, mVelY;
//};
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Rendered texture
//LTexture gFlyTexture;
//LTexture gBackgroundTexture;
//SDL_Rect gFlyClips[12];
//
//// Level & screen dimensions
//const int LEVEL_WIDTH   = 2736;
//const int LEVEL_HEIGHT  = 1572;
//const int SCREEN_WIDTH  = 640;
//const int SCREEN_HEIGHT = 480;
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
//void LTexture::updateScale(double sc) {
//    scale = sc;
//    mWidth *= sc;
//    mHeight *= sc;
//}
//
//// Load Texture from a file
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
//// Getters for height, width, and scale
//int LTexture::getHeight() { return mHeight; }
//int LTexture::getWidth() { return mWidth; }
//int LTexture::getScale() { return scale; }
//
//Fly::Fly() {
//    // Initializes the offsets
//    mX = (SCREEN_WIDTH / 2 - FLY_WIDTH / 2);
//    mY = (SCREEN_HEIGHT / 2 - FLY_HEIGHT / 2);
//
//
//    // Initialize the velocity
//    mVelX = mVelY = 0;
//}
//
//void Fly::handleEvent(SDL_Event &e) {
//    // If a key was pressed 
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
//        //Adjust the velocity and radians
//        switch (e.key.keysym.sym) {
//        case SDLK_UP:
//            mVelY -= FLY_VEL;
//            break;
//        case SDLK_DOWN:
//            mVelY += FLY_VEL;
//            break;
//        case SDLK_RIGHT:
//            mVelX += FLY_VEL;
//            break;
//        case SDLK_LEFT:
//            mVelX -= FLY_VEL;
//            break;
//        default:;   /* null */
//        }
//    }
//}
//
//void Fly::move() {
//    // Move the fly left or right
//    mX += mVelX;
//    mY += mVelY;
//
//    // If the fly went to far in the x axis
//    if ((mX < 0) || (mX + FLY_WIDTH > LEVEL_WIDTH)) {
//        // Move back
//        mX -= mVelX;
//    }
//
//    // If the fish went to far in the y axis
//    if ((mY < 0) || (mY + FLY_HEIGHT > LEVEL_HEIGHT)) {
//        // Move back
//        mY -= mVelY;
//    }
//}
//
//void Fly::render(int camX, int camY, int frame) {
//
//    // If the fly is in motion show the fly flying animation
//    if (mVelX || mVelY) { frame += 6; }
//
//    // whether to flip the fly based on the motion of the fly
//    if (flip != SDL_FLIP_HORIZONTAL && mVelX < 0) { flip = SDL_FLIP_HORIZONTAL; }
//    if (flip != SDL_FLIP_NONE && mVelX > 0) { flip = SDL_FLIP_NONE; }
//
//
//    // Show the fly
//    gFlyTexture.render((mX - camX), (mY - camY), &gFlyClips[frame], 0, NULL, flip);
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
//    // Load fly texture
//    if (!gFlyTexture.loadFromFile("assets/fly.png")) {
//        printf("Failed to load fly texture image!\n");
//        success = false;
//    }
//    else {
//        gFlyTexture.updateScale(.85);
//
//        const size_t ROWS = 2, COLS = 6;
//        const int IMG_TILE_WID = 139, IMG_TILE_HT = 78;
//
//        // Set the gFlyTexture animation clips
//        for (size_t row = 0; row < ROWS; ++row) {
//            for (size_t col = 0; col < COLS; ++col) {
//                gFlyClips[(row * COLS) + col].x = col * IMG_TILE_WID;
//                gFlyClips[(row * COLS) + col].y = row * IMG_TILE_HT;
//                gFlyClips[(row * COLS) + col].w = IMG_TILE_WID;
//                gFlyClips[(row * COLS) + col].h = IMG_TILE_HT;
//            }
//        }
//
//    }
//
//    // Load background texture
//    if (!gBackgroundTexture.loadFromFile("assets/thanksgiving_dinner.png")) {
//        printf("Failed to load background texture image!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gFlyTexture.free();
//    gBackgroundTexture.free();
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
//            size_t frame = 0;
//
//            // The fly that will be flying around the screen
//            Fly fly;
//            // The camera area
//            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
//
//            // Event handler
//            SDL_Event e;
//            Uint32 time = SDL_GetTicks();
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
//                    // Handle user events
//                    fly.handleEvent(e);
//                }
//
//                if (SDL_GetTicks() - time > 70) {
//                    ++frame;
//                    if (frame == 6) {
//                        frame = 0;
//                    }
//                    time = SDL_GetTicks();
//                }
//
//                // Move the fly
//                fly.move();
//
//                // Center the camera over the fly
//                camera.x = (fly.getX() + Fly::FLY_WIDTH / 2) - SCREEN_WIDTH / 2;
//                camera.y = (fly.getY() + Fly::FLY_HEIGHT / 2) - SCREEN_HEIGHT / 2;
//                // Keep the camera in bounds
//                if (camera.x < 0) {
//                    camera.x = 0;
//                }
//                if (camera.y < 0) {
//                    camera.y = 0;
//                }
//                if (camera.x > LEVEL_WIDTH - camera.w) {
//                    camera.x = LEVEL_WIDTH - camera.w;
//                }
//                if (camera.y > LEVEL_HEIGHT - camera.h) {
//                    camera.y = LEVEL_HEIGHT - camera.h;
//                }
//
//
//                // Clear screen, to white
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
// 
//                // Render textures
//                gBackgroundTexture.render(0, 0, &camera);
//                fly.render(camera.x, camera.y, frame);
//
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