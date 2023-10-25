#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Simple Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load an image (you should have "rectangle.png" in the same directory)
    SDL_Surface* imageSurface = IMG_Load("rectangle.png");
    if (imageSurface == nullptr) {
        SDL_Log("Image could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    // Initial position of the rectangle
    int rectX = 0;
    int rectY = 100;
    
    // Animation loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the rectangle
        SDL_Rect rectDst = {rectX, rectY, 64, 64}; // Width and height of the rectangle
        SDL_RenderCopy(renderer, texture, NULL, &rectDst);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Move the rectangle horizontally
        rectX += 2;

        // Control animation speed
        SDL_Delay(16); // Approximately 60 frames per second
    }

    // Cleanup and quit
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
