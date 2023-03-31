#include <windows.h>
#include <WindowsX.h>
#include <math.h>
#include <stdlib.h>
#define BSIZE 20

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
         WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("Choihohee");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
         LPSTR lpszCmdLine, int nCmdShow)
{
   HWND   hwnd;
   MSG      msg;
   WNDCLASS WndClass;   
   WndClass.style         = CS_HREDRAW | CS_VREDRAW;
   WndClass.lpfnWndProc   = WndProc;      
   WndClass.cbClsExtra      = 0;      
   WndClass.cbWndExtra      = 0;      
   WndClass.hInstance      = hInstance;      
   WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   WndClass.hCursor      = LoadCursor(NULL, IDC_ARROW);   
   WndClass.hbrBackground   = (HBRUSH)GetStockObject(WHITE_BRUSH);   
   WndClass.lpszMenuName   = NULL;      
   WndClass.lpszClassName   = lpszClass;   
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

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);   
      DispatchMessage(&msg);   
   }   
   return (int)msg.wParam;
}
   //피타고라스 정의를 이용하여 원의 중심으로부터 마우스포인터까지 거리를 반환
   int Length(int x1, int y1) {
      if(x1 >= y1)
         return x1=y1;
      else
         return (y1-x1);
   }


   bool correct(int x, int y, int x1, int y1) {
     if (Length(x, x1) < BSIZE&&Length(y,y1)<BSIZE) {
        return TRUE;
    }
   else {
      return FALSE;
    }
   }



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
   HDC hdc;
   PAINTSTRUCT ps;
   static int mDown, x, y, xClick, yClick;
   static bool click;

   switch (iMsg) 
   {
   case WM_CREATE:  
      SetTimer(hwnd, 1, 1000, NULL);
      x = y = 100;
      mDown = xClick = yClick = 0;
      click = FALSE;
      break;

   case WM_TIMER:
      x = rand() % 575;
      y = rand() % 547;
      click = FALSE;

      InvalidateRect(hwnd, NULL, TRUE);
      break;

   case WM_LBUTTONDOWN:
      xClick = LOWORD(lParam);
      yClick = HIWORD(lParam);

      if(correct(x, y, xClick, yClick))
         click = TRUE;
      else
         click = FALSE;

      InvalidateRect(hwnd, NULL, TRUE);
      break;

   case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      
      if(click == TRUE){
         SetTextColor(hdc, RGB(255, 0, 0));

         TextOut(hdc, 500, 500, "SUCCESS", 7);
      }
      else if(click == FALSE){
         SetTextColor(hdc, RGB(0, 0, 0));
         TextOut(hdc, 500, 500, "FAIL", 4);
      }

      TextOut(hdc, x, y, "H", 1);

      EndPaint(hwnd, &ps);

      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}