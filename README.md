# Roadrolla' #
Roadrolla is an OpenGL 1.1 based 'game', originally created in 2011 as a homework for a [course](https://portal.vik.bme.hu/kepzes/targyak/VIIIAB03/en/).

## Dependencies ##
* [CMake](https://cmake.org/) 3.23 or newer
* [freeglut](http://freeglut.sourceforge.net/)
* [vcpkg](https://vcpkg.io) on Windows

## System Requirements ##
* OpenGL 1.1 compatible video card (any video chip released after 1999 😂)

## Summary of set up
* `git clone git@github.com:laszlolukacs/roadrolla-gl.git`
* `cd ./roadrolla-gl`
* Windows:
    + [Install vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-msbuild?pivots=shell-powershell#1---set-up-vcpkg)
    + Open `roadrolla.sln` with Visual Studio
    + or build with CMake and vcpkg: `cmake -S ./ -B ./build -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"`
    + `cmake --build ./build --config Release`
* Debian Linux:
    + `sudo apt install cmake libglu1-mesa-dev freeglut3-dev mesa-common-dev`
    + `cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./build/`
    + `cmake --build ./build`
* macOS
    + `brew install xquartz cmake libx11 libxi libxrandr libxxf86vm pkg-config mesa freeglut`
    + Open `roadrolla.xcodeproj` with Xcode
    + or build with CMake: `cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./build/` then `cmake --build ./build`

## Deployment
Compile contents of the `src` directory & run the resulting executable.

## Notes
This project has been prepared for usage with
* [Visual Studio 2022](https://www.visualstudio.com/vs/)
* [Xcode](https://developer.apple.com/xcode/)
* [CMake](https://cmake.org/) e.g. for cross platform builds

## Contribution guidelines
TBD

## Vehicle controls
* **F** - Press to increase the **acceleration** of the vehicle
* **N** - Press to **steady** the acceleration rate of the vehicle
* **B** - Press to increase the **deceleration** of the vehicle, if the vehicle stands still it starts to accelerate backwards

## Chicken controls
* **C** - Order a chicken to attempt crossing the road

## Camera controls
* **F1/F2/F3** - Press to switch to dashboard/chase/roaming camera
* Use the mouse to look around
* **W/S/A/D** - Press & hold to move the camera forward/backward/left/right (only for roaming camera)
* **F4** - Toggle 'fake' fullscreen mode
