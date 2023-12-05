#include <SDL.h>

#include "A_star.h"
#include "Grid.h"
#include "Cell.h"
#include "utils.h"


int main(int argc, char* argv[]) 
{


    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create a window
    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create a renderer
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

    int start_row = 5;
    int start_col = 5;
    int goal_row = 65;
    int goal_col = 65;


    // ------ INITIALIZE PLANNER OBJECTS -------------------------------
    // define your grid, start point, and goal point
    Grid grid(numRows, numColumns);
    Cell start(start_row, start_col, numRows, numColumns);
    Cell goal(goal_row, goal_col, numRows, numColumns);

    // instance of the AStar class
    AStar a_star(&grid);

    // DEFAULT OBSTACLES
    // set specific cells as blocked
    // for(int i=15; i<25; i++)
    // {
    //     for(int j=15; j<25; j++)
    //     {
    //         grid.setCellBlocked(j, i);
    //     }
    // }
    // for(int i=45; i<55; i++)
    // {
    //     for(int j=45; j<55; j++)
    //     {
    //         grid.setCellBlocked(j, i);
    //     }
    // }

    // ------------------------------------------------------------



    // current state
    SDLState currentState = OBSTACLE_SELECTION;


    // param initialization
    SDL_Event event;
    int startCellX = -1;
    int startCellY = -1;
    int endCellX = -1;
    int endCellY = -1;
    bool selecting = false; // flag for selecting multiple cells for obstacles
    bool quit = false; // flag to quit
    bool state_msg = false; // flag to give user a message based on the state
    bool path_found = false; // flag to check if we need to paint pthe final path to goal

    std::vector<Cell> path_to_goal; // if we find a path to goal, store it here

    // frame rate control
    const int FPS = 45;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;

    // main event loop
    while (!quit) 
    {

        // initial frame time
        frameStart = SDL_GetTicks();

        // while (SDL_PollEvent(&event)) {
        while(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_QUIT) 
            {
                quit = true;
            }

            // we always initiate the process with the OBSTACLE_SELECTION state
            if(currentState == OBSTACLE_SELECTION)
            {

                // print user msg
                if(state_msg == false)
                {
                    cout << "#####-----------------------------------------#####" << endl << endl;
                    cout << "Select with your mouse more obstacles in the grid!" << endl;
                    cout << "When you are done, press any key to do path-planning!" << endl;
                    state_msg = true;
                }

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


                    // speciy the selected cells as blocked
                    for(int i = startCellX; i <= endCellX; i++) 
                    {
                        for(int j = startCellY; j <= endCellY; j++) 
                        {
                            grid.setCellBlocked(j, i);
                        }
                    }

                } 
                else if(event.type == SDL_MOUSEMOTION && selecting) 
                {
                    // continuously update the ending cell's coordinates
                    endCellX = event.motion.x / cellSize;
                    endCellY = event.motion.y / cellSize;

                    // Update the grid based on the selection
                    for(int i = std::min(startCellX, endCellX); i <= std::max(startCellX, endCellX); i++) 
                    {
                        for(int j = std::min(startCellY, endCellY); j <= std::max(startCellY, endCellY); j++) 
                        {
                            // Update the grid with true for the selected cells
                            if (i >= 0 && i < numRows && j >= 0 && j < numColumns) 
                            {
                                grid.cells[j][i] = true;
                            }
                        }
                    }
                }

                // go to next state
                if(event.type == SDL_KEYDOWN) 
                {
                    currentState = PATH_PLANNING;
                    state_msg = false; // make it false so we print msg in next state
                }
            }
        }


        // do the path planning. This state does not have any dependency on SDL events
        if(currentState == PATH_PLANNING)
        {

            // action based on state of the path planner
            if(a_star.astarState == INIT)
            {
                cout << a_star.planner_output[a_star.astarState] << endl;

                // initialize path planning
                a_star.initPlanner(start, goal);
            }
            else if(a_star.astarState == FINISH)
            {
                // cout << a_star.planner_output[a_star.astarState] << endl;
                continue;
            }
            else
            {

                // do one step of the planner
                a_star.step(goal);

                if(a_star.astarState != EXPLORING)
                {
                    cout << a_star.planner_output[a_star.astarState] << endl;
                }

                if(a_star.astarState == NO_PATH)
                {
                    // change state to the final one
                    a_star.astarState = FINISH;
                }
                else if(a_star.astarState == PATH_FOUND)
                {
                    // path found, store it
                    // path_to_goal = a_star.getPath();
                    
                    // we use this to plot the path
                    path_found = true;

                    // change state to the final one
                    a_star.astarState = FINISH;
                }
            }
        }



        // ------ DRAW BACKGROUND -------------------------------

        // clear the renderer with a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White (R, G, B, A)
        SDL_RenderClear(renderer);

        // render the grid
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black grid lines (R, G, B, A)

        // draw horizontal grid lines
        for (int i = 0; i <= numRows; i++) 
        {
            SDL_RenderDrawLine(renderer, 0, i * cellSize, numColumns * cellSize, i * cellSize);
        }

        // draw vertical grid lines
        for (int j = 0; j <= numColumns; j++) 
        {
            SDL_RenderDrawLine(renderer, j * cellSize, 0, j * cellSize, numRows * cellSize);
        }

        // ------ DRAW CELLS -------------------------------------


        // blocked cells
        for (int i = 0; i < numRows; i++) 
        {
            for (int j = 0; j < numColumns; j++) 
            {
                if (grid.cells[i][j]) 
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect blockedCell = {j * cellSize, i * cellSize, cellSize, cellSize};
                    SDL_RenderFillRect(renderer, &blockedCell);
                }
            }
        }


        // cells in openList
        for(Node& openNode : a_star.openList) 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 192, 0); // Yellow (R, G, B, A)
            SDL_Rect openCell = {(openNode.col) * cellSize, (openNode.row) * cellSize, cellSize, cellSize};
            SDL_RenderFillRect(renderer, &openCell);
        }


        // cells in closedList
        for(Node& closedNode : a_star.closedList) 
        {
            SDL_SetRenderDrawColor(renderer, 192, 192, 192, 0); // Grey (R, G, B, A)
            SDL_Rect closedCell = {(closedNode.col) * cellSize, (closedNode.row) * cellSize, cellSize, cellSize};
            SDL_RenderFillRect(renderer, &closedCell);
        }


        // current cell
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 0); // Grey (R, G, B, A)
        // SDL_Rect currentCell = {(a_star.currNode.col) * cellSize, (a_star.currNode.row) * cellSize, cellSize, cellSize};
        SDL_Rect currentCell = {(a_star.currNode_ptr->col) * cellSize, (a_star.currNode_ptr->row) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &currentCell);
        

        // SDL_SetRenderDrawColor(renderer, 192, 192, 192, 0); // Grey (R, G, B, A)
        // SDL_SetRenderDrawColor(renderer, 255, 255, 192, 0); // Yellow (R, G, B, A)

        // if we found path, plot it
        if(path_found==true)
        {
            for(int i=0; i<path_to_goal.size(); i++)
            {
                cout << "drawing the path"<< endl;
                // SDL_SetRenderDrawColor(renderer, 176, 25, 218, 0); // Purple (R, G, B, A)
                // SDL_Rect pathCell = {(path_to_goal[i].col) * cellSize, (path_to_goal[i].row) * cellSize, cellSize, cellSize};
                // SDL_RenderFillRect(renderer, &pathCell);    
            }        
        }

        // cout << path_to_goal.size()<< endl;

        // start cell
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); // Green (R, G, B, A)
        SDL_Rect startCell = {(start_col) * cellSize, (start_row) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &startCell);

        // goal cell
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Red (R, G, B, A)
        SDL_Rect goalCell = {(goal_col) * cellSize, (goal_row) * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &goalCell);


        // frame rate control with defined FPS
        int frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < frameDelay) 
        {
            SDL_Delay(frameDelay - frameTime);
        }

        // update the screen
        SDL_RenderPresent(renderer);

    }

    // cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

