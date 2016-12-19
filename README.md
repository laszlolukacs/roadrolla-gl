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
* [Visual Studio 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48146)
* [CMake](https://cmake.org/) e.g. for \*NIX or cross platform builds

## Contribution guidelines
TBD

## Vehicle controls
* **F** - Press to increase the **acceleration** of the vehicle
* **N** - Press to stop increasing/decreasing the **acceleration**
* **B** - Press to increase the **decceleartion** of the vehicle, if the vehicle stands still it starts to accelerate backwards

## Chicken controls
* **C** - Order a chicken to attempt crossing the road
