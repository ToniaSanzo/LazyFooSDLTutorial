/*
* author: Tonia Sanzo
*
* Lesson 22: Timing
*/
//// Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <string>
//#include <sstream>
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
//    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
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
//// Globally used font
//TTF_Font *gFont = NULL;
//
//// Rendered texture
//LTexture gPromptTextTexture;
//LTexture gPrimaryTextTexture;
//
//// Screen dimensions
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
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
//// Load a font texture
//bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
//    // Get rid of preexisting texture
//    free();
//
//    // Render text surface
//    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//    if (textSurface == NULL) {
//        printf("Unable to render text surface!  SDL_ttfError: %s\n", TTF_GetError());
//    }
//    else {
//        // Create texture from surface pixels
//        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//        if (mTexture == NULL) {
//            printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
//        }
//        else {
//            // Get image dimensions
//            mWidth = textSurface->w;
//            mHeight = textSurface->h;
//        }
//
//        // Get rid of old surface
//        SDL_FreeSurface(textSurface);
//    }
//
//    // Return success
//    return mTexture != NULL;
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
//    gFont = TTF_OpenFont("assets/font.ttf", 28);
//    if (gFont == NULL) {
//        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
//        success = false;
//    }
//    else {
//        // Set text color as black
//        SDL_Color textColor = { 0, 0, 0, 255 };
//
//        // Load prompt texture
//        if (!gPromptTextTexture.loadFromRenderedText("Press \"Enter\" to reset start time.", textColor)) {
//            printf("Unable to render prompt texture!\n");
//            success = false;
//        }
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gPromptTextTexture.free();
//    gPrimaryTextTexture.free();
//
//    // Free global font
//    TTF_CloseFont(gFont);
//    gFont = NULL;
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
//            //Set text color as black
//            SDL_Color textColor = { 0, 0, 0, 255 };
//
//            //Current time start time
//            Uint32 startTime = 0;
//            Uint32 printTime = 0;
//
//            //In memory text stream
//            std::stringstream timeText;
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
//                    // Reset start time on return keypress
//                    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
//                        startTime = SDL_GetTicks();
//                        printTime = 0;
//
//                        timeText.str("");
//                        timeText << "Seconds: " << printTime;
//
//                        // Update the text
//                        if (!gPrimaryTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
//                            printf("Unable to render time texture!\n");
//                        }
//                    }
//                    
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0xEA, 0xEA, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Update time if necessary
//                if (printTime < (SDL_GetTicks() - startTime) / 1000) {
//                    printTime = (SDL_GetTicks() - startTime) / 1000;
//                    // Set text to be rendered
//                 
//                    timeText.str("");
//                    timeText << "Seconds: " << printTime;
//                    
//                    // Update the text
//                    if (!gPrimaryTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
//                        printf("Unable to render time texture!\n");
//                    }
//                }
//
//                // Render the textures
//                gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, 0);
//                gPrimaryTextTexture.render((SCREEN_WIDTH - gPrimaryTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gPrimaryTextTexture.getHeight()) / 2);
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