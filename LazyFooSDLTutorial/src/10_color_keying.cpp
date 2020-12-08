/*
* author: Tonia Sanzo
*
* Lesson 10: Color Keying
*/
//#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer * gRenderer = NULL;
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
//    // Renders texture at given point
//    void render(int x, int y);
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
//    mWidth   = 0;
//    mHeight  = 0;
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
//// Render texture
//void LTexture::render(int x, int y) {
//    // Set Rendering space and render to screen
//    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
//}
//
//// Scene textures
//LTexture gKayakTexture;
//LTexture gBackgroundTexture;
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Load kayak texture
//    if (!gKayakTexture.loadFromFile("assets/kayak.png")) {
//        printf("Failed to load kayak texture image!\n");
//        success = false;
//    }
//
//    // Load background texture
//    if (!gBackgroundTexture.loadFromFile("assets/background.png")) {
//        printf("Failed to load background texture image!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gKayakTexture.free();
//    gBackgroundTexture.free();
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
//            }
//        }
//    }
//
//    return success;
//}
//
//int main(int argc, char *args[])
//{
//    // Used to move the kayak around slightly
//    unsigned int loopCnt = 0;
//    int kX = 85, kY = 370;
//
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
//            //While application is running
//            while (!quit)
//            {
//                //Handle events on queue
//                while (SDL_PollEvent(&e) != 0)
//                {
//                    //User requests quit
//                    if (e.type == SDL_QUIT)
//                    {
//                        quit = true;
//                    }
//                }
//
//                // Clear screen
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Render background to screen
//                gBackgroundTexture.render(0, 0);
//
//                if (loopCnt % 5000 == 0) {
//                    kY += 4;
//                }
//
//                if (loopCnt % 4800 == 0) {
//                    kX += 4;
//                }
//
//                if (loopCnt % 10000 == 0) {
//                    kY -= 8;
//                }
//
//                if (loopCnt % 9600 == 0) {
//                    kX -= 8;
//                }
//
//                // Render kayak to screen
//                gKayakTexture.render(kX, kY);
//
//                ++loopCnt;
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