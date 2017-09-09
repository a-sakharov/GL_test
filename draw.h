#ifndef __DRAW_H__
#define __DRAW_H__

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gl\GL.h>
#include "glext.h"


#define LOADOPENGLPROC(type, name)\
if (!(name = (type)wglGetProcAddress(#name)))\
{\
print_error("Cannot load opengl proc" #name);\
exit(-1);\
}

#define LOADSHADERFROMFILE(destination, filename)\
if (!(destination = LoadFromFile(filename)))\
{\
	print_error("Cannot load shader " filename);\
	exit(-1);\
}


PFNGLSHADERSOURCEARBPROC glShaderSource;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLCREATEPROGRAMPROC  glCreateProgram;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYAPPLEPROC glBindVertexArray;
PFNGLCLEARBUFFERFVPROC glClearBufferfv;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
PFNGLPATCHPARAMETERIPROC glPatchParameteri;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLGETSTRINGIPROC glGetStringi;

GLuint rendering_program;
GLuint vertex_array_object;

void cleanup();
void update();
void init();
GLchar *LoadFromFile(char *filename);
extern void swap_buffers();
extern void print_error(char *state);
double GetSecMsecTime();
#endif
