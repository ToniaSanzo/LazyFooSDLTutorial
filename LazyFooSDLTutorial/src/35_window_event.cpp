///*
//* author: Tonia Sanzo
//*
//* Lesson 35: Window Events
//*/
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
//class LWindow
//{
//public:
//    // Intializes internals
//    LWindow();
//
//    // Creates window
//    bool init();
//
//    // Creates renderer from internal window
//    SDL_Renderer *createRenderer();
//
//    // Handles window events
//    void handleEvent(SDL_Event &e);
//
//    // Deallocates internals
//    void free();
//
//    // Window dimensions
//    int getWidth();
//    int getHeight();
//    double getScale();
//    void updateScale(double sc);
//
//    // Window focii
//    bool hasMouseFocus();
//    bool hasKeyboardFocus();
//    bool isMinimized();
//
//private:
//    // Window data
//    SDL_Window *mWindow;
//    double mScale;
//
//    // Window dimensions
//    int mWidth;
//    int mHeight;
//
//    // Window focus
//    bool mMouseFocus;
//    bool mKeyboardFocus;
//    bool mFullScreen;
//    bool mMinimized;
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
//    double getScale();
//    double getWindowScale();
//
//    // Set image scale, and window scale
//    void updateScale(double sc);
//    void updateWindowScale(double sc);
//private:
//    // The actual hardware texture
//    SDL_Texture *mTexture;
//
//    // Image dimensions
//    int mWidth;
//    int mHeight;
//    double scale, windowScale;
//};
//
//// Our custom window
//LWindow gWindow;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Rendered texture
//LTexture gSceneTexture;
//
//// Screen dimensions
//const int SCREEN_WIDTH = 614;
//const int SCREEN_HEIGHT = 794;
//
//// LTexture constructor
//LTexture::LTexture() {
//    // Initialize
//    mTexture = NULL;
//    mWidth = 0;
//    mHeight = 0;
//    scale = 1;
//    windowScale = 1;
//}
//
//// LTexture destructor
//LTexture::~LTexture() {
//    // Deallocate texture
//    free();
//}
//
//// Sets LTextures render scale
//void LTexture::updateScale(double sc) 
//{
//    scale = sc;
//    mWidth *= sc;
//    mHeight *= sc;
//}
//
//// Update the window scale
//void LTexture::updateWindowScale(double sc)
//{
//    windowScale = sc;
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
//    SDL_Rect renderQuad = { x , y, mWidth * windowScale, mHeight * windowScale };
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
//double LTexture::getScale() { return scale; }
//double LTexture::getWindowScale() { return windowScale; }
//
//
//LWindow::LWindow() {
//    // Initialize non-existant window
//    mWindow = NULL;
//    mMouseFocus = false;
//    mKeyboardFocus = false;
//    mFullScreen = false;
//    mMinimized = false;
//    mWidth = 0;
//    mHeight = 0;
//    mScale = 1;
//}
//
//bool LWindow::init() {
//    // Create window
//    mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//    if (mWindow != NULL) {
//        mMouseFocus = true;
//        mKeyboardFocus = true;
//        mWidth = SCREEN_WIDTH;
//        mHeight = SCREEN_HEIGHT;
//    }
//
//    return mWindow != NULL;
//}
//
//SDL_Renderer *LWindow::createRenderer() {
//    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//}
//
//void LWindow::handleEvent(SDL_Event &e) {
//    // Window event occured
//    if (e.type == SDL_WINDOWEVENT) {
//        // Caption update flag
//        bool updateCaption = false;
//        double tempScale = 1;
//
//        switch (e.window.event) {
//        // Get new dimensions and repaint on window size change
//        case SDL_WINDOWEVENT_RESIZED:
//            mWidth = e.window.data1;
//            mHeight = e.window.data2;
//            tempScale = static_cast<double>(mHeight) / SCREEN_HEIGHT;
//            updateScale(tempScale);
//            SDL_RenderPresent(gRenderer);
//            break;
//
//        // Repaint on exposure
//        case SDL_WINDOWEVENT_EXPOSED:
//            SDL_RenderPresent(gRenderer);
//            break;
//        // Mouse entered window
//        case SDL_WINDOWEVENT_ENTER:
//            mMouseFocus = true;
//            updateCaption = true;
//            break;
//
//        // Mouse left window
//        case SDL_WINDOWEVENT_LEAVE:
//            mMouseFocus = false;
//            updateCaption = true;
//            break;
//
//        // Window has keyboard focus
//        case SDL_WINDOWEVENT_FOCUS_GAINED:
//            mKeyboardFocus = true;
//            updateCaption = true;
//            break;
//        
//        // Window lost keyboard focus
//        case SDL_WINDOWEVENT_FOCUS_LOST:
//            mKeyboardFocus = false;
//            updateCaption = true;
//            break;
//
//        // Window minimized
//        case SDL_WINDOWEVENT_MINIMIZED:
//            mMinimized = true;
//            break;
//
//        // Window maximized
//        case SDL_WINDOWEVENT_MAXIMIZED:
//            mMinimized = false;
//            break;
//
//        // Window restored
//        case SDL_WINDOWEVENT_RESTORED:
//            mMinimized = false;
//            break;
//        }
//
//        // Update window caption with new data
//        if (updateCaption) {
//            std::stringstream caption;
//            caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
//            SDL_SetWindowTitle(mWindow, caption.str().c_str());
//        }
//
//        // Enter exit full screen on return key
//        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
//            if (mFullScreen) {
//                SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
//                mFullScreen = false;
//            }
//            else {
//                SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
//                mFullScreen = true;
//                mMinimized = false;
//            }
//        }
//        
//    }
//}
//
//int LWindow::getWidth() {
//    return mWidth;
//}
//
//int LWindow::getHeight() {
//    return mHeight;
//}
//
//double LWindow::getScale()
//{
//    return mScale;
//}
//
//bool LWindow::hasMouseFocus() {
//    return mMouseFocus;
//}
//
//bool LWindow::hasKeyboardFocus() {
//    return mKeyboardFocus;
//}
//
//bool LWindow::isMinimized() {
//    return mMinimized;
//}
//
//void LWindow::updateScale(double sc)
//{
//    mWidth = SCREEN_WIDTH * sc;
//    mHeight = SCREEN_HEIGHT * sc;
//    SDL_SetWindowSize(mWindow, mWidth, mHeight);
//    mScale = sc;
//}
//
//void LWindow::free() {
//    SDL_DestroyWindow(mWindow);
//    mWindow = NULL;
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
//        if (!gWindow.init())
//        {
//            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//            success = false;
//        }
//        else
//        {
//            // Create renderer for the window
//            gRenderer = gWindow.createRenderer();
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
//    // Load background texture
//    if (!gSceneTexture.loadFromFile("assets/hello_adobe.png")) {
//        printf("Failed to load background texture image!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gSceneTexture.free();
//   
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    gWindow.free();
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
//            // The camera area
//            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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
//                    gWindow.handleEvent(e);
//                }
//
//                // Resize the texture in relation to the window rescale
//                if (gSceneTexture.getWindowScale() != gWindow.getScale()) {
//                    gSceneTexture.updateWindowScale(gWindow.getScale());
//                }
//
//                // Only draw when not minimized
//                if (!gWindow.isMinimized()) {
//                    // Clear screen, to white
//                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                    SDL_RenderClear(gRenderer);
//
//                    // Render textures
//                    gSceneTexture.render(0, 0);
//
//                    // Update screen
//                    SDL_RenderPresent(gRenderer);
//                }
//
//            }
//        }
//    }
//
//    //Free resources and close SDL
//    close();
//
//    return 0;
//}