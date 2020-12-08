/*
* author: Tonia Sanzo
*
* Lesson 29: Circular Collision Detection
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
//// The dot that will move around the screen
//class Dot {
//public:
//    // The dimensions of the dot
//    static const int DOT_WIDTH = 20;
//    static const int DOT_HEIGHT = 20;
//
//
//    // Maximum axis velocity of the dot
//    static const int DOT_VEL = 1;
//
//    // Initializes the variables
//    Dot(int x, int y);
//
//    // Takes key presses and adjusts the box velocity
//    void handleEvent(SDL_Event &e);
//
//    // Moves the dot and checks collision
//    void move(SDL_Rect& square, Circle& circle);
//
//    // Shows the dot on the screen
//    void render();
//
//    // Gets collision circle
//    Circle &getCollider();
//
//private:
//    // The X and Y offsets of the dot
//    int mX, mY;
//
//    // The velocity of the dot
//    int mVelX, mVelY;
//
//    // Dot's collision circle
//    Circle mCollider;
//
//    // Moves the dot collider based on the current position
//    void shiftCollider();
//};
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Rendered texture
//LTexture gDotTexture;
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
//Dot::Dot(int x, int y) {
//    // Initializes the offsets
//    mX = x;
//    mY = y;
//
//    // Create the necessary SDL_Rects
//    mCollider.r = DOT_WIDTH / 2;
//
//    // Initialize the velocity
//    mVelX = mVelY = 0;
//
//    // Move collider relative to the circle
//    shiftCollider();
//}
//
//void Dot::handleEvent(SDL_Event &e) {
//    // If a key was pressed 
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
//        //Adjust the velocity and radians
//        switch (e.key.keysym.sym) {
//        case SDLK_UP:
//            mVelY -= DOT_VEL;
//            break;
//        case SDLK_DOWN:
//            mVelY += DOT_VEL;
//            break;
//        case SDLK_RIGHT:
//            mVelX += DOT_VEL;
//            break;
//        case SDLK_LEFT:
//            mVelX -= DOT_VEL;
//            break;
//        default:;   /* null */
//        }
//    }
//}
//// Calculates distance squared between two points
//double distanceSquared(int x1, int y1, int x2, int y2) {
//    int deltaX = x2 - x1;
//    int deltaY = y2 - y1;
//    return (deltaX * deltaX) + (deltaY * deltaY);
//}
//
//// Circle/circle collision detector
//bool checkCollision(Circle &a, Circle &b) {
//    // Calculate total radius squared
//    int totalRadiusSquared = a.r + b.r;
//    totalRadiusSquared *= totalRadiusSquared;
//
//    // If the distance b/w the centers of the circles is less than the sum of their 
//    // radii
//    if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) {
//        // The circles have collided
//        return true;
//    }
//
//    // The circles did not collide
//    return false;
//}
//
//// Circle/Box collision detector
//bool checkCollision(Circle &a, SDL_Rect &b) {
//    // Closest point on collision box
//    int cX, cY;
//    
//    // Find closest x offset
//    if (a.x < b.x) {
//        cX = b.x;
//    }
//    else if (a.x > b.x + b.w) {
//        cX = b.x + b.w;
//    }
//    else {
//        cX = a.x;
//    }
//
//    // Find closest y offset
//    if (a.y < b.y) {
//        cY = b.y;
//    }
//    else if (a.y > b.y + b.h) {
//        cX = b.x + b.h;
//    }
//    else {
//        cY = a.y;
//    }
//
//    // If the closest point is inside the circle
//    if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
//        // This box and the circle have collided
//        return true;
//    }
//
//    // If the shapes have
//    return false;
//}
//
//void Dot::move(SDL_Rect& square, Circle& circle) {
//    // Move the dot left or right
//    mX += mVelX;
//    mY += mVelY;
//    shiftCollider();
//
//    // If the dot went to far in the x axis
//    if ((mX < 0) || (mX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, square) || checkCollision(mCollider, circle)) {
//        // Move back
//        mX -= mVelX;
//        shiftCollider();
//    }
//
//    // If the fish went to far in the y axis
//    if ((mY < 0) || (mY + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, square) || checkCollision(mCollider, circle)) {
//        mY -= mVelY;
//        shiftCollider();
//    }
//}
//
//Circle &Dot::getCollider() {
//    return mCollider;
//}
//
//void Dot::shiftCollider() {
//    mCollider.x = mX;
//    mCollider.y = mY;
//}
//
//void Dot::render() {
//    // Show the dot
//    gDotTexture.render((mX - mCollider.r), (mY - mCollider.r));
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
//    // Load dot texture
//    if (!gDotTexture.loadFromFile("assets/dot.png")) {
//        printf("Failed to load dot texture image!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gDotTexture.free();
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
//            // The dot we will move
//            Dot dot(10, 10);
//
//            // The dot that will be collided against
//            Dot otherDot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
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
//                    dot.handleEvent(e);
//                }
//
//                // move the fish
//                dot.move(wall, otherDot.getCollider());
//
//                // Clear screen, to white
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
//                SDL_RenderDrawRect(gRenderer, &wall);
//
//                //Render screen
//                dot.render();
//                otherDot.render();
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