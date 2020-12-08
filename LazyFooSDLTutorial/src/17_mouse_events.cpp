/*
* author: Tonia Sanzo
*
* Lesson 17: Mouse Events
*/
//#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <time.h>
//#include <cmath>
//
//// Button constants
//const int BUTTON_WIDTH = 160;
//const int BUTTON_HEIGHT = 120;
//const int TOTAL_BUTTONS = 4;
//
//enum LButtonSprite {
//    BUTTON_SPRITE_MOUSE_OUT = 0,
//    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
//    BUTTON_SPRITE_MOUSE_DOWN = 2,
//    BUTTON_SPRITE_MOUSE_UP = 3,
//    BUTTON_SPRITE_TOTAL = 4
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
//#if defined(SDL_TTF_MAJOR_VERSION)
//    // Creates image from font string
//    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
//#endif
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
//// The mouse button
//class LButton {
//public:
//    // Initializes internal varaibles
//    LButton();
//
//    // Sets top left position
//    void setPosition(int x, int y);
//
//    // Handles mouse event
//    void handleEvent(SDL_Event *e);
//
//    // Shows button sprite
//    void render();
//private:
//    // Top left position
//    SDL_Point mPosition;
//
//    // Currently used global sprite
//    LButtonSprite mCurrentSprite;
//};
//
//// The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
//// The window renderer
//SDL_Renderer *gRenderer = NULL;
//
//// Load the music
//Mix_Music *gMusic = NULL;
//
//// Rendered texture
//LTexture gButtonSpriteSheetTexture;
//SDL_Rect gSpriteClips[TOTAL_BUTTONS];
//LButton gButtons[TOTAL_BUTTONS];
//
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
//// Load a font texture
//#if defined(SDL_TTF_MAJOR_VERSION)
//bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
//    //// Get rid of preexisting texture
//    //free();
//
//    //// Render text surface
//    //SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//    //if (textSurface == NULL) {
//    //    printf("Unable to render text surface!  SDL_ttfError: %s\n", TTF_GetError());
//    //}
//    //else {
//    //    // Create texture from surface pixels
//    //    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//    //    if (mTexture == NULL) {
//    //        printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
//    //    }
//    //    else {
//    //        // Get image dimensions
//    //        mWidth = textSurface->w;
//    //        mHeight = textSurface->h;
//    //    }
//
//    //    // Get rid of old surface
//    //    SDL_FreeSurface(textSurface);
//    //}
//
//    //// Return success
//    //return mTexture != NULL;
//    return false;
//}
//#endif
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
//LButton::LButton() {
//    mPosition.x = mPosition.y = 0;
//    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
//}
//
//void LButton::setPosition(int x, int y) {
//    mPosition.x = x;
//    mPosition.y = y;
//}
//
//void LButton::handleEvent(SDL_Event *e) {
//    // If mouse event happened
//    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
//        // Get mouse position
//        int x, y;
//        SDL_GetMouseState(&x, &y);
//
//        // Check if mouse is in button
//        bool inside = true;
//
//        // Mouse is left of the button
//        if (x < (mPosition.x + 25)) {
//            inside = false;
//        }
//        // Mouse is right of the button
//        else if (x > (mPosition.x + (BUTTON_WIDTH * 2) - 25)) {
//            inside = false;
//        }
//        // Mouse above the button
//        else if (y < mPosition.y + 25) {
//            inside = false;
//        }
//        // Mouse below the button
//        else if (y > (mPosition.y + (BUTTON_HEIGHT * 2) - 25)) {
//            inside = false;
//        }
//
//        // Mouse is outside button
//        if (!inside) {
//            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
//        }
//        // Mouse is inside button
//        else {
//            // Set mouse over sprite
//            switch (e->type) {
//            case SDL_MOUSEMOTION:
//                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
//                Mix_PauseMusic();
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
//                
//                Mix_ResumeMusic();
//                break;
//            case SDL_MOUSEBUTTONUP:
//                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
//                Mix_PauseMusic();
//                break;
//            default:; // null //
//            }
//        }
//    }
//}
//
//void LButton::render() {
//    // Show current buttonsprite
//    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
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
//        gWindow = SDL_CreateWindow("Froggy Blues", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
//                // Initialize SDL_mixer
//                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
//    // Load buttons texturesloadFromFile
//    if (!gButtonSpriteSheetTexture.loadFromFile("assets/button.png")) {
//        printf("Failed to load buttons texture!\n");
//        success = false;
//    }
//    else {
//        gButtonSpriteSheetTexture.updateScale(2);
//        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
//            gSpriteClips[i].x = i * BUTTON_WIDTH;
//            gSpriteClips[i].y = 0;
//            gSpriteClips[i].w = BUTTON_WIDTH;
//            gSpriteClips[i].h = BUTTON_HEIGHT;
//        }
//
//        gButtons[0].setPosition(0, 0);
//        gButtons[1].setPosition(BUTTON_WIDTH * 2, 0);
//        gButtons[2].setPosition(0, BUTTON_HEIGHT * 2);
//        gButtons[3].setPosition(BUTTON_WIDTH * 2, BUTTON_HEIGHT * 2);
//    }
//
//    // Load music
//    gMusic = Mix_LoadMUS("assets/WoodenChampionship_loboloco.wav");
//    if (gMusic == NULL) {
//        printf("Failed to load blues music! SDL_mixer Error: %s\n", Mix_GetError());
//        success = true;
//    }
//
//
//
//    return success;
//}
//
//void close() {
//    // Free loaded images
//    gButtonSpriteSheetTexture.free();
//
//    // Free the music 
//    Mix_FreeMusic(gMusic);
//    gMusic = NULL;
//
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    // Quit SDL subsystems
//    Mix_Quit();
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
//            Mix_PlayMusic(gMusic, -1);
//            Mix_PauseMusic();
//            // Main loop flag
//            bool quit = false;
//
//            // Event handler
//            SDL_Event e;
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
//
//                    // Handle button events
//                    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
//                        gButtons[i].handleEvent(&e);
//                    }
//
//                }
//
//                // Clear screen, to black
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Render buttons
//                for (int i = 0; i < TOTAL_BUTTONS; ++i) {
//                    gButtons[i].render();
//                }
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