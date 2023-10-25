#include <SDL.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
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

    // Define grid parameters
    int numRows = 80;
    int numColumns = 80;

    // Calculate cell size to fill the window
    int cellSize = 800 / numColumns;

    // Main event loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer with a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White (R, G, B, A)
        SDL_RenderClear(renderer);

        // Render the grid
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black grid lines (R, G, B, A)

        // Draw horizontal grid lines
        for (int i = 0; i <= numRows; i++) {
            SDL_RenderDrawLine(renderer, 0, i * cellSize, numColumns * cellSize, i * cellSize);
        }

        // Draw vertical grid lines
        for (int j = 0; j <= numColumns; j++) {
            SDL_RenderDrawLine(renderer, j * cellSize, 0, j * cellSize, numRows * cellSize);
        }

        // Fill specific cells with color
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue (R, G, B, A)
        SDL_Rect blueCell = {4 * cellSize, 3 * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &blueCell);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
