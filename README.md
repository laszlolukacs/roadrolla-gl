# Roadrolla' #
Roadrolla is an OpenGL 1.1 based 'game', originally created in 2011 as a homework for a [course](https://portal.vik.bme.hu/kepzes/targyak/VIIIAB03/en/).

## Dependencies ##
* [freeglut](http://freeglut.sourceforge.net/)
* Recommended: [Visual Studio 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48146) as IDE - solution and dependencies are preconfigured for VS2015

## System Requirements ##
* OpenGL 1.1 compatible video card (any video chip released after 1999 😂)

## Summary of set up
* `git clone git@github.com:laszlolukacs/roadrolla-gl_1_1.git <LOCAL_WORKING_DIR>`
* (If using Visual Studio) Open the `roadrolla.sln` in Visual Studio 2015

## Notes
Debug versions of the code are very slow, because tesselation is done again and again before frame rendering.

## Deployment
Compile & run the resulting executable.

## Contribution guidelines
TBD

## Vehicle controls
* **F** - Press to increase the **acceleration** of the vehicle
* **N** - Press to stop increasing/decreasing the **acceleration**
* **B** - Press to increase the **decceleartion** of the vehicle, if the vehicle stands still it starts to accelerate backwards

## Chicken controls
* **C** - Order a chicken to attempt crossing the road