///*
//* author: Tonia Sanzo
//*
//* Lesson 41: Bitmap Fonts
//*/
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <string>
//#include <fstream>
//
//// The screen dimensions
//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 760;
//
//// Renderer and window to render too
//SDL_Renderer *gRenderer = nullptr;
//SDL_Window *gWindow = nullptr;
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
//    void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip = SDL_FLIP_NONE);
//
//    // Gets image dimensions
//    int getWidth();
//    int getHeight();
//    int getScale();
//
//    // Set image scale
//    void updateScale(double sc);
//
//    // Pixel manipulators
//    bool lockTexture();
//    bool unlockTexture();
//    void *getPixels();
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
//// Out bitmap font
//class LBitmapFont
//{
//public:
//    // The default constructor
//    LBitmapFont();
//
//    // Generates the font
//    bool buildFont(UTexture *bitmap);
//
//    // Shows the text
//    void renderText(int x, int y, std::string text);
//
//private:
//    // The font texture
//    UTexture *mBitmap;
//
//    // The individual characters in the surface
//    SDL_Rect mChars[256];
//
//    // Spacing Variables
//    int mNewLine, mSpace;
//};
//
//// The font texture, and font object
//UTexture gFontTexture;
//LBitmapFont gFont;
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
//// Define whether this texture can blend
//void UTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
//    // Modulate texture
//    SDL_SetTextureColorMod(mTexture, r, g, b);
//}
//
//// Define whether this texture can blend
//void UTexture::setBlendMode(SDL_BlendMode blending) {
//    // Set blending function
//    SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//// Define the texture's opacity
//void UTexture::setAlpha(Uint8 alpha) {
//    // Modulate texture alpha
//    SDL_SetTextureAlphaMod(mTexture, alpha);
//}
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
//int UTexture::getHeight() { return mHeight; }
//int UTexture::getWidth() { return mWidth; }
//int UTexture::getScale() { return mScale; }
//
//// Set image scale
//void UTexture::updateScale(double sc) {
//    mScale = sc;
//    mWidth = static_cast<double>(mWidth) * sc;
//    mHeight = static_cast<double>(mHeight) * sc;
//}
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
//// Get the pointer to the pixels, while the texture's locked
//void *UTexture::getPixels()
//{
//    return mPixels;
//}
//
//// Get the texture's pitch (width in memory), while the texture's locked
//int UTexture::getPitch()
//{
//    return mPitch;
//}
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
//LBitmapFont::LBitmapFont()
//{
//    // Initialize variables
//    mBitmap = NULL;
//    mNewLine = 0;
//    mSpace = 0;
//}
//
//bool LBitmapFont::buildFont(UTexture *bitmap)
//{
//    bool success = true;
//
//    // Lock pixels for access
//    if (!bitmap->lockTexture())
//    {
//        printf("Unable to lock bitmap font texture!\n");
//        success = false;
//    }
//    else
//    {
//        // Set the background color 
//        Uint32 bgColor = bitmap->getPixels32(0, 0);
//
//        // Set the cell dimensions
//        int cellW = bitmap->getWidth() / 16;
//        int cellH = bitmap->getHeight() / 16;
//
//        // New line variables
//        int top = cellH;
//        int baseA = cellH;
//
//        // The current character we're setting
//        int currentChar = 0;
//
//        // Go through the cell rows
//        for (int rows = 0; rows < 16; ++rows)
//        {
//            // Go through the cell columns
//            for (int cols = 0; cols < 16; ++cols)
//            {
//                // Set the character offset
//                mChars[currentChar].x = cellW * cols;
//                mChars[currentChar].y = cellH * rows;
//
//                // Set the dimensions of the character
//                mChars[currentChar].w = cellW;
//                mChars[currentChar].h = cellH;
//
//                // Find Left Side
//                // Go through pixel columns
//                for (int pCol = 0; pCol < cellW; ++pCol)
//                {
//                    // Go through pixel rows
//                    for (int pRow = 0; pRow < cellH; ++pRow)
//                    {
//                        // Get the pixel offsets
//                        int pX = (cellW * cols) + pCol;
//                        int pY = (cellH * rows) + pRow;
//
//                        // If a non colorkeypixel is found
//                        if (bitmap->getPixels32(pX, pY) != bgColor)
//                        {
//                            // Set the x offset
//                            mChars[currentChar].x = pX;
//
//                            // Break the loops
//                            pCol = cellW;
//                            pRow = cellH;
//                        }
//                    }
//                }
//
//                // Find Right Side
//                // Go through pixel rows
//                for (int pColW = cellW - 1; pColW >= 0; --pColW)
//                {
//                    // Go through pixel xolumns
//                    for (int pRowW = 0; pRowW < cellH; ++pRowW)
//                    {
//                        // Get the pixel offsets
//                        int pX = (cellW * cols) + pColW;
//                        int pY = (cellH * rows) + pRowW;
//
//                        // If a non color key pixe is found
//                        if (bitmap->getPixels32(pX, pY) != bgColor)
//                        {
//                            // Set the x offset
//                            mChars[currentChar].w = (pX - mChars[currentChar].x) + 1;
//
//                            // Break the loops
//                            pColW = -1;
//                            pRowW = cellH;
//                        }
//                    }
//                }
//
//                // Find Top
//                // Go through pixel rows
//                for (int pRow = 0; pRow < cellH; ++pRow)
//                {
//                    // Go through pixel collumns
//                    for (int pCol = 0; pCol < cellW; ++pCol)
//                    {
//                        // Get the pixel offsets
//                        int pX = (cellW * cols) + pCol;
//                        int pY = (cellH * rows) + pRow;
//
//                        // If a non color key pixel is found
//                        if (bitmap->getPixels32(pX, pY) != bgColor)
//                        {
//                            // If new top is found
//                            if (pRow < top)
//                            {
//                                top = pRow;
//                            }
//
//                            // Break the loops
//                            pCol = cellW;
//                            pRow = cellH;
//                        }
//                    }
//                }
//
//                // Find bottom of A
//                if (currentChar == 'A')
//                {
//                    // Go through pixel rows
//                    for (int pRow = cellH - 1; pRow >= 0; --pRow)
//                    {
//                        // Go through pixel columns
//                        for (int pCol = 0; pCol < cellW; ++pCol)
//                        {
//                            // Get the pixel offsets
//                            int pX = (cellW * cols) + pCol;
//                            int pY = (cellH * rows) + pRow;
//
//                            // If a non-colorkey pixel is found
//                            if (bitmap->getPixels32(pX, pY) != bgColor)
//                            {
//                                // Bottom of a is found
//                                baseA = pRow;
//
//                                // Break the loops
//                                pCol = cellW;
//                                pRow = -1;
//                            }
//                        }
//                    }
//                }
//
//                // Go to the next character
//                ++currentChar;
//            }
//        }
//
//        // Calculate space
//        mSpace = cellW / 2;
//
//        // Calculate new line
//        mNewLine = baseA - top;
//
//        // Lop off excess top pixels
//        for (int i = 0; i < 256; ++i)
//        {
//            mChars[i].y += top;
//            mChars[i].h -= top;
//        }
//
//        bitmap->unlockTexture();
//        mBitmap = bitmap;
//
//    }
//
//    return success;
//}
//
//void LBitmapFont::renderText(int x, int y, std::string text)
//{
//    // If the font has been built
//    if (mBitmap != NULL)
//    {
//        // Temp offsets
//        int curX = x, curY = y;
//
//        // Go through the text
//        for (int i = 0; i < text.length(); ++i)
//        {
//            // If the current character is a space
//            if (text[i] == ' ')
//            {
//                // Move over
//                curX += mSpace;
//            }
//
//            // If the current character is a newline
//            else if (text[i] == '\n')
//            {
//                // Move down
//                curY += mNewLine;
//
//                // Move back
//                curX = x;
//            }
//
//            else
//            {
//                // Get the ASCII value of the character
//                int ascii = (unsigned char)text[i];
//
//                // Show the character
//                mBitmap->render(curX, curY, &mChars[ascii]);
//
//                // Move over the width of the character with one pixel of padding
//                curX += mChars[ascii].w + 1;
//            }
//        }
//    }
//}
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
//    if (!gFontTexture.loadFromFile("assets/ToniaFont.png"))
//    {
//        printf("Failed to load font texture!\n");
//        success = false;
//    }
//
//    else
//    {
//
//        // Build the font
//        gFont.buildFont(&gFontTexture);
//    }
//
//    return success;
//}
//
//void close()
//{
//    gFontTexture.free();
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
//                std::string str = "Hey Wyatt, I can't wait\n to see you tomorrow\n\n check the symbols -> ";
//                str += 9;
//
//                gFont.renderText(0, 0, str);
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