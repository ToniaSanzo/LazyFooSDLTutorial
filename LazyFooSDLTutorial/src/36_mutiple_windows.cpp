/*
* author: Tonia Sanzo
*
* Lesson 36: Multiple windows
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
//// Total windows
//const int TOTAL_WINDOWS = 3;
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
//    // Focuses on window
//    void focus();
//
//    // Shows windows contents
//    void render();
//
//    // Deallocates internals
//    void free();
//
//    // Window dimensions
//    int getWidth();
//    int getHeight();
//
//    // Window focii
//    bool hasMouseFocus();
//    bool hasKeyboardFocus();
//    bool isMinimized();
//    bool isShown();
//
//private:
//    // Window data
//    SDL_Window *mWindow;
//    SDL_Renderer *mRenderer;
//    int mWindowID;
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
//    bool mShown;
//};
//
//// 3 globally allocated windows
//LWindow gWindow[TOTAL_WINDOWS];
//
//// Screen dimensions
//const int SCREEN_WIDTH = 614;
//const int SCREEN_HEIGHT = 794;
//
//
//LWindow::LWindow() {
//    // Initialize non-existant window
//    mWindow = NULL;
//    mRenderer = NULL;
//    mMouseFocus = false;
//    mKeyboardFocus = false;
//    mFullScreen = false;
//    mMinimized = false;
//    mShown = false;
//    mWindowID = 0;
//    mWidth = 0;
//    mHeight = 0;
//}
//
//SDL_Renderer *LWindow::createRenderer() {
//    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//}
//
//void LWindow::handleEvent(SDL_Event &e) {
//    // Window event occured
//    if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID) {
//        // Caption update flag
//        bool updateCaption = false;
//
//        switch (e.window.event) {
//        // Window appeared
//        case SDL_WINDOWEVENT_SHOWN:
//            mShown = true;
//            break;
//
//        // Window disappeared
//        case SDL_WINDOWEVENT_HIDDEN:
//            mShown = false;
//            break;
//
//
//        // Get new dimensions and repaint on window size change
//        case SDL_WINDOWEVENT_SIZE_CHANGED:
//            mWidth = e.window.data1;
//            mHeight = e.window.data2;
//            SDL_RenderPresent(mRenderer);
//            break;
//
//        // Repaint on exposure
//        case SDL_WINDOWEVENT_EXPOSED:
//            SDL_RenderPresent(mRenderer);
//            break;
//        
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
//
//        // Hide on close
//        case SDL_WINDOWEVENT_CLOSE:
//            SDL_HideWindow(mWindow);
//            break;
//        }
//
//        // Update window caption with new data
//        if (updateCaption) {
//            std::stringstream caption;
//            caption << "SDL Tutorial - ID:" << mWindowID << " MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
//            SDL_SetWindowTitle(mWindow, caption.str().c_str());
//        }
//    }
//}
//
//void LWindow::focus() {
//    // Restore window if needed
//    if (!mShown) { SDL_ShowWindow(mWindow); }
//
//    // Move window forward
//    SDL_RaiseWindow(mWindow);
//}
//
//void LWindow::render() {
//    if (!mMinimized) {
//        // Clear screen
//        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(mRenderer);
//
//        // Update screen
//        SDL_RenderPresent(mRenderer);
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
//bool LWindow::isShown() {
//    return mShown;
//}
//
//void LWindow::free() {
//    SDL_DestroyRenderer(mRenderer);
//    mRenderer = NULL;
//
//    SDL_DestroyWindow(mWindow);
//    mWindow = NULL;
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
//
//        // Create renderer for window
//        mRenderer = createRenderer();
//        if (mRenderer == NULL) {
//            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
//            SDL_DestroyWindow(mWindow);
//            mWindow = NULL;
//        }
//        else {
//            // Initialize renderer color
//            SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//
//            // Grab window identifier
//            mWindowID = SDL_GetWindowID(mWindow);
//
//            // Flag as opened
//            mShown = true;
//        }
//    }
//    else {
//        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//    }
//
//    return mWindow != NULL && mRenderer != NULL;
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
//        // Set texture filtering to linear
//        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//            printf("Warning! Linear texture filtering not enabled!");
//        }
//
//        // Create window
//        if (!gWindow[0].init()) {
//            printf("Window 0 could not be created!\n");
//            success = false;
//        }
//    }
//    return success;
//}
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//    return success;
//}
//
//void close() {
//    for (int i = 0; i < TOTAL_WINDOWS; ++i) {
//        gWindow[i].free();
//    }
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
//            // Initialize the rest of the windows
//            for (int i = 1; i < TOTAL_WINDOWS; ++i) {
//                gWindow[i].init();
//            }
//
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
//                    // Handle window events
//                    for (int i = 0; i < TOTAL_WINDOWS; ++i) {
//                        gWindow[i].handleEvent(e);
//                    }
//
//                    // Pull up window
//                    if (e.type == SDL_KEYDOWN) {
//                        switch (e.key.keysym.sym) {
//                        case SDLK_1:
//                            gWindow[0].focus();
//                            break;
//
//                        case SDLK_2:
//                            gWindow[1].focus();
//                            break;
//
//                        case SDLK_3:
//                            gWindow[2].focus();
//                            break;
//                        }
//                    }
//                }
//
//                // Update all windows
//                for (int i = 0; i < TOTAL_WINDOWS; ++i) {
//                    gWindow[i].render();
//                }
//
//                // Check all windows
//                bool allWindowsClosed = true;
//                for (int i = 0; i < TOTAL_WINDOWS; ++i) {
//                    if (gWindow[i].isShown()) {
//                        allWindowsClosed = false;
//                        break;
//                    }
//                }
//                
//                // Application closedc all windows
//                if (allWindowsClosed) {
//                    quit = true;
//                }
//            }
//        }
//    }
//
//    //Free resources and close SDL
//    close();
//
//    return 0;
//}