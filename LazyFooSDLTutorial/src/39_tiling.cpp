/*
* author: Tonia Sanzo
*
* Lesson 39: Tiling
*/
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <string>
//#include <fstream>
//// Screen dimension constants
//const int SCREEN_WIDTH  = 1280;
//const int SCREEN_HEIGHT = 700;
//
//// The level dimensions, 12 x 10 Tile Map
//const int LEVEL_WIDTH  = 3072 * 3;
//const int LEVEL_HEIGHT = 2560 * 3;
//
//// Tile constants
//const int TILE_WIDTH  = 256;
//const int TILE_HEIGHT = 256;
//const int TOTAL_TILES = 120;
//const int TOTAL_TILE_SPRITES = 12;
//
//// Knight constants
//const int TOTAL_KNIGHT_SPRITES = 4;
//
//// The different tile sprites
//const int TILE_GRASS    = 0;
//const int TILE_TOPLEFT  = 1;
//const int TILE_TOP      = 2;
//const int TILE_TOPRIGHT = 3;
//const int TILE_FOREST   = 4;
//const int TILE_LEFT     = 5;
//const int TILE_CENTER   = 6;
//const int TILE_RIGHT    = 7;
//const int TILE_MOUNTAIN = 8;
//const int TILE_BOTLEFT  = 9;
//const int TILE_BOT      = 10;
//const int TILE_BOTRIGHT = 11;
//
//// Renderer and window to render too
//SDL_Renderer *gRenderer = nullptr;
//SDL_Window *gWindow     = nullptr;
//
//// Texture wrapper class
//class UTexture {
//
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
//    // Creates image from font string
//    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
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
//    // Initialize UTexture
//    void initUTexture(SDL_Renderer *rend);
//
//    // Gets image dimensions
//    int getWidth();
//    int getHeight();
//    int getScale();
//
//    // Set image scale
//    void updateScale(double sc);
//private:
//    // The actual hardware texture, and the games renderer
//    SDL_Texture *mTexture;
//
//    // Image dimesnions
//    int mWidth, mHeight;
//    double mScale;
//};
//
//// UTexture constructor
//UTexture::UTexture() {
//    // Initialize
//    mTexture = NULL;
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
//    // Exit prematuraly if UTexture has not been properly initialized
//    if (!gRenderer) {
//        printf("Attempted to render a texture without initializing a renderer!\n");
//        return false;
//    }
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
//// initialize UTexture with a renderer
//void UTexture::initUTexture(SDL_Renderer *rend) {
//    gRenderer = rend;
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
//// The textures, and the sprite clips for each of the textures
//UTexture gTileTexture, gKnightTexture;
//SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
//SDL_Rect gKnightClips[TOTAL_KNIGHT_SPRITES];
//
////The tile
//class Tile {
//public:
//    //Initializes position and type
//    Tile(int x, int y, int tileType);
//
//    //Shows the tile
//    void render(SDL_Rect &camera);
//
//    //Get the tile type
//    int getType();
//
//    //Get the collision box
//    SDL_Rect getBox();
//
//private:
//    //The attributes of the tile
//    SDL_Rect mBox;
//
//    //The tile type
//    int mType;
//};
//
//// The knight that will move around on the screen
//class Knight {
//public:
//    // The dimensions of the knight
//    static const int KNIGHT_HEIGHT = 128;
//    static const int KNIGHT_WIDTH  = 128;
//
//    // Maximum axis veloicty of the knight
//    static const int KNIGHT_VEL = 9;
//
//    // Initializes the variables
//    Knight();
//
//    // Takes key presses and adjusts the knight's velocity
//    void handleEvent(SDL_Event &e);
//
//    // Moves the knight and check collision against tiles
//    void move(Tile *tiles[]);
//
//    // Center's the camera over the knight
//    void setCamera(SDL_Rect &camera);
//
//    // draw the knight on the screen
//    void render(SDL_Rect &camera);
//
//private:
//    // Collision box of the knight
//    SDL_Rect mBox;
//
//    // The velocity of the knight
//    int mVelX, mVelY;
//    SDL_RendererFlip flipFlag = SDL_FLIP_NONE;
//    Uint32 pTime;
//    int cFrame;
//};
//
////Starts up SDL and creates window
//bool init();
//
////Loads media
//bool loadMedia(Tile *tiles[]);
//
////Frees media and shuts down SDL
//void close(Tile *tiles[]);
//
////Box collision detector
//bool checkCollision(SDL_Rect a, SDL_Rect b);
//
////Checks collision box against set of tiles
//bool touchesWall(SDL_Rect box, Tile *tiles[]);
//
////Sets tiles from tile map
//bool setTiles(Tile *tiles[]);
//
//Tile::Tile(int x, int y, int tileType) {
//    // Get the offsets
//    mBox.x = x;
//    mBox.y = y;
//
//    // Set the collision box
//    mBox.w = TILE_WIDTH * 3;
//    mBox.h = TILE_HEIGHT * 3;
//
//    // Get the tile type
//    mType = tileType;
//}
//
//void Tile::render(SDL_Rect &camera) {
//    //If the tile is on screen
//    if (checkCollision(camera, mBox))
//    {
//        //Show the tile
//        gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
//    }
//}
//
//int Tile::getType() {
//    return mType;
//}
//
//SDL_Rect Tile::getBox() {
//    return mBox;
//}
//
//Knight::Knight()
//{
//    // Initialize the collision box
//    mBox.x = 4500;
//    mBox.y = 4500;
//    mBox.w = KNIGHT_WIDTH;
//    mBox.h = KNIGHT_HEIGHT;
//
//    // Initialize the velocity
//    mVelX = 0;
//    mVelY = 0;
//
//    pTime = SDL_GetTicks();
//    cFrame = 0;
//}
//
//void Knight::handleEvent(SDL_Event &e) 
//{
//    //If a key was pressed
//    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//    {
//        //Adjust the velocity
//        switch (e.key.keysym.sym)
//        {
//        case SDLK_UP: mVelY -= KNIGHT_VEL; break;
//        case SDLK_DOWN: mVelY += KNIGHT_VEL; break;
//        case SDLK_LEFT: mVelX -= KNIGHT_VEL; break;
//        case SDLK_RIGHT: mVelX += KNIGHT_VEL; break;
//        }
//    }
//    //If a key was released
//    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
//    {
//        //Adjust the velocity
//        switch (e.key.keysym.sym)
//        {
//        case SDLK_UP: mVelY += KNIGHT_VEL; break;
//        case SDLK_DOWN: mVelY -= KNIGHT_VEL; break;
//        case SDLK_LEFT: mVelX += KNIGHT_VEL; break;
//        case SDLK_RIGHT: mVelX -= KNIGHT_VEL; break;
//        }
//    }
//}
//
//void Knight::move(Tile *tiles[])
//{
//
//    if (mVelX < 0) 
//    {
//        flipFlag = SDL_FLIP_HORIZONTAL;
//    }
//    else if (mVelX > 0)
//    {
//        flipFlag = SDL_FLIP_NONE;
//    }
//
//    //Move the dot left or right
//    mBox.x += mVelX;
//
//    //If the dot went too far to the left or right or touched a wall
//    if ((mBox.x < 0) || (mBox.x + KNIGHT_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) 
//    {
//        //move back
//        mBox.x -= mVelX;
//    }
//
//    //Move the dot up or down
//    mBox.y += mVelY;
//
//    //If the dot went too far up or down or touched a wall
//    if ((mBox.y < 0) || (mBox.y + KNIGHT_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles)) 
//    {
//        //move back
//        mBox.y -= mVelY;
//    }
//}
//
//void Knight::setCamera(SDL_Rect &camera)
//{
//    //Center the camera over the dot
//    camera.x = (mBox.x + KNIGHT_WIDTH / 2) - SCREEN_WIDTH / 2;
//    camera.y = (mBox.y + KNIGHT_HEIGHT / 2) - SCREEN_HEIGHT / 2;
//
//    //Keep the camera in bounds
//    if (camera.x < 0)
//    {
//        camera.x = 0;
//    }
//    if (camera.y < 0)
//    {
//        camera.y = 0;
//    }
//    if (camera.x > LEVEL_WIDTH - camera.w)
//    {
//        camera.x = LEVEL_WIDTH - camera.w;
//    }
//    if (camera.y > LEVEL_HEIGHT - camera.h)
//    {
//        camera.y = LEVEL_HEIGHT - camera.h;
//    }
//}
//
//void Knight::render(SDL_Rect &camera)
//{
//    // If the knight is not in motion
//    if (!mVelX && !mVelY)
//    {
//        // Update the frame every second
//        if ((SDL_GetTicks() - pTime) > 1000) {
//            cFrame = (cFrame + 1) % 2;
//            pTime = SDL_GetTicks();
//        }
//        
//        //Show the knight
//        gKnightTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gKnightClips[cFrame], 0, nullptr, flipFlag);
//    }
//    else {
//        // Update the frame every 1/4 second
//        if ((SDL_GetTicks() - pTime) > 250) {
//            cFrame = (cFrame + 1) % 2;
//            pTime = SDL_GetTicks();
//        }
//
//        //Show the knight
//        gKnightTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gKnightClips[cFrame + 2], 0, nullptr, flipFlag);
//    }
//
//}
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
//bool loadMedia(Tile *tiles[])
//{
//    //Loading success flag
//    bool success = true;
//
//    //Load knight texture
//    if (!gKnightTexture.loadFromFile("assets/knight.png"))
//    {
//        printf("Failed to load knight texture!\n");
//        success = false;
//    }
//    else
//    {
//        gKnightTexture.updateScale(2);
//
//        gKnightClips[0] = SDL_Rect{ 0, 0, 64, 64 };
//        gKnightClips[1] = SDL_Rect{ 64, 0, 64, 64 };
//        gKnightClips[2] = SDL_Rect{ 0, 64, 64, 64 };
//        gKnightClips[3] = SDL_Rect{ 64, 64, 64, 64 };
//    }
//
//    //Load tile texture
//    if (!gTileTexture.loadFromFile("assets/map_tiles.png"))
//    {
//        printf("Failed to load tile set texture!\n");
//        success = false;
//    }
//    else
//    {
//        gTileTexture.updateScale(3);
//    }
//
//    //Load tile map
//    if (!setTiles(tiles))
//    {
//        printf("Failed to load tile set!\n");
//        success = false;
//    }
//
//    return success;
//}
//
//bool setTiles(Tile *tiles[])
//{
//    // Success flag
//    bool tilesLoaded = true;
//
//    // The tile offsets
//    int x = 0, y = 0;
//
//    // Open the map
//    std::ifstream map("assets/land.map");
//
//    // If the map couldn't be loaded
//    if (map.fail())
//    {
//        printf("Unable to load map file!\n");
//        tilesLoaded = false;
//    }
//    else
//    {
//        //Initialize the tiles
//        for (int i = 0; i < TOTAL_TILES; ++i)
//        {
//            //Determines what kind of tile will be made
//            int tileType = -1;
//
//            //Read tile from map file
//            map >> tileType;
//
//            //If the was a problem in reading the map
//            if (map.fail())
//            {
//                //Stop loading map
//                printf("Error loading map: Unexpected end of file!\n");
//                tilesLoaded = false;
//                break;
//            }
//
//            //If the number is a valid tile number
//            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
//            {
//                tiles[i] = new Tile(x, y, tileType);
//            }
//            //If we don't recognize the tile type
//            else
//            {
//                //Stop loading map
//                printf("Error loading map: Invalid tile type at %d!\n", i);
//                tilesLoaded = false;
//                break;
//            }
//            //Move to next tile spot
//            x += TILE_WIDTH * 3;
//
//            //If we've gone too far
//            if (x >= LEVEL_WIDTH)
//            {
//                //Move back
//                x = 0;
//
//                //Move to the next row
//                y += TILE_HEIGHT * 3;
//            }
//        }
//
//        //Clip the sprite sheet
//        if (tilesLoaded)
//        {
//            gTileClips[TILE_GRASS].x = 0;
//            gTileClips[TILE_GRASS].y = 0;
//            gTileClips[TILE_GRASS].w = 256;
//            gTileClips[TILE_GRASS].h = 256;
//
//            gTileClips[TILE_TOPLEFT].x = 256;
//            gTileClips[TILE_TOPLEFT].y = 0;
//            gTileClips[TILE_TOPLEFT].w = 256;
//            gTileClips[TILE_TOPLEFT].h = 256;
//
//            gTileClips[TILE_TOP].x = 512;
//            gTileClips[TILE_TOP].y = 0;
//            gTileClips[TILE_TOP].w = 256;
//            gTileClips[TILE_TOP].h = 256;
//
//            gTileClips[TILE_TOPRIGHT].x = 768;
//            gTileClips[TILE_TOPRIGHT].y = 0;
//            gTileClips[TILE_TOPRIGHT].w = 256;
//            gTileClips[TILE_TOPRIGHT].h = 256;
//
//            gTileClips[TILE_FOREST].x = 0;
//            gTileClips[TILE_FOREST].y = 256;
//            gTileClips[TILE_FOREST].w = 256;
//            gTileClips[TILE_FOREST].h = 256;
//
//            gTileClips[TILE_LEFT].x = 256;
//            gTileClips[TILE_LEFT].y = 256;
//            gTileClips[TILE_LEFT].w = 256;
//            gTileClips[TILE_LEFT].h = 256;
//
//            gTileClips[TILE_CENTER].x = 512;
//            gTileClips[TILE_CENTER].y = 256;
//            gTileClips[TILE_CENTER].w = 256;
//            gTileClips[TILE_CENTER].h = 256;
//
//            gTileClips[TILE_RIGHT].x = 768;
//            gTileClips[TILE_RIGHT].y = 256;
//            gTileClips[TILE_RIGHT].w = 256;
//            gTileClips[TILE_RIGHT].h = 256;
//
//            gTileClips[TILE_MOUNTAIN].x = 0;
//            gTileClips[TILE_MOUNTAIN].y = 512;
//            gTileClips[TILE_MOUNTAIN].w = 256;
//            gTileClips[TILE_MOUNTAIN].h = 256;
//
//            gTileClips[TILE_BOTLEFT].x = 256;
//            gTileClips[TILE_BOTLEFT].y = 512;
//            gTileClips[TILE_BOTLEFT].w = 256;
//            gTileClips[TILE_BOTLEFT].h = 256;
//
//            gTileClips[TILE_BOT].x = 512;
//            gTileClips[TILE_BOT].y = 512;
//            gTileClips[TILE_BOT].w = 256;
//            gTileClips[TILE_BOT].h = 256;
//
//            gTileClips[TILE_BOTRIGHT].x = 768;
//            gTileClips[TILE_BOTRIGHT].y = 512;
//            gTileClips[TILE_BOTRIGHT].w = 256;
//            gTileClips[TILE_BOTRIGHT].h = 256;
//        }
//    }
//
//    //Close the file
//    map.close();
//
//    //If the map was loaded fine
//    return tilesLoaded;
//}
//
//bool touchesWall(SDL_Rect box, Tile *tiles[])
//{
//    //Go through the tiles
//    for (int i = 0; i < TOTAL_TILES; ++i)
//    {
//        //If the tile is a wall type tile
//        if (tiles[i]->getType() != TILE_GRASS && tiles[i]->getType() != TILE_FOREST)
//        {
//            //If the collision box touches the wall tile
//            if (checkCollision(box, tiles[i]->getBox()))
//            {
//                return true;
//            }
//        }
//    }
//
//    //If no wall tiles were touched
//    return false;
//}
//
//bool checkCollision(SDL_Rect a, SDL_Rect b)
//{
//    //The sides of the rectangles
//    int leftA, leftB;
//    int rightA, rightB;
//    int topA, topB;
//    int bottomA, bottomB;
//
//    //Calculate the sides of rect A
//    leftA = a.x;
//    rightA = a.x + a.w;
//    topA = a.y;
//    bottomA = a.y + a.h;
//
//    //Calculate the sides of rect B
//    leftB = b.x;
//    rightB = b.x + b.w;
//    topB = b.y;
//    bottomB = b.y + b.h;
//
//    //If any of the sides from A are outside of B
//    if (bottomA <= topB)
//    {
//        return false;
//    }
//
//    if (topA >= bottomB)
//    {
//        return false;
//    }
//
//    if (rightA <= leftB)
//    {
//        return false;
//    }
//
//    if (leftA >= rightB)
//    {
//        return false;
//    }
//
//    //If none of the sides from A are outside B
//    return true;
//}
//
//void close(Tile *tiles[])
//{
//    //Deallocate tiles
//    for (int i = 0; i < TOTAL_TILES; ++i)
//    {
//        if (tiles[i] != NULL)
//        {
//            delete tiles[i];
//            tiles[i] = NULL;
//        }
//    }
//
//    //Free loaded images
//    gKnightTexture.free();
//    gTileTexture.free();
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
//        //The level tiles
//        Tile *tileSet[TOTAL_TILES];
//
//        //Load media
//        if (!loadMedia(tileSet))
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
//            //The knight that will be moving around on the screen
//            Knight knight;
//
//            //Level camera
//            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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
//                    //Handle input for the dot
//                    knight.handleEvent(e);
//                }
//
//                //Move the dot
//                knight.move(tileSet);
//                knight.setCamera(camera);
//
//                //Clear screen
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//                //Render level
//                for (int i = 0; i < TOTAL_TILES; ++i)
//                {
//                    tileSet[i]->render(camera);
//                }
//
//                //Render dot
//                knight.render(camera);
//
//                //Update screen
//                SDL_RenderPresent(gRenderer);
//            }
//        }
//
//        //Free resources and close SDL
//        close(tileSet);
//    }
//
//    return 0;
//}