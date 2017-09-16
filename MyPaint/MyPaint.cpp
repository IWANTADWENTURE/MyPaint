// MyPaint.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "MyPaint.h"
#include "DrawShapes.cpp"
#include <windows.h> 
#include <stdlib.h> 
#include <string.h> 
#include <tchar.h>
#include "PictureSaver.cpp"

using namespace std;

#define MAX_LOADSTRING 100

#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

COLORREF DrawShapes::PenColor;
int DrawShapes::PenWidth;
HPEN DrawShapes::hPenOld;
HPEN DrawShapes::hLinePen;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYPAINT));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYPAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd;
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINTS ptsEnd;
	static POINTS ptsBegin;
	static HDC hdc;
	static RECT rect;
	static DrawShapes DrawShapeVar;
	static PictureSaver PicSav;
	static void (DrawShapes::*ShapeDraw)(HDC, POINTS, POINTS) = &DrawShapes::NoDraw;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
			switch (wmId)
			{
			case IDM_ABOUT: {//About programm
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			}
			case IDM_EXIT: { //Exit
				DestroyWindow(hWnd);
				break;
			}
			case IDM_Save: {//Save Picture
				PicSav.SavePicture(hWnd, "img.bmp");
				break;
			}
			case IDINS_Empty: {//Do nothing
				ShapeDraw = &DrawShapes::NoDraw;
				break;
			}
			case IDSH_Rectangle: {	//IDSH - shape ID
				ShapeDraw = &DrawShapes::DrawRect;
				break;
			}
			case IDSH_RonRect: {
				ShapeDraw = &DrawShapes::DrawRoundRect;
				break;
			}
			case IDSH_Ellipse: {
				ShapeDraw = &DrawShapes::DrawElip;
				break;
			}
			case IDSH_Line: {
				ShapeDraw = &DrawShapes::DrawLine;
				break;
			}
			case ID_PW_3: {
				DrawShapeVar.SetPenWidth(3);
				break;
			}
			case ID_PW_4: {
				DrawShapeVar.SetPenWidth(4);
				break;
			}
			case ID_PW_7: {
				DrawShapeVar.SetPenWidth(7);
				break;
			}
			case ID_PC_Black: {
				DrawShapeVar.SetPenColor(RGB(0, 0, 0));
				break;
			}
			case ID_PC_Blue: {
				DrawShapeVar.SetPenColor(RGB(0, 0, 255));
				break;
			}
			case ID_PC_Red: {
				DrawShapeVar.SetPenColor(RGB(255, 0, 0));
				break;
			}
			case ID_PC_Green: {
				DrawShapeVar.SetPenColor(RGB(0, 255, 0));
				break;
			}
			default: {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			}
        }
        break;
	case WM_LBUTTONDOWN:
		ptsBegin = MAKEPOINTS(lParam);// remember coord where LMB pick for start draw
		return 0;

	case WM_LBUTTONUP: {
		ptsEnd = MAKEPOINTS(lParam);
		(DrawShapeVar.*ShapeDraw)(GetDC(hWnd), ptsBegin, ptsEnd);//remember coords end paint shape
		break;
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps); 
			HBRUSH hBrush;
			hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			EndPaint(hWnd, &ps);
			Ellipse(hdc, 100, 100, 200, 300); //эллипс будет заштрихован
			ReleaseCapture();
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

// Обработчик сообщений для окна "О программе".
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
