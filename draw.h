#ifndef __DRAW_H__
#define __DRAW_H__


#include <windows.h>
#include <gl\GL.h>
#include "glext.h"


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


GLuint rendering_program;
GLuint vertex_array_object;


void cleanup();
void update();
void init();
extern void swap_buffers();

#endif
