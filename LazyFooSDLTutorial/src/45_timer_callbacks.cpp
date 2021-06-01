/*
* author: Tonia Sanzo
*
* Lesson 44: Frame Independent Movement
*/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <mutex>
#include <cstdlib>
#include <ctime>


// The screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 760;


// Renderer and window to render too
SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;


// Texture wrapper class
class UTexture {
public:
    // Initialize variables
    UTexture();

    // Deallocate memory
    ~UTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Creates blank texture
    bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

    // Deallocates texture
    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Set image scale
    void updateScale(double sc);

    // Renders texture at a given point
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip = SDL_FLIP_NONE);

    // Set self as render target
    void setAsRenderTarget();

    // Gets image dimensions
    int getWidth();
    int getHeight();
    int getScale();

    // Pixel manipulators
    bool lockTexture();
    bool unlockTexture();
    void* getPixels();
    void copyPixels(void* pixels);
    int getPitch();
    Uint32 getPixels32(unsigned int x, unsigned int y); // This gets a pixel at an exact (x,y) coordinate, this function works specifically for 32 bit pixels

private:
    // The actual hardware texture, and the games renderer
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;

    // Image dimesnions
    int mWidth, mHeight;
    double mScale;
};

#define FRAME_WIDTH 1280
#define FRAME_HEIGHT 760
const int ANIMATION_FRAMES = 30;             // number of frames in the sprite sheet
UTexture gBackgroundTexture;                 // Sprite sheet, loaded as a UTexture
UTexture gBackgroundTextureAlt;              // Alternative, texture for fading frames together

SDL_Rect gBackgroundClips[ANIMATION_FRAMES]; // Dimension and coordinates of each frame


// UTexture constructor
UTexture::UTexture() {
    // Initialize the variables
    mTexture = NULL;
    mPixels = NULL;
    mPitch = 0;
    mWidth = 0;
    mHeight = 0;
    mScale = 1;
}


// UTexture destructor
UTexture::~UTexture() {
    // Deallocate texture
    free();

    // Free renderer and font if necessary
    if (gRenderer) {
        gRenderer = NULL;
    }
}


// Load UTexture from a file
bool UTexture::loadFromFile(std::string path) {
    // Get rid of preexisting texture
    free();

    // Exit prematuraly if UTexture has not been properly initialized
    if (!gRenderer) {
        printf("Attempted to render a texture without initializing a renderer!\n");
        return false;
    }

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        printf("unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (!newTexture) {
            printf("Unable to create texture from %s! SDL Error: %s\n:", path.c_str(), SDL_GetError());
        }
        else {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}


// Creates a 32bit RGBA texture with stream access, (It is important that the textures pixels matches the format
// of the pixels we are streaming
bool UTexture::createBlank(int width, int height, SDL_TextureAccess access)
{
    // Create uninitialized texture
    mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if (mTexture == NULL)
    {
        printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        mWidth = width;
        mHeight = height;
    }

    return mTexture != NULL;
}


// Deallocate the texture
void UTexture::free() {
    // Free texture if it exists
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mScale = 0;
    }
}


// Define whether this texture can blend
void UTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
    // Modulate texture
    SDL_SetTextureColorMod(mTexture, r, g, b);
}


// Define whether this texture can blend
void UTexture::setBlendMode(SDL_BlendMode blending) {
    // Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}


// Define the texture's opacity
void UTexture::setAlpha(Uint8 alpha) {
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}


// Set image scale
void UTexture::updateScale(double sc) {
    mScale = sc;
    mWidth = static_cast<double>(mWidth) * sc;
    mHeight = static_cast<double>(mHeight) * sc;
}


// Render texture
void UTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Set Rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    // Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w * mScale;
        renderQuad.h = clip->h * mScale;
    }

    // Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


void UTexture::setAsRenderTarget()
{
    // Make self render target
    SDL_SetRenderTarget(gRenderer, mTexture);
}


int UTexture::getHeight() { return mHeight; }
int UTexture::getWidth() { return mWidth; }
int UTexture::getScale() { return mScale; }


