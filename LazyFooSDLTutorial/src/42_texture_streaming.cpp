/*
* author: Tonia Sanzo
*
* Lesson 42: Texture Streaming
*/
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <string>
//#include <fstream>
//
//
//// The screen dimensions
//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 760;
//
//
//// Renderer and window to render too
//SDL_Renderer *gRenderer = nullptr;
//SDL_Window *gWindow = nullptr;
//
//
//// Texture wrapper class
//class UTexture {
//public:
//    // Initialize variables
//    UTexture();
//
//    // Deallocate memory
//    ~UTexture();
//
//    // Loads image at specified path
//    bool loadFromFile(std::string path);
//
//    // Creates blank texture
//    bool createBlank(int width, int height);
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
//    // Set image scale
//    void updateScale(double sc);
//
//    // Renders texture at given point
//    void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip = SDL_FLIP_NONE);
//
//    // Gets image dimensions
//    int getWidth();
//    int getHeight();
//    int getScale();
//
//    // Pixel manipulators
//    bool lockTexture();
//    bool unlockTexture();
//    void *getPixels();
//    void copyPixels(void *pixels);
//    int getPitch();
//    Uint32 getPixels32(unsigned int x, unsigned int y); // This gets a pixel at an exact (x,y) coordinate, this function works specifically for 32 bit pixels
//
//private:
//    // The actual hardware texture, and the games renderer
//    SDL_Texture *mTexture;
//    void *mPixels;
//    int mPitch;
//
//    // Image dimesnions
//    int mWidth, mHeight;
//    double mScale;
//};
//
//
//// A text animation stream
//class DataStream
//{
//public:
//    // Initializes internals
//    DataStream();
//
//    // Loads initial data
//    bool loadMedia();
//
//    // Deallocator
//    void free();
//
//    // Gets current frame data
//    void *getBuffer();
//
//private:
//    // Internal data
//    SDL_Surface *mImages[4];
//    int mCurrentImage;
//    int mDelayFrames;
//};
//
//
//// The streaming texture, and data stream
//UTexture gStreamingTexture;
//DataStream gDataStream;
//
//
//// UTexture constructor
//UTexture::UTexture() {
//    // Initialize the variables
//    mTexture = NULL;
//    mPixels = NULL;
//    mPitch = 0;
//    mWidth = 0;
//    mHeight = 0;
//    mScale = 1;
//}
//
//
//// UTexture destructor
//UTexture::~UTexture() {
//    // Deallocate texture
//    free();
//
//    // Free renderer and font if necessary
//    if (gRenderer) {
//        gRenderer = NULL;
//    }
//}
//
//
//// Load UTexture from a file
//bool UTexture::loadFromFile(std::string path) {
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
//        // Convert surface to display format
//        SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
//        if (!formattedSurface) {
//            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
//        }
//        else
//        {
//            // Create blank streamable texture
//            newTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
//            if (!newTexture)
//            {
//                printf("Unable to create blank texture! SDL Error: %s", SDL_GetError());
//            }
//            else
//            {
//                // Enable blending on texture
//                SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
//
//                // Lock texture for manipulation
//                SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);
//
//                // Copy loaded/formatted surface pixels
//                memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);
//
//                // Get image dimensions
//                mWidth = formattedSurface->w;
//                mHeight = formattedSurface->h;
//
//                // Get pixel data in editable format
//                Uint32 *pixels = (Uint32 *)mPixels;
//                int pixelCount = (mPitch / 2) * mHeight;
//
//                // Map colors
//                Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
//                int transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);
//
//                // Color key pixels
//                for (int i = 0; i < pixelCount; ++i)
//                {
//                    if (pixels[i] == colorKey)
//                    {
//                        pixels[i] = transparent;
//                    }
//                }
//
//                // Unlock texture to update
//                SDL_UnlockTexture(newTexture);
//                mPixels = NULL;
//            }
//
//            // Get rid of old formatted surface
//            SDL_FreeSurface(formattedSurface);
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
//
//// Creates a 32bit RGBA texture with stream access, (It is important that the textures pixels matches the format
//// of the pixels we are streaming
//bool UTexture::createBlank(int width, int height)
//{
//    // Create uninitialized texture
//    mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
//    if (mTexture == NULL)
//    {
//        printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
//    }
//    else
//    {
//        mWidth = width;
//        mHeight = height;
//    }
//
//    return mTexture != NULL;
//}
//
//
//// Deallocate the texture
//void UTexture::free() {
//    // Free texture if it exists
//    if (mTexture) {
//        SDL_DestroyTexture(mTexture);
//        mTexture = NULL;
//        mWidth = 0;
//        mHeight = 0;
//        mScale = 0;
//    }
//}
//
//
//// Define whether this texture can blend
//void UTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
//    // Modulate texture
//    SDL_SetTextureColorMod(mTexture, r, g, b);
//}
//
//
//// Define whether this texture can blend
//void UTexture::setBlendMode(SDL_BlendMode blending) {
//    // Set blending function
//    SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//
//// Define the texture's opacity
//void UTexture::setAlpha(Uint8 alpha) {
//    // Modulate texture alpha
//    SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//
//// Set image scale
//void UTexture::updateScale(double sc) {
//    mScale = sc;
//    mWidth = static_cast<double>(mWidth) * sc;
//    mHeight = static_cast<double>(mHeight) * sc;
//}
//
//
//// Render texture
//void UTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
//    // Set Rendering space and render to screen
//    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//    // Set clip rendering dimensions
//    if (clip != NULL) {
//        renderQuad.w = clip->w * mScale;
//        renderQuad.h = clip->h * mScale;
//    }
//
//    // Render to screen
//    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
//}
//
//
//int UTexture::getHeight() { return mHeight; }
//int UTexture::getWidth() { return mWidth; }
//int UTexture::getScale() { return mScale; }
//
//
//// Lock the texture to be updated
//bool UTexture::lockTexture()
//{
//    bool success = true;
//
//    // Texture is already locked
//    if (mPixels != NULL)
//    {
//        printf("Texture is already locked!\n");
//        success = false;
//    }
//    // Lock texture
//    else
//    {
//        if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0) {
//            printf("Unable to lock texture! %s\n", SDL_GetError());
//            success = false;
//        }
//    }
//
//    return success;
//}
//
//
//// Unlock the texture after it has been updated
//bool UTexture::unlockTexture()
//{
//    bool success = true;
//
//    // Texture is not locked
//    if (mPixels == NULL)
//    {
//        printf("Texture is not locked!\n");
//        success = false;
//    }
//    // Unlock texture
//    else
//    {
//        SDL_UnlockTexture(mTexture);
//        mPixels = NULL;
//        mPitch = 0;
//    }
//
//    return success;
//}
//
//
//// Get the pointer to the pixels, while the texture's locked
//void *UTexture::getPixels()
//{
//    return mPixels;
//}
//
//
//void UTexture::copyPixels(void *pixels)
//{
//    // Texture is locked
//    if (mPixels != NULL)
//    {
//        // Copy to locked pixels
//        memcpy(mPixels, pixels, mPitch * mHeight);
//    }
//}
//
//
//// Get the texture's pitch (width in memory), while the texture's locked
//int UTexture::getPitch()
//{
//    return mPitch;
//}
//
//
//// Gets the pixel with the specified (x,y) coordinate
//Uint32 UTexture::getPixels32(unsigned int x, unsigned int y)
//{
//    // Convert the pixels to 32 bit
//    Uint32 *pixels = static_cast<Uint32 *>(mPixels);
//
//    // Get the pixel requested, note* we divide the mPitch by 4 to convert it from bytes to pixels
//    return pixels[(y * (mPitch / 4)) + x];
//}
//
//
//DataStream::DataStream()
//{
//    mImages[0] = NULL;
//    mImages[1] = NULL;
//    mImages[2] = NULL;
//    mImages[3] = NULL;
//
//    mCurrentImage = 0; 
//    mDelayFrames = 50;
//}
//
//
//bool DataStream::loadMedia()
//{
//    bool success = true;
//
//    for (int i = 0; i < 4; ++i)
//    {
//        char path[64] = "";
//        sprintf_s(path, "assets/skate_anim_1_%d.png", i);
//
//        SDL_Surface *loadedSurface = IMG_Load(path);
//        if (loadedSurface == NULL)
//        {
//            printf("Unable to load %s! SDL_image error: %s\n", path, IMG_GetError());
//            success = false;
//        }
//        else
//        {
//            mImages[i] = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
//        }
//
//        SDL_FreeSurface(loadedSurface);
//    }
//
//    return success;
//}
//
//
//void DataStream::free()
//{
//    for (int i = 0; i < 4; ++i)
//    {
//        SDL_FreeSurface(mImages[i]);
//    }
//}
//
//
//void *DataStream::getBuffer()
//{
//    --mDelayFrames;
//    if (mDelayFrames == 0)
//    {
//        ++mCurrentImage;
//        mDelayFrames = 50;
//    }
//
//    if (mCurrentImage == 4)
//    {
//        mCurrentImage = 0;
//    }
//
//    return mImages[mCurrentImage]->pixels;
//}
//
//
////Starts up SDL and creates window
//bool init();
//
////Loads media
//bool loadMedia();
//
////Frees media and shuts down SDL
//void close();
//
//// Initialize the SDL subsystems
//bool init() {
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
//            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
//    return success;
//}
//
//bool loadMedia()
//{
//    //Loading success flag
//    bool success = true;
//
//    // Load the texture
//    if (!gStreamingTexture.createBlank(192, 288))
//    {
//        printf("Failed to load streaming texture!\n");
//        success = false;
//    }
//
//    // Load data stream
//    if (!gDataStream.loadMedia())
//    {
//        printf("Failed to load data stream!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//void close()
//{
//    // Free loaded images
//    gStreamingTexture.free();
//    gDataStream.free();
//
//    //Destroy window	
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    //Quit SDL subsystems
//    IMG_Quit();
//    SDL_Quit();
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
//
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
//            //While application is running
//            while (!quit)
//            {
//                //Handle events on queue
//                while (SDL_PollEvent(&e) != 0)
//                {
//                    //User requests quit
//                    if (e.type == SDL_QUIT)
//                    {
//                        quit = true;
//                    }
//
//                }
//
//                //Clear screen
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                // Copy frame from buffer
//                gStreamingTexture.lockTexture();
//                gStreamingTexture.copyPixels(gDataStream.getBuffer());
//                gStreamingTexture.unlockTexture();
//
//                // Render frame
//                gStreamingTexture.render((SCREEN_WIDTH - gStreamingTexture.getWidth()) / 2, (SCREEN_HEIGHT - gStreamingTexture.getHeight()) / 2);
//
//                //Update screen
//                SDL_RenderPresent(gRenderer);
//            }
//        }
//
//        //Free resources and close SDL
//        close();
//    }
//
//    return 0;
//}