#ifndef __CORE_H__
#define __CORE_H__

#include <Windows.h>

//definitions
#define WINDOW_CLASS_NAME	(L"gl_test class")
#define HEIGHT				(500)
#define WIDTH				(500)
#define TIMER_UPDATE		(1)


//function declarations
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//DWORD WINAPI update_call_thread(LPVOID lpParameter);
BOOL bSetupPixelFormat(HDC hdc);
void print_error(char *state);
BOOL swap_buffers();
char *LoadFromFile(char *filename);
void print_error(char *state);
double GetSecMsecTime();
#endif
