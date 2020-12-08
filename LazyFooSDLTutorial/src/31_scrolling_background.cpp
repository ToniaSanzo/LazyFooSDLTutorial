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
//// The player that will move around the screen
//class Player {
//public:
//    // The dimensions of the player
//    static const int PLAYER_WIDTH = 320;
//    static const int PLAYER_HEIGHT = 320;
//
//
//    // Maximum axis velocity of the player
//    static const int PLAYER_VEL = 2;
//
//    // Initializes the variables
//    Player();
//
//    // Takes key presses and adjusts the box velocity
//    void handleEvent(SDL_Event &e);
//
//    // Moves the player and checks collision
//    void move();
//
//    // Shows the player on the screen
//    void render(int frame = 0);
//
//    // Getters for the flies position
//    inline int getX() { return mX; }
//    inline int getY() { return mY; }
//    inline int getVelX() { return mVelX; }
//    inline int getVelY() { return mVelY; }
//
//private:
//    SDL_RendererFlip flip = SDL_FLIP_NONE;
//
//    // The X and Y offsets of the player
//    int mX, mY;
//
//    // The velocity of the player
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
//LTexture gPlayerTexture;
//LTexture gBackgroundTexture;
//SDL_Rect gPlayerClips[11];
//
//// Level & screen dimensions
//const int LEVEL_WIDTH = 6144;
//const int LEVEL_HEIGHT = 640;
//const int SCREEN_WIDTH = 840;
//const int SCREEN_HEIGHT = 640;
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
//Player::Player() {
//    // Initializes the offsets
//    mX = (SCREEN_WIDTH / 2 - PLAYER_WIDTH);
//    mY = (SCREEN_HEIGHT / 2 - PLAYER_HEIGHT);
//
//    // Initialize the velocity
//    mVelX = mVelY = 0;
//}
//
//void Player::handleEvent(SDL_Event &e) {
//    // If a key was pressed 
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
//        //Adjust the velocity and radians
//        switch (e.key.keysym.sym) {
//        case SDLK_UP:
//            mVelY -= PLAYER_VEL;
//            break;
//        case SDLK_DOWN:
//            mVelY += PLAYER_VEL;
//            break;
//        case SDLK_RIGHT:
//            mVelX += PLAYER_VEL;
//            break;
//        case SDLK_LEFT:
//            mVelX -= PLAYER_VEL;
//            break;
//        default:;   /* null */
//        }
//    }
//}
//
//void Player::move() {}
//
//void Player::render(int frame) {
//
//    // If the player is in motion show the player flying animation
//    if (mVelX || mVelY) { frame = (8 + (frame % 3)); }
//
//    // whether to flip the player based on the motion of the
//    // player
//    if (flip != SDL_FLIP_HORIZONTAL && mVelX < 0) { flip = SDL_FLIP_HORIZONTAL; }
//    if (flip != SDL_FLIP_NONE && mVelX > 0) { flip = SDL_FLIP_NONE; }
//
//    // Show the player
//    gPlayerTexture.render((mX), (mY), &gPlayerClips[frame], 0, NULL, flip);
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
//    // Load player texture
//    if (!gPlayerTexture.loadFromFile("assets/solarpunk_player.png")) {
//        printf("Failed to load player texture image!\n");
//        success = false;
//    }
//    else {
//        gPlayerTexture.updateScale(2);
//
//        const int IMG_TILE_WID = 320, IMG_TILE_HT = 320;
//        
//        // Initialize the idle animations
//        for (int i = 0; i < 8; ++i) {
//            gPlayerClips[i].x = i * IMG_TILE_WID;
//            gPlayerClips[i].y = 0;
//            gPlayerClips[i].w = IMG_TILE_WID;
//            gPlayerClips[i].h = IMG_TILE_HT;
//        }
//
//        // Initialize the movement animations
//        for (int i = 0; i < 3; ++i) {
//            gPlayerClips[8 + i].x = i * IMG_TILE_WID;
//            gPlayerClips[8 + i].y = IMG_TILE_HT;
//            gPlayerClips[8 + i].w = IMG_TILE_WID;
//            gPlayerClips[8 + i].h = IMG_TILE_HT;
//        }
//    }
//
//    // Load background texture
//    if (!gBackgroundTexture.loadFromFile("assets/solarpunk_background.png")) {
//        printf("Failed to load background texture image!\n");
//        success = false;
//    }
//    else {
//        gBackgroundTexture.updateScale(2);
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gPlayerTexture.free();
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
//            // The player that will be flying around the screen
//            Player player;
//            // The camera area
//            SDL_Rect camera = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
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
//                    player.handleEvent(e);
//                }
//
//                // Move the camera relative to the level
//                camera.x += player.getVelX();
//                camera.y += player.getVelY();
//
//                // Keep the camera in bounds
//                if (camera.x < 0) {
//                    camera.x += 4096;
//                }
//                if (camera.y < 0) {
//                    camera.y = 0;
//                }
//                if (camera.x > LEVEL_WIDTH - camera.w) {
//                    camera.x -= 4096;
//                }
//                if (camera.y > LEVEL_HEIGHT - camera.h) {
//                    camera.y = LEVEL_HEIGHT - camera.h;
//                }
//
//                // Update the frame
//                if (SDL_GetTicks() - time > 300) {
//                    ++frame;
//                    if (frame == 8) {
//                        frame = 0;
//                    }
//                    time = SDL_GetTicks();
//                }
//
//                // Clear screen, to white
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Render textures
//                gBackgroundTexture.render(0, 0, &camera);
//                player.render(frame);
//
//                // Update screen
//                SDL_RenderPresent(gRenderer);
//            }
//        }
//    }
//    //Free resources and close SDL
//    close();
//
//    return 0;
//}