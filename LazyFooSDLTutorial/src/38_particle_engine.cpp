/*
* author: Tonia Sanzo
*
* Lesson 38: Particle Engine
*/
// Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

// Particle count
const int TOTAL_PARTICLES = 20;
class LTexture;

class Particle {
public:
    // Initialize position and animation
    Particle(int x, int y);

    // Shows the particle
    void render();

    // Checks if particle is dead
    bool isDead();

private:
    // Offsets
    int mPosX, mPosY;

    // Current frame of animation
    int mFrame;

    // Type of particle
    LTexture *mTexture;
};

// Texture wrapper class
class LTexture {
public:
    // Initialize variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Creates image from font string
    //bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

    // Deallocates texture
    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

    // Gets image dimensions
    int getWidth();
    int getHeight();
    int getScale();

    // Set image scale
    void updateScale(int sc);
private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
    int scale;
};

// The dot that will move around the screen
class Dot {
public:
    // The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    // Maximum axis velocity of the dot
    static const int DOT_VEL = 1;

    // Initializes the variables and allocates particles
    Dot(int x, int y);

    // Destructor for the Dot
    ~Dot();

    // Takes key presses and adjusts the box velocity
    void handleEvent(SDL_Event &e);

    // Moves the dot and checks collision
    void move();

    // Shows the dot on the screen
    void render();

private:
    // The X and Y offsets of the dot
    int mX, mY;

    // The velocity of the dot
    int mVelX, mVelY;

    // The particles
    Particle *particles[TOTAL_PARTICLES];

    // Shows the particles
    void renderParticles();
};

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Rendered texture
LTexture gDotTexture, gATexture, gBTexture, gCTexture, gShimmerTexture;

// Screen dimensions
const int SCREEN_WIDTH = 1220;
const int SCREEN_HEIGHT = 900;


// LTexture constructor
LTexture::LTexture() {
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    scale = 1;
}

// LTexture destructor
LTexture::~LTexture() {
    // Deallocate texture
    free();
}

// Sets LTextures render scale
void LTexture::updateScale(int sc) {
    scale = sc;
    mWidth *= sc;
    mHeight *= sc;
}

// Load Texture from a file
bool LTexture::loadFromFile(std::string path) {
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
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

// Deallocate the texture
void LTexture::free() {
    // Free texture if it exists
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

// Define whether this texture can blend
void LTexture::setBlendMode(SDL_BlendMode blending) {
    // Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

// Define the texture's opacity
void LTexture::setAlpha(Uint8 alpha) {
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

// Modulate the texture's color
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // Modulate texture
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

// Render texture
void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    // Set Rendering space and render to screen
    SDL_Rect renderQuad = { x - (mWidth / 2) , y - (mHeight / 2), mWidth * scale, mHeight * scale };

    // Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w * scale;
        renderQuad.h = clip->h * scale;
    }

    // Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

// Getters for height, width, and scale
int LTexture::getHeight() { return mHeight; }
int LTexture::getWidth() { return mWidth; }
int LTexture::getScale() { return scale; }

Dot::Dot(int x, int y) {
    // Initializes the offsets
    mX = x;
    mY = y;

    // Initialize the velocity
    mVelX = mVelY = 0;

    // Initialize particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i] = new Particle(mX, mY);
    }
}

Dot::~Dot() {
    // Delete particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        delete particles[i];
    }
}

void Dot::renderParticles() {
    // Go through particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        // Delete and replace dead particles
        if (particles[i]->isDead()) {
            delete particles[i];
            particles[i] = new Particle(mX, mY);
        }
    }

    // Show particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        particles[i]->render();
    }
}

void Dot::handleEvent(SDL_Event &e) {
    // If a key was pressed 
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity and radians
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            mVelY -= DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        default:;   /* null */
        }
    }
}

void Dot::move() {
    mX += mVelX;
    mY += mVelY;

    // Keep the dot within the horizontal bounds
    if (mX < 0) {
        mX = mVelX = 0;
    }
    else if (mX + (gDotTexture.getWidth() / 2) > SCREEN_WIDTH ){
        mX = SCREEN_WIDTH - gDotTexture.getWidth() / 2;
        mVelX = 0;
    }

    // Keep the dot with the vertical bounds
    if (mY < 0) {
        mY = mVelY = 0;
    }
    else if (mY + (gDotTexture.getHeight() / 2) > SCREEN_HEIGHT) {
        mY = SCREEN_HEIGHT - gDotTexture.getHeight() / 2;
        mVelY = 0;
    }

}

void Dot::render() {
    // Show the dot
    gDotTexture.render(mX, mY);

    // Show particles on top of dot
    renderParticles();
}

Particle::Particle(int x, int y) {
    // Set offsets
    mPosX = ((x - gDotTexture.getWidth() / 2) - 60) + (rand() % gDotTexture.getWidth() + 70);
    mPosY = ((y - gDotTexture.getHeight() / 2) - 60) + (rand() % gDotTexture.getHeight() + 70);

    // Initialize animation
    mFrame = rand() % 5;

    // Set type
    switch (rand() % 3) {
    case 0: mTexture = &gATexture; break;
    case 1: mTexture = &gBTexture; break;
    default: mTexture = &gCTexture; break;
    }
}

void Particle::render() {
    // Show image
    mTexture->render(mPosX, mPosY);

    // Show shimmer
    if (mFrame % 2 == 0) {
        gShimmerTexture.render(mPosX, mPosY);
    }

    // Animate
    mFrame++;
}

bool Particle::isDead() {
    return mFrame > 10;
}

// Initialize the SDL subsystems
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

                // Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load dot texture
    if (!gDotTexture.loadFromFile("assets/angel.png")) {
        printf("Failed to load fireball texture image!\n");
        success = false;
    }

    // Load texture a
    if (!gATexture.loadFromFile("assets/spark_a.png")) {
        printf("Failed to load spark_a.png texture image!\n");
        success = false;
    }

    // Load texture b
    if (!gBTexture.loadFromFile("assets/spark_b.png")) {
        printf("Failed to load spark_b.png texture image!\n");
        success = false;
    }

    // Load texture c
    if (!gATexture.loadFromFile("assets/spark_c.png")) {
        printf("Failed to load spark_c.png texture image!\n");
        success = false;
    }

    // Load shimmer texture
    if (!gShimmerTexture.loadFromFile("assets/shimmer.png")) {
        printf("Failed to load shimmer.png texture image!\n");
        success = false;
    }

    // Set texture transparency
    gATexture.setAlpha(192);
    gBTexture.setAlpha(192);
    gCTexture.setAlpha(192);
    gShimmerTexture.setAlpha(192);

    return success;
}

void close() {
    // Free loaded images
    gDotTexture.free();
    gATexture.free();
    gBTexture.free();
    gCTexture.free();
    gShimmerTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // The dot we will move
            Dot dot(10, 10);

            // While application is running
            while (!quit)
            {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    // handle input for the dot
                    dot.handleEvent(e);
                }

                // move the dot
                dot.move();

                // Clear screen, to white
                SDL_SetRenderDrawColor(gRenderer, 125, 125, 125, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render screen
                dot.render();

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}