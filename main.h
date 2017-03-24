#ifndef __MAIN_H__
#define __MAIN_H__

//pre-include definitions
#ifndef UNICODE
#define UNICODE
#endif

//libraries
#pragma comment (lib, "Opengl32.lib")

//inclused
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <gl\GL.h>

//definiions
#define GL_TEST_CLASS_NAME	(L"gl_test class")
#define HEIGHT				(480)
#define WIDTH				(640)
#define UPDATE_SCENE		(0x01)

//global variables
HINSTANCE hInst = NULL;
HWND hWnd;
HDC ghDC;
HGLRC ghRC;


//function declarations
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL bSetupPixelFormat(HDC hdc);
GLvoid drawScene();
GLvoid draw_square();

#endif
