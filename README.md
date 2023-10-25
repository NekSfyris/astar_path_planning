# grid_path_planning
bla bla

## Install
Install the Simple DirectMedia Layer (SDL) library on Linux:
sudo apt-get update
sudo apt-get install libsdl2-2.0
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev


## Build
mkdir build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make


## Run
Compile the code with C++ compiler:
g++ -o sdl_test1 sdl_test1.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image
g++ -o sdl_test2 sdl_test2.cpp -I/usr/include/SDL2 -lSDL2

Then run the executable:
./sdl_test1


To run the project executable after building:
cd bin
./YourProjectName



## Setup

### Python3 Virtual Environment

Install what you need with:
- sudo apt-get install python3-pip
- sudo pip3 install virtualenv 

Go in the project folder you are interested in creating the python environment:
-cd ~/Desktop/auto_trading

Create virtualenv using Python3:
- virtualenv -p python3 venv

Active your virtual environment:    
- source venv/bin/activate
    
To deactivate:
- deactivate




