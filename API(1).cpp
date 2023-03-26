#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
         WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("Menu");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
      100,   
      100,   
      600,   
      500,   
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
   static int mDown, x, y;

   switch (iMsg) 
   {
   case WM_CREATE:  
	  x=100;
	  check=FALSE;
	  SetTimer(hwnd,1,1,NULL); //5초에1번
      y = mDown = 0;
      break;

   case WM_TIMER:

	   if(x==0)
		   check=TRUE;
	   else if(x==580)
		   check=FALSE;
	   if(check==TRUE)
		   x+=1;
	   else if(check==FALSE)
		   x-=1;

	   InvalidateRect(hwnd,NULL,TRUE);
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
      mDown = TRUE;
      // m_count++;
      // itoa(m_count, linebfr, 10);

      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_LBUTTONUP:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      mDown = FALSE;

      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_RBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      mDown = FALSE;
      // m_count++;
      // itoa(m_count, linebfr, 10);

      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      TextOut(hdc, x, y, "H", 1);

      EndPaint(hwnd, &ps);
      // mDown = FALSE; // 왼쪽을 누를 때마다 점만 찍힘. 이 명령어 없으면 왼쪽을 한 번 누르고 쭉 그림 그리기 가능
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}