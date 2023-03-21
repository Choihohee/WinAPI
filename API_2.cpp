#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
         WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("Menu");

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
      CW_USEDEFAULT,   
      CW_USEDEFAULT,   
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
   HDC hdc;
   PAINTSTRUCT ps;
   static COLORREF fColor;
   static char linebfr[256] = {0,};
   static int m_count, x, y, left_button;

   switch (iMsg) 
   {
   case WM_CREATE:  
      fColor = RGB(0,0,0);
      break;

   case WM_CHAR:
      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_MOUSEMOVE:
      x = LOWORD(lParam);
      y = HIWORD(lParam);

      // m_count++;
      // itoa(m_count, linebfr, 10);

      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_LBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      left_button = TRUE;
      // m_count++;
      // itoa(m_count, linebfr, 10);

      InvalidateRect(hwnd, NULL, FALSE);
      break;


   case WM_RBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      left_button = FALSE;
      // m_count++;
      // itoa(m_count, linebfr, 10);

      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      
      if(left_button == TRUE)
         SetPixel(hdc, x, y, RGB(255, 0, 0));

      EndPaint(hwnd, &ps);
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}