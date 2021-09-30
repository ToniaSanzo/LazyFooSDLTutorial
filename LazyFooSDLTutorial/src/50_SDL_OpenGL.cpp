/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, OpenGL, and iostream
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
using namespace std;

int main(int argc, char* argv[])
{
    // Create a window data type this pointer will point to the window that is allocated
    // from SDL_CreateWindow
    SDL_Window* window = nullptr;

    // Initialize the video subsystem. If it returns less than 1 print the error code.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialize " << SDL_GetError();
        return 1;
    }
    else
    {
        cout << "SDL video system's initialized.\n";
    }

    // Before we create our window, specify OpenGL version: 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // We want the core profile. This set's the OpenGL attributes to match the Glad generated header.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Window is essentially updating twice as often
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);     // and has 24-bits for the color.


    // Request a window to be created for our platform the paramters are for the title, x and y
    // position, and the width and height of the window.
    window = SDL_CreateWindow
    (
        "SDL/OpenGL Window",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        1200, 
        650,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    // Create the OpenGL context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        cout << "OpenGL failed to create context " << SDL_GetError();
        return 1;
    }
    else
    {
        cout << "OpenGL context created.\n";
    }

    // Setup our function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    // Infinite loop for out application
    bool gameIsRunning = true;
    while (gameIsRunning)
    {
        glViewport(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 650);

        SDL_Event event;
        // Start out event loop
        while (SDL_PollEvent(&event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                cout << "mouse moved\n";
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_0)
                {
                    cout << "0 pressed\n";
                }
                else
                {
                    cout << "0 wasn't pressed\n";
                }
            }
            // Retrieve the state of all the keys then we can query the scan code of one or more keys
            // at a time.
            const Uint8* state = SDL_GetKeyboardState(nullptr);
            if (state[SDL_SCANCODE_RIGHT])
            {
                cout << "right arrow key is pressed\n";
            }
        }

        // Set the background color to: 
        glClearColor(.2f, .6f, .7f, 1.f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);

    }

    // We destroy our window. We are passing in the pointer that points to the memory allocated by the
    // 'SDL_CreateWindow' function. Remember, this is a 'C-style' API, we don't have destructors
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
    return 0;
}