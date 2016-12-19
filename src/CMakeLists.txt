# Laszlo Lukacs, 2016-12-19 03:04

# includes freeglut
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

# include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

include_directories (${roadrolla-gl_SOURCE_DIR}/src)
include_directories (${roadrolla-gl_SOURCE_DIR}/src/Actors)
include_directories (${roadrolla-gl_SOURCE_DIR}/src/Textures)
include_directories (${roadrolla-gl_SOURCE_DIR}/src/Primitives)

link_directories (
	${roadrolla-gl_BINARY_DIR}/src
	${roadrolla-gl_SOURCE_DIR}/src/Actors
	${roadrolla-gl_SOURCE_DIR}/src/Textures
	${roadrolla-gl_SOURCE_DIR}/src/Primitives
)

add_executable (roadrolla
				main.cpp
				Primitive.cpp
				Primitives/ParametricSurface.cpp
				Primitives/Circle.cpp
				Primitives/Cone.cpp
				Primitives/Cube.cpp
				Primitives/Cylinder.cpp
				Primitives/Ellipsoid.cpp
				Primitives/Plane.cpp
				Actors/Chicken.cpp
				Actors/RoadRoller.cpp
				RoadRollerGame.cpp
                )

target_link_libraries(roadrolla ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )