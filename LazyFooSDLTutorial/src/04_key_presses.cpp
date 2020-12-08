///*
//* author: Tonia Sanzo
//*
//* Lesson 4: Key Presses
//*/
//#include <SDL.h>
//#include <stdio.h>
//#include <string>
//
//
//// Screen dimmensions
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//
//// key press surface constants, this enum defines KEY_PRESS_SURFACE_DEFAULT = 0, ... , KEY_PRESS_SURFACE_TOTAL
//enum KeyPressSurfaces
//{
//    KEY_PRESS_SURFACE_DEFAULT,
//    KEY_PRESS_SURFACE_UP,
//    KEY_PRESS_SURFACE_DOWN,
//    KEY_PRESS_SURFACE_LEFT,
//    KEY_PRESS_SURFACE_RIGHT,
//    KEY_PRESS_SURFACE_TOTAL
//};
//
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
//// Note* These SDL_Surfaces are pointers, this is because it is easier to render
//// for example if we have a surfacew we render over and over it is easier to
//// have tons of copies of that surface when we can just render the one copy
//// over and over
//
//// Initialize each surface in the program
//bool loadMedia();
//
//// The surface contained by the window
//SDL_Surface *gScreenSurface = NULL;
//
//// The images that correspond to a keypress
//SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
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
//    // Deallocate surface's
//    SDL_FreeSurface(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]);
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = NULL;
//
//    SDL_FreeSurface(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]);
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = NULL;
//
//    SDL_FreeSurface(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]);
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = NULL;
//    
//    SDL_FreeSurface(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]);
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = NULL;
//
//    SDL_FreeSurface(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]);
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = NULL;
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
//    // Load image at specified path
//    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
//    if (loadedSurface == NULL) {
//        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//    }
//    return loadedSurface;
//}
//
//
//bool loadMedia() {
//    // Loading success flag
//    bool success = true;
//
//    // Load default surface
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/default.bmp");
//    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
//        printf("Failed to load default image!\n");
//        success = false;
//    }
//
//    // Load up surface
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/up.bmp");
//    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
//        printf("Failed to load up image!\n");
//        success = false;
//    }
//
//    // Load down surface
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/down.bmp");
//    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
//        printf("Failed to load down image!\n");
//        success = false;
//    }
//
//    // Load left surface
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/left.bmp");
//    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
//        printf("Failed to load left image!\n");
//        success = false;
//    }
//
//    // Load right surface
//    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/right.bmp");
//    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
//        printf("Failed to load right image!\n");
//        success = false;
//    }
//
//    return success;
//}
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
//            // Main loop flag
//            bool quit = false;
//
//            // Event handler, an SDL_Event is some thing like a key press, mouse motion, joy button press, etc.
//            SDL_Event e;
//
//            // Set default current surface
//            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
//
//            // While the application is running, this loop is often refereed to as the game loop
//            while (!quit) {
//
//                // Handle the events on the queue
//                while (SDL_PollEvent(&e) != 0) {
//                    // User requests quit
//                    if (e.type == SDL_QUIT) {
//                        quit = true;
//                    }
//                    // User presses a key
//                    else if (e.type == SDL_KEYDOWN) {
//                        // NOTE* inside of SDL_Event is is an SDL_Keysym which contains information about the key that was
//                        // pressed, such as a key press
//                        // Select surfaces based on key press
//                        switch (e.key.keysym.sym) {
//                        case SDLK_UP:
//                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
//                            break;
//                        case SDLK_DOWN:
//                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
//                            break;
//                        case SDLK_LEFT:
//                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
//                            break;
//                        case SDLK_RIGHT:
//                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
//                            break;
//                        default:
//                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
//                            break;
//                        }
//
//                    }
//                }
//
//                //Apply the current image
//                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
//
//                //Update the surface
//                SDL_UpdateWindowSurface(gWindow);
//
//            }
//        }
//    }
//
//    // Free resources and close SDL
//    close();
//    return 0;
//}