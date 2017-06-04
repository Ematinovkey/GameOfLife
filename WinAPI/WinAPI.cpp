// WinAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinAPI.h"
#include "World.h"
#include <urlmon.h>

#define MAX_LOADSTRING 100

// Global Variables:
int x, y, _x, _y;
bool started;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
World field;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      450, 150,616, 619, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_RESET:
				KillTimer(hWnd, TIMER_1);
				started = false;
				field.reset();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_MENU_START:
				SetTimer(hWnd, TIMER_1, 100, NULL);
				started = true;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_MENU_STOP:
				KillTimer(hWnd, TIMER_1);
				started = false;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_OSCILLATORS_PENTA:
				field.penta();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_OSCILLATORS_BLINKER:
				field.blinker();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_OSCILLATORS_BEACON:
				field.beacon();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_METHUSELAHS_DIEHARD:
			case ID_METHUSELAHS_R:
			case ID_STRUCTURES_GLIDERGUN:
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (!started)
		{
			if (field.get_cell_state(y / _y, x / _x))
				field.set_cell_state0(y / _y, x / _x);
			else
				field.set_cell_state1(y / _y, x / _x);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
    	field.create_new_gen();
		if(!field.check_life())
		{
			KillTimer(hWnd, TIMER_1);
			started = false;
			MessageBox(hWnd, L"The simulation is over!", L"Life ended...", MB_OK);
		}
    	InvalidateRect(hWnd, NULL, TRUE);
    	break;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 616;
		lpMMI->ptMinTrackSize.y = 619;
		lpMMI->ptMaxTrackSize.x = 616;
		lpMMI->ptMaxTrackSize.y = 619;
		break;
	}
	case WM_ERASEBKGND:
		return (LRESULT)1;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			RECT rc;
			GetClientRect(hWnd, &rc);
			_x = rc.right / 40, _y = rc.bottom / 40;
			HDC hdc, hdcMem;
			HBITMAP hbmMem;
			HGDIOBJ hbmOld;
			hdc = BeginPaint(hWnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
			hbmOld = SelectObject(hdcMem, hbmMem);
			FillRect(hdcMem, &rc, (HBRUSH)(COLOR_WINDOW + 1));
			SetBkMode(hdcMem, TRANSPARENT);
			for (int i = 0; i < 40; i++)
				for (int j = 0; j < 40; j++)
				{
					if (field.get_cell_state(j, i))
					{
						SelectObject(hdcMem, GetStockObject(WHITE_PEN));
						SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
						Rectangle(hdcMem, i*_x, j*_y, (i + 1)*_x, (j + 1)*_y);
					}
					else
					{
						SelectObject(hdcMem, GetStockObject(WHITE_PEN));
						SelectObject(hdcMem, GetStockObject(DC_BRUSH));
						Rectangle(hdcMem, i*_x, j*_y, (i + 1)*_x, (j + 1)*_y);
					}

				}

			BitBlt(hdc,
				rc.left, rc.top,
				rc.right, rc.bottom,
				hdcMem,
				rc.left, rc.top,
				SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
