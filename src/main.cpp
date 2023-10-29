#include <SDL.h>

#include "A_star.h"
#include "Grid.h"
#include "Cell.h"


enum State 
{
    OBSTACLE_SELECTION,
    PATH_PLANNING
};


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


    // grid parameters
    int numRows = 80;
    int numColumns = 80;

    // cell size to fill the window
    int cellSize = 800 / numColumns;

    bool init = false; // false = we haven't initialized yet, yes = we have
    int start_row = 5;
    int start_col = 4;
    int goal_row = 65;
    int goal_col = 70;
    int curr_row = start_row, curr_col = start_col;



    // ------ INITIALIZE PLANNER OBJECTS -------------------------------
    // Define your grid, start point, and goal point
    Grid grid(numRows, numColumns);
    Cell start(start_row, start_col, grid);
    Cell goal(goal_row, goal_col, grid);

    // instance of the AStar class
    AStar a_star(&grid);

    // DEFAULT OBSTACLES
    // Set specific cells as blocked
    for(int i=10; i<35; i++)
    {
        for(int j=10; j<35; j++)
        {
            grid.setCellBlocked(j, i);
        }
    }
    for(int i=45; i<65; i++)
    {
        for(int j=45; j<65; j++)
        {
            grid.setCellBlocked(j, i);
        }
    }

    // ------------------------------------------------------------



    //current state
    State currentState = OBSTACLE_SELECTION;


    //param initialization
    bool quit = false;
    int startCellX = -1;
    int startCellY = -1;
    int endCellX = -1;
    int endCellY = -1;
    bool selecting = false;
    SDL_Event event;
    bool pathFound = false; //true if path has been found

    //main event loop
    while (!quit) 
    {
        // while (SDL_PollEvent(&event)) {
        while (SDL_PollEvent(&event) != 0) 
        {
            if(event.type == SDL_QUIT) 
            {
                quit = true;
            }

            if(currentState == OBSTACLE_SELECTION)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN) 
                {
                    //FOR SINGLE CELL
                    // Handle mouse click events
                    // int x = event.button.x / cellSize;
                    // int y = event.button.y / cellSize;
                    // Toggle the status of the clicked cell
                    // grid.cells[x][y] = !grid.cells[x][y];

                    startCellX = event.button.x / cellSize;
                    startCellY = event.button.y / cellSize;
                    selecting = true;
                } 
                else if(event.type == SDL_MOUSEBUTTONUP) 
                {
                    endCellX = event.button.x / cellSize;
                    endCellY = event.button.y / cellSize;
                    selecting = false;
                } 
                else if(event.type == SDL_MOUSEMOTION && selecting) 
                {
                    // Continuously update the ending cell's coordinates
                    endCellX = event.motion.x / cellSize;
                    endCellY = event.motion.y / cellSize;

                    // Update the grid based on the selection
                    for (int i = std::min(startCellX, endCellX); i <= std::max(startCellX, endCellX); i++) 
                    {
                        for (int j = std::min(startCellY, endCellY); j <= std::max(startCellY, endCellY); j++) 
                        {
                            // Update the grid with true for the selected cells
                            if (i >= 0 && i < numRows && j >= 0 && j < numColumns) 
                            {
                                grid.cells[i][j] = true;
                            }
                        }
                    }
                }

                // go to next state
                if(event.type == SDL_KEYDOWN) 
                {
                    currentState = PATH_PLANNING;
                }
            }
            else if(currentState == PATH_PLANNING)
            {
                cout << "path planning!" << endl;

                // if (!pathFound) {
                //     if (astar.step()) {
                //         // Path found
                //         std::vector<Point> path = astar.getPath();
                //         // Do something with the path
                //         pathFound = true;
                //     }
                // }

            }
        }


        // ------ DRAW BACKGROUND -------------------------------

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

        // ------------------------------------------------------------


        // Blocked cells
        for (int i = 0; i < numRows; i++) 
        {
            for (int j = 0; j < numColumns; j++) 
            {
                if (grid.cells[i][j]) 
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect blockedCell = {i * cellSize, j * cellSize, cellSize, cellSize};
                    SDL_RenderFillRect(renderer, &blockedCell);
                }
            }
        }



        // Current cell
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue (R, G, B, A)
        SDL_Rect currCell = {(curr_col-1) * cellSize, (curr_row-1) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &currCell);

        // Start cell
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); // Blue (R, G, B, A)
        SDL_Rect startCell = {(start_col-1) * cellSize, (start_row-1) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &startCell);

        // Goal cell
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Blue (R, G, B, A)
        SDL_Rect goalCell = {(goal_col-1) * cellSize, (goal_row-1) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &goalCell);

        // Update the screen
        SDL_RenderPresent(renderer);

    }

    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

