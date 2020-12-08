/*
* author: Tonia Sanzo
*
* Lesson 13: Alpha Blending
*/
//#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <time.h>
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
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
//LTexture gEyeTexture;
//LTexture gAppleTexture;
//SDL_Rect gSpriteClips[2];
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Load apple texture
//    if (!gAppleTexture.loadFromFile("assets/eye_apple.png")) {
//        printf("Failed to load apple texture image!\n");
//        success = false;
//    }
//    else {
//        // Set standard alpha blending, and the apple rectangle
//        gAppleTexture.setBlendMode(SDL_BLENDMODE_BLEND);
//        gSpriteClips[1].x = 640;
//        gSpriteClips[1].y = 0;
//        gSpriteClips[1].w = 640;
//        gSpriteClips[1].h = 480;
//
//    }
//
//    // Load eye texture
//    if (!gEyeTexture.loadFromFile("assets/eye_apple.png")) {
//        printf("Failed to load apple texture image!\n");
//        success = false;
//    }
//    else {
//        // Set the eye rectangle
//        gSpriteClips[0].x = gSpriteClips[0].y = 0;
//        gSpriteClips[0].w = 640;
//        gSpriteClips[0].h = 480;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gEyeTexture.free();
//    gAppleTexture.free();
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
//                        // Increase opacity
//                        case SDLK_w:
//                            a += 32;
//                            break;
//                        // Decrease opacity
//                        case SDLK_s:
//                            a -= 32;
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
//                gEyeTexture.render(0, 0, &gSpriteClips[0]);
//
//                // Modulate and render foreground
//                gAppleTexture.setAlpha(a);
//                gAppleTexture.render(0, 0, &gSpriteClips[1]);
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