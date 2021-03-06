/*
* author: Tonia Sanzo
*
* Lesson 3: Event Driven Programming
*/
//#include <SDL.h>
//#include <stdio.h>
//
//// Screen dimmensions
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// Starts up SDL and creates the window
//bool init();
//
//// Loads media
//bool loadMedia();
//
//// Frees media and shuts down SDL
//void close();
//
//
//// Note* these variables are defined as global variables this is for simplicity
//// but in future projects we wont define these varaibles globally
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// Note* These SDL_Surfaces are pointers, this is because it is easier to render
//// for example if we have a surfacew we render over and over it is easier to
//// have tons of copies of that surface when we can just render the one copy
//// over and over
//
//// The surface contained by the window
//SDL_Surface *gScreenSurface = NULL;
//
//// The image we will load and show on the screen
//SDL_Surface *gXOut = NULL;
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
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Load splash image
//    gXOut = SDL_LoadBMP("assets/xOut.bmp");
//    if (gXOut == NULL) {
//        printf("Unable to load image %s! SDL Error: %s\n", "assets/xOut.bmp", SDL_GetError());
//        success = false;
//    }
//    return success;
//}
//
//
//void close() {
//    // Deallocate surface
//    SDL_FreeSurface(gXOut);
//    gXOut = NULL;
//
//    // Destroy window
//    SDL_DestroyWindow(gWindow);
//
//    // Quit SDL subsystems
//    SDL_Quit();
//}
//
//
//int main(int argc, char *args[]) {
//    // Start up SDL and create window
//    if (!init()) {
//        printf("Failed to initialize!\n");
//    }
//    else {
//        // Load media
//        if (!loadMedia()) {
//            printf("Failed to load media!\n");
//        }
//        else
//        {
//            // Apply the image
//            SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
//
//            // Update the surface
//            SDL_UpdateWindowSurface(gWindow);
//        }
//    }
//
//    // Main loop flag
//    bool quit = false;
//
//    // Event handler, an SDL_Event is some thing like a key press, mouse motion, joy button press, etc.
//    SDL_Event e;
//
//    // While the application is running, this loop is often refereed to as the game loop
//    while (!quit) {
//        
//        // Handle the events on the queue
//        while (SDL_PollEvent(&e) != 0) {
//            // User requests quit
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        //Apply the image
//        SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
//
//        //Update the surface
//        SDL_UpdateWindowSurface(gWindow);
//   
//    }
//
//    // Free resources and close SDL
//    close();
//    return 0;
//}