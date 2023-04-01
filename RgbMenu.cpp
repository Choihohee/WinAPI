#include <windows.h>
#include "resource.h"								 //메뉴 이름
#include <WindowsX.h>
#include <math.h>
#include <stdlib.h>
#define BSIZE 20

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("Menu");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine, int nCmdShow)
{
    HWND   hwnd;
    MSG      msg;
    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);;
    WndClass.lpszClassName = lpszClass;
    RegisterClass(&WndClass);

    hwnd = CreateWindow(lpszClass,
        lpszClass,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        600,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
//피타고라스 정의를 이용하여 원의 중심으로부터 마우스포인터까지 거리를 반환
int Length(int x1, int y1) {
    if (x1 >= y1)
        return x1 = y1;
    else
        return (y1 - x1);
}


bool correct(int x, int y, int x1, int y1) {
    if (Length(x, x1) < BSIZE && Length(y, y1) < BSIZE) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static COLORREF fColor;


    switch (iMsg)
    {
    case WM_CREATE:
        fColor = RGB(0, 0, 0);
        break;
    case WM_COMMAND:
        if (wParam == ID_RED)
            fColor = RGB(255, 0, 0);

        if (wParam == ID_GREEN)
            fColor = RGB(0, 255, 0);

        if (wParam == ID_BLUE)
            fColor = RGB(0, 0, 255);

        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        SetTextColor(hdc, fColor);
        TextOut(hdc, 100, 100, "Hello Windows API Programming", 29);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}