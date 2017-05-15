# Roadrolla' #
Roadrolla is an OpenGL 1.1 based 'game', originally created in 2011 as a homework for a [course](https://portal.vik.bme.hu/kepzes/targyak/VIIIAB03/en/).

## Dependencies ##
* [freeglut](http://freeglut.sourceforge.net/)

## System Requirements ##
* OpenGL 1.1 compatible video card (any video chip released after 1999 😂)

## Summary of set up
* `git clone git@github.com:laszlolukacs/roadrolla-gl.git <LOCAL_WORKING_DIR>`
* (If using Visual Studio) Open `roadrolla.sln`

## Deployment
Compile contents of the `src` directory & run the resulting executable.

## Notes
This project has been prepared for usage with
* [Visual Studio 2017](https://www.visualstudio.com/vs/)
* [CMake](https://cmake.org/) e.g. for \*NIX or cross platform builds

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