// Lock the texture to be updated
bool UTexture::lockTexture()
{
    bool success = true;

    // Texture is already locked
    if (mPixels != NULL)
    {
        printf("Texture is already locked!\n");
        success = false;
    }
    // Lock texture
    else
    {
        if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0) {
            printf("Unable to lock texture! %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}


// Unlock the texture after it has been updated
bool UTexture::unlockTexture()
{
    bool success = true;

    // Texture is not locked
    if (mPixels == NULL)
    {
        printf("Texture is not locked!\n");
        success = false;
    }
    // Unlock texture
    else
    {
        SDL_UnlockTexture(mTexture);
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}


// Get the pointer to the pixels, while the texture's locked
void* UTexture::getPixels()
{
    return mPixels;
}


void UTexture::copyPixels(void* pixels)
{
    // Texture is locked
    if (mPixels != NULL)
    {
        // Copy to locked pixels
        memcpy(mPixels, pixels, mPitch * mHeight);
    }
}


// Get the texture's pitch (width in memory), while the texture's locked
int UTexture::getPitch()
{
    return mPitch;
}


// Gets the pixel with the specified (x,y) coordinate
Uint32 UTexture::getPixels32(unsigned int x, unsigned int y)
{
    // Convert the pixels to 32 bit
    Uint32* pixels = static_cast<Uint32*>(mPixels);

    // Get the pixel requested, note* we divide the mPitch by 4 to convert it from bytes to pixels
    return pixels[(y * (mPitch / 4)) + x];
}


//Starts up SDL and creates window
bool init();


//Loads media
bool loadMedia();


//Frees media and shuts down SDL
void close();



// Initialize the SDL subsystems
bool init() {
    //Initialization flag
    bool success = true;

    // Seed random
    srand(time(nullptr));

    //Initialize SDL video and timer
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Tonia Sanzo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for the window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load the background texture
    if (!gBackgroundTexture.loadFromFile("assets/its_a_loop.png"))
    {
        printf("Failed to load its a loop texture!\n");
        success = false;
    }

    else
    {
        gBackgroundTexture.setBlendMode(SDL_BLENDMODE_BLEND);
        // Set each frames coordinate and dimension
        for (int row = 0; row < 6; ++row)
        {
            for (int col = 0; col < 5; ++col)
            {
                gBackgroundClips[(row * 5) + col].x = col * FRAME_WIDTH;
                gBackgroundClips[(row * 5) + col].y = row * FRAME_HEIGHT;
                gBackgroundClips[(row * 5) + col].w = FRAME_WIDTH;
                gBackgroundClips[(row * 5) + col].h = FRAME_HEIGHT;
            }
        }
    }

    // Load the background
    if (!gBackgroundTextureAlt.loadFromFile("assets/its_a_loop.png"))
    {
        printf("Failed to load its a loop texture!\n");
        success = false;
    }

    else
    {
        gBackgroundTextureAlt.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    return success;
}

void close()
{
    // Free loaded images
    gBackgroundTexture.free();
    gBackgroundTextureAlt.free();

    //Destroy window	
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

// The application time based timer
class LTimer {
public:
    // Initializes variables
    LTimer();

    // The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    // Get's the timer's time
    Uint32 getTicks();

    // Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    // The clock time when the timer started
    Uint32 mStartTicks;

    // The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    // The timer status
    bool mPaused;
    bool mStarted;
};

LTimer::LTimer() {
    // Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start() {
    // Startthe timer
    mStarted = true;

    // Unpause the timer
    mPaused = false;

    // Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop() {
    // Stop the timer
    mStarted = false;

    // Unpause the timer
    mPaused = false;

    // Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause() {
    // If the timer is running and isn't already paused
    if (mStarted && !mPaused) {
        mPaused = true;

        // Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    // If the timer is running and paused
    if (mStarted && mPaused) {
        // Unpause the timer
        mPaused = false;

        // Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks() {
    // The actual timer time
    Uint32 time = 0;

    // If the timer is running
    if (mStarted) {
        // If the timer is paused
        if (mPaused) {
            time = mPausedTicks;
        }
        else {
            // Returnthe current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted() {
    // Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused() {
    // Timer is running and paused
    return mPaused && mStarted;
}

Uint32 callback(Uint32 interval, void* param)
{
    (*(static_cast<bool*>(param))) = true;
    printf("Callback true!\n");

    return 0;
}

// Cycles through and plays the loading cycle of netflix
void netflixLoading(LTimer& aTimer, int& aFrm)
{
    int frameTime = 322;
    if (aTimer.getTicks() > frameTime)
    {
        aFrm = (++aFrm) % 3;
        aTimer.stop();
        aTimer.start();
    }
}

// Cycles through the loop sequence
void uhOhMoment(LTimer& aTimer, int& aFrm, Uint8& altMod, bool& renderAltImg, bool& aPlayUhOh)
{
    int frameTime = 317;
    int i = 0;
    int fadeFrames = 4;

    // Baker smoking
    if (aTimer.getTicks() < frameTime * ++i) {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 3;
    }
    else if (aTimer.getTicks() < frameTime * ++i)
    {
        aFrm = 4;
    }
    // end Baker frame

    // Brandon Breathing
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 7;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 5;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 7;
    }
    else if(aTimer.getTicks() < frameTime * (i += 3))
    {
        aFrm = 6;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 7;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 5;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 7;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 5;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 7;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 5;
    }
    // End Brandon Breathing

    // Lights through blinds    
    else if (aTimer.getTicks() < frameTime * (i += fadeFrames))
    {
        renderAltImg = true;
        aFrm = 8;
    
        double whole = (frameTime * i) - (frameTime * (i - fadeFrames));
        double part = aTimer.getTicks() - (frameTime * (i - fadeFrames));
        double ratio = part / whole;
        altMod = 255 * ratio;
    }
    else if (aTimer.getTicks() < frameTime * (i += fadeFrames))
    {
        renderAltImg = true;
        aFrm = 9;
    
        double whole = (frameTime * i) - (frameTime * (i - fadeFrames));
        double part = aTimer.getTicks() - (frameTime * (i - fadeFrames));
        double ratio = part / whole;
        altMod = 255 * ratio;
    }
    else if (aTimer.getTicks() < frameTime * (i += fadeFrames))
    {
        renderAltImg = false;
        aFrm = 10;
    }
    // End Lights through blinds

    // Blinds Zoom in
    else if (aTimer.getTicks() < frameTime * (i += 1))
    {
        aFrm = 11;
    }
    else if (aTimer.getTicks() < frameTime * (i += 1))
    {
        aFrm = 12;
    }
    else if (aTimer.getTicks() < frameTime * (i += 1))
    {
        aFrm = 13;
    }
    else if (aTimer.getTicks() < frameTime * (i += 3))
    {
        aFrm = 14;
    }
    // End blinds zoom in

    // It's my Mom!

    else if (aTimer.getTicks() < frameTime * (i += 3))
    {
        aFrm = 15;
    }
    else if (aTimer.getTicks() < frameTime * (i += 3))
    {
        aFrm = 16;
    }
    else if (aTimer.getTicks() < frameTime * (i += 5))
    {
        aFrm = 17;
    }
    // End its my mom

    // My cousin Thiem
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }  
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }

    // Thiem Talking
    else if (aTimer.getTicks() < frameTime * (++i))
    {
       aFrm = 19;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
       aFrm = 22;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
       aFrm = 19;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
       aFrm = 22;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
       aFrm = 19;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
       aFrm = 22;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
       aFrm = 19;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
       aFrm = 22;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
       aFrm = 19;
    }

    else if (aTimer.getTicks() < frameTime * (i += 5))
    {
       aFrm = 22;
    }
    // End Thiem talking

    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i) + .5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i)+.5f))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (i += 2))
    {
        aFrm = 20;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 18;
    }
    else if (aTimer.getTicks() < frameTime * (static_cast<float>(i)+.5f))
    {
        aFrm = 20;
    }
    // End My cousin Thiem

    // End sequence
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 0;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 1;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 2;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 25;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 26;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 21;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 27;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 21;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 27;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 21;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 27;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 21;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 27;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 23;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 28;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 23;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 28;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 23;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 26;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 29;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 0;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 1;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 2;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 0;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 1;
    }
    else if (aTimer.getTicks() < frameTime * (++i))
    {
        aFrm = 2;
    }
    else if (aTimer.getTicks() < frameTime * (i += 16))
    {
        aFrm = 24;
    }
    // End end sequence
    
    else
    {
        printf("Time run: %d\n", aTimer.getTicks());
        aTimer.stop();
        aTimer.start();
        aPlayUhOh = false;
    }
}

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {

        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            // Keeps track of time between steps
            LTimer frmTimer;
            frmTimer.start();

            // Set callback
            bool cbRecieved(false);
            SDL_TimerID timerID = SDL_AddTimer((rand() % 5 + 9) * 1000, callback, &cbRecieved);
            int currentClip = 0;
            bool renderAltImg = false;
            bool playUhOh = false;
            Uint8 altAlpha = 0;

            // While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                if (playUhOh)
                {
                    uhOhMoment(frmTimer, currentClip, altAlpha, renderAltImg, playUhOh);
                }
                else
                {
                    netflixLoading(frmTimer, currentClip);
                }

                if (renderAltImg)
                {
                    gBackgroundTextureAlt.setAlpha(altAlpha);
                    gBackgroundTexture.render(0, 0, &gBackgroundClips[currentClip]);
                    gBackgroundTextureAlt.render(0, 0, &gBackgroundClips[currentClip + 1]);

                }
                else
                {
                    gBackgroundTexture.render(0, 0, &gBackgroundClips[currentClip]);
                }

                if (cbRecieved) {
                    printf("main thread! yes\n");
                    playUhOh = true;
                    cbRecieved = false;
                    timerID = SDL_AddTimer((rand() % 5 + 48) * 1000, callback, &cbRecieved);
                }

                //Update screen
                SDL_RenderPresent(gRenderer);
            }

            SDL_RemoveTimer(timerID);
        }

        //Free resources and close SDL
        close();
    }

    return 0;
}