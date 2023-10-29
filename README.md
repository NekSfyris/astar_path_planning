# path_planning
A collection of path planning algorithms. 

## Install
Install the Simple DirectMedia Layer (SDL) library on Linux:
```
sudo apt-get update
sudo apt-get install libsdl2-2.0
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
```

## Build
While being inside the project folder:
```
mkdir build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
```

## Run
Compile the code with C++ compiler:
```
g++ -o sdl_test1 sdl_test1.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image
g++ -o sdl_test2 sdl_test2.cpp -I/usr/include/SDL2 -lSDL2
```

Then run the executable:
```
./sdl_test1
```

To run the project executable after building:
```
cd build
./path_planning
```




