/*
* author: Tonia Sanzo
*
* Lesson 5: Optimized Surface Loading and Soft Stretching
*/
//#include <SDL.h>
//#include <stdio.h>
//#include <string>
//
//
//// Screen dimmensions
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// Starts up SDL and creates the window
//bool init();
//
//// Frees media and shuts down SDL
//void close();
//
//// Loads the individual image
//SDL_Surface *loadSurface(std::string path);
//
//// Note* these variables are defined as global variables this is for simplicity
//// but in future projects we wont define these varaibles globally
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The surface contained by the window
//SDL_Surface *gScreenSurface = NULL;
//
//// The current image being displayed on the screen
//SDL_Surface *gCurrentSurface = NULL;
//
//
//bool init() {
//    // Initialization flag
//    bool success = true;
//
//    // Initiailize SDL, if an error occurs SDL_Init() returns -1
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//        success = false;
//    }
//    else {
//        // Create window
//        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//
//        // If the window failed to initialize
//        if (gWindow == NULL) {
//            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//            success = false;
//        }
//        else {
//            // Get window surface
//            gScreenSurface = SDL_GetWindowSurface(gWindow);
//        }
//    }
//
//    return success;
//}
//
//
//void close() {
//    // Deallocate surface
//    SDL_FreeSurface(gCurrentSurface);
//    gCurrentSurface = NULL;
//
//    // Destroy window
//    SDL_DestroyWindow(gWindow);
//
//    // Quit SDL subsystems
//    SDL_Quit();
//}
//
//
//SDL_Surface *loadSurface(std::string path) {
//    // The final optimized image
//    SDL_Surface *optimizedSurface = NULL;
//
//
//    // Load image at specified path
//    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
//    if (loadedSurface == NULL) {
//        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//    }
//    else {
//        // Convert surface to screen format
//        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
//        if (optimizedSurface == NULL) {
//            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//        }
//
//        // Get rid of old loaded surface
//        SDL_FreeSurface(loadedSurface);
//    }
//    return optimizedSurface;
//}
//
//int main(int argc, char *args[]) {
//    // Start up SDL and create window
//    if (!init()) {
//        printf("Failed to initialize!\n");
//    }
//    else {
//       
//        // Main loop flag
//        bool quit = false;
//
//        // Event handler, an SDL_Event is some thing like a key press, mouse motion, joy button press, etc.
//        SDL_Event e;
//
//        // Apply the image strethed
//        SDL_Rect stretchRect;
//        stretchRect.x = 0;
//        stretchRect.y = 0;
//        stretchRect.w = SCREEN_WIDTH;
//        stretchRect.h = SCREEN_HEIGHT;
//            
//        gCurrentSurface = loadSurface("assets/heartWM.bmp");
//
//        // While the application is running, this loop is often refereed to as the game loop
//        while (!quit) {
//
//            // Handle the events on the queue
//            while (SDL_PollEvent(&e) != 0) {
//                // User requests quit
//                if (e.type == SDL_QUIT) {
//                    quit = true;
//                }
//            }
//            //Apply the current image
//            SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
//
//            //Update the surface
//            SDL_UpdateWindowSurface(gWindow);
//
//        }
//    }
//
//    // Free resources and close SDL
//    close();
//    return 0;
//}