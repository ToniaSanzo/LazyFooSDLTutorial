/*
* author: Tonia Sanzo
*
* Lesson 49: Mutex and conditions
*/
#include <SDL.h>
#include <SDL_thread.h>
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

//Our worker functions
int producer(void* data);
int consumer(void* data);
void produce();
void consume();

//The protective mutex
SDL_mutex* gBufferLock = NULL;

//The conditions
SDL_cond* gCanProduce = NULL;
SDL_cond* gCanConsume = NULL;

//The "data buffer"
int gData = -1;

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
    //Create the mutex
    gBufferLock = SDL_CreateMutex();

    //Create conditions
    gCanProduce = SDL_CreateCond();
    gCanConsume = SDL_CreateCond();

    // Loading success flag
    bool success = true;
    return success;
}


void close()
{
    //Destroy the mutex
    SDL_DestroyMutex(gBufferLock);
    gBufferLock = NULL;

    //Destroy conditions
    SDL_DestroyCond(gCanProduce);
    SDL_DestroyCond(gCanConsume);
    gCanProduce = NULL;
    gCanConsume = NULL;

    //Destroy window	
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


int producer(void* data)
{
    printf("\nProducer started...\n");

    // Seed thread random
    srand(SDL_GetTicks());

    for (int i = 0; i < 5; ++i)
    {
        SDL_Delay(rand() % 1000);
        produce();
    }

    printf("\nProducer finished!\n");
    return 0;
}


int consumer(void* data)
{
    printf("\nConsumer started...\n");

    // Seed thread random
    srand(SDL_GetTicks());

    for (int i = 0; i < 5; ++i)
    {
        SDL_Delay(rand() % 1000);
        consume();
    }
    printf("\nConsumer finished!\n");
    return 0;
}


void produce()
{
    //Lock
    SDL_LockMutex(gBufferLock);

    //If the buffer is full
    if (gData != -1)
    {
        //Wait for buffer to be cleared
        printf("\nProducer encountered full buffer, waiting for consumer to empty buffer...\n");
        SDL_CondWait(gCanProduce, gBufferLock);
    }

    //Fill and show buffer
    gData = rand() % 255;
    printf("\nProduced %d\n", gData);

    //Unlock
    SDL_UnlockMutex(gBufferLock);

    //Signal consumer
    SDL_CondSignal(gCanConsume);
   
}

void consume()
{
    //Lock
    SDL_LockMutex(gBufferLock);

    //If the buffer is empty
    if (gData == -1)
    {
        //Wait for buffer to be filled
        printf("\nConsumer encountered empty buffer, waiting for producer to fill buffer...\n");
        SDL_CondWait(gCanConsume, gBufferLock);
    }

    //Show and empty buffer
    printf("\nConsumed %d\n", gData);
    gData = -1;

    //Unlock
    SDL_UnlockMutex(gBufferLock);

    //Signal producer
    SDL_CondSignal(gCanProduce);
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

            // Run the thread
            srand(SDL_GetTicks());
            SDL_Thread* threadA = SDL_CreateThread(producer, "Thread A", (void*)"Thread A");
            SDL_Delay(16 + rand() % 32);
            SDL_Thread* threadB = SDL_CreateThread(consumer, "Thread B", (void*)"Thread B");

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
                SDL_SetRenderDrawColor(gRenderer, 0x33, 0x55, 0x33, 0xFF);
                SDL_RenderClear(gRenderer);


                //Update screen
                SDL_RenderPresent(gRenderer);
            }
            //Remove timer in case the call back was not called
            SDL_WaitThread(threadA, NULL);
            SDL_WaitThread(threadB, NULL);
        }

        //Free resources and close SDL
        close();
    }

    return 0;
}