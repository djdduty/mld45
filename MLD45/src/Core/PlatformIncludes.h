#ifndef PLATFORM_INCLUDES_H
#define PLATFORM_INCLUDES_H

#define GLEW_STATIC

#ifdef __APPLE__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <sys/malloc.h>

#else

#include <glew/include/GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <malloc.h>

#endif //ifdef __APPLE__ && else

#endif //top ifndef
