# include freeglut
if(APPLE)
	set(CMAKE_FIND_FRAMEWORK LAST)
	set(GLUT_ROOT "$ENV{HOMEBREW_PREFIX}/opt/freeglut")
endif()
if(WIN32)
	cmake_path(SET GLUT_HOME_PATH $ENV{GLUT_HOME})
	set(CMAKE_PREFIX_PATH ${GLUT_HOME_PATH})
endif()
find_package(GLUT REQUIRED)
if(NOT GLUT_FOUND)
	message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

# include OpenGL
set(OpenGL_GL_PREFERENCE GLVND) # GLVND ABI for LINUX
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(ERROR " OpenGL not found!")
endif(NOT OPENGL_FOUND)

include_directories(${roadrolla-gl_SOURCE_DIR}/src)
include_directories(${roadrolla-gl_SOURCE_DIR}/src/Actors)
include_directories(${roadrolla-gl_SOURCE_DIR}/src/Textures)
include_directories(${roadrolla-gl_SOURCE_DIR}/src/Primitives)

link_directories(
	${roadrolla-gl_BINARY_DIR}/src
	${roadrolla-gl_SOURCE_DIR}/src/Actors
	${roadrolla-gl_SOURCE_DIR}/src/Textures
	${roadrolla-gl_SOURCE_DIR}/src/Primitives
)

add_executable(roadrolla
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

target_sources(roadrolla PRIVATE roadrolla.rc)

if(LINUX)
	target_link_libraries(roadrolla OpenGL::OpenGL OpenGL::GLU GLUT::GLUT) # OpenGL::OpenGL for the modern GLVND ABI for LINUX
else()
	target_link_libraries(roadrolla OpenGL::GL OpenGL::GLU GLUT::GLUT)
endif()
