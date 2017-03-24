#include "main.h"

int main(int argc, char **argv)
{
	WNDCLASSEX wClass;
	MSG msg;
	UINT_PTR timer;

	srand((unsigned int)time(NULL));

	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.style = CS_HREDRAW | CS_VREDRAW;
	wClass.lpfnWndProc = (WNDPROC)WindowProc;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = hInst;
	wClass.hIcon = NULL;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = GL_TEST_CLASS_NAME;
	wClass.hIconSm = NULL;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL, L"Window class creation failed\r\nError code:", L"Window Class Failed", MB_ICONERROR);
	}

	if(!(hWnd = CreateWindowEx(0, GL_TEST_CLASS_NAME, L"GL_test", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 200, 200, 360, 290, NULL, NULL, hInst, NULL)))
	{
		MessageBox(NULL, L"Window creation failed", L"Window Creation Failed", MB_ICONERROR);
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow (hWnd);
	if(!(timer = SetTimer(hWnd, UPDATE_SCENE, 100, NULL)))
	{
		puts("Error timer()");
	}

	ZeroMemory(&msg, sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if(!KillTimer(hWnd, timer))
	{
		puts("Error KillTImer()");
	}

	if(!UnregisterClass(GL_TEST_CLASS_NAME, NULL))
	{
		puts("error unregister class");
	}

	return 0;
}



LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	LONG result = 1;

	switch(uMsg)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			default:

				break;
			}
		}
		break;

	case WM_PAINT: 
		BeginPaint(hWnd, &ps); 
		EndPaint(hWnd, &ps); 
		break; 

	case WM_TIMER: 
		switch(wParam)
		{
		case UPDATE_SCENE:
			{
				drawScene();
			}
			break;


		default:
			break;
		}
		break; 

	case WM_CREATE: 
		{
			puts("Window created");
			if(!SetWindowPos(hWnd, HWND_TOP, 0, 0, WIDTH, HEIGHT, SWP_NOMOVE))
			{
				puts("error SetWindowPos");
			}

			if(!(ghDC = GetDC(hWnd)))
			{
				puts("error GetDC");
			}

			if(!bSetupPixelFormat(ghDC))
			{
				puts("error bSetupPixelFormat");
			}

			if(!(ghRC = wglCreateContext(ghDC)))
			{
				puts("error wglCreateContext");
			}

			if(!wglMakeCurrent(ghDC, ghRC))
			{
				puts("error wglMakeCurrent");
			}

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
		}
		break;

	case WM_DESTROY:
		{
			puts("Window destroed");

			if (ghRC) 
			{
				if(!wglDeleteContext(ghRC))
				{
					puts("error wglDeleteContext");
				}
			}

			if (ghDC) 
			{
				if(!ReleaseDC(hWnd, ghDC))
				{
					puts("error ReleaseDC");
				}
			}

			PostQuitMessage(0);
			return 0;
		}
		break;

	default: 
        result = DefWindowProc (hWnd, uMsg, wParam, lParam); 
        break; 
	}

	return result;
}

BOOL bSetupPixelFormat(HDC hdc) 
{ 
	PIXELFORMATDESCRIPTOR pfd; 
	int pixelformat; 

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion = 1; 
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;// | PFD_DOUBLEBUFFER; 
	pfd.dwLayerMask = PFD_MAIN_PLANE; 
	pfd.iPixelType = PFD_TYPE_COLORINDEX; 
	pfd.cColorBits = 8; 
	pfd.cDepthBits = 16; 
	pfd.cAccumBits = 0; 
	pfd.cStencilBits = 0; 

	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == 0) 
	{ 
		MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK); 
		return FALSE; 
	} 

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) 
	{ 
		MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK); 
		return FALSE; 
	} 

	return TRUE; 
}

GLvoid drawScene() 
{ 
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	draw_square();
	glFlush();
	//SwapBuffers(ghDC); 
}

GLvoid draw_square()
{
	GLfloat x = 1.0/((float)(rand()%100)), 
		y = 1.0/((float)(rand()%100)), 
		l = 1.0/((float)(rand()%100));

	glColor3f(1.0/((float)(rand()%10)), 1.0/((float)(rand()%10)), 1.0/((float)(rand()%10)));
	glBegin(GL_POLYGON);
	glVertex3f(x, y, 0.0);
	glVertex3f(x+l, y, 0.0);
	glVertex3f(x+l, y+l, 0.0);
	glVertex3f(x, y+l, 0.0);
	glEnd();
}
