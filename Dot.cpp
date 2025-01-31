﻿#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
         WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("Menu");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
		   LPSTR lpszCmdLine, int nCmdShow)	
		   //WINAPI : 윈도우 프로그램이라는 의미
		   //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
		   //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
		   //iCmdShow : 윈도우가 화면에 출력될 형태
{	HWND	hwnd;															 
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass 라는 구조체 정의									 
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;			 //출력스타일 : 수직/수평의 변화시 다시 그림
	WndClass.lpfnWndProc	= WndProc;							 //프로시저 함수명
	WndClass.cbClsExtra		= 0;								 //O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra		= 0;								 //O/s 사용 여분 메모리 (Window)
	WndClass.hInstance		= hInstance;						 //응용 프로그램 ID
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	 //아이콘 유형
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);		 //커서 유형
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
	WndClass.lpszMenuName	= NULL;								 //메뉴 이름
	WndClass.lpszClassName	= lpszClass;						 //클래스 이름
	RegisterClass(&WndClass);									 //앞서 정의한 윈도우 클래스의 주소 

   hwnd = CreateWindow(lpszClass,				//윈도우가 생성되면 핸들(hwnd)이 반환
      lpszClass,								//윈도우 클래스, 타이틀 이름
      WS_OVERLAPPEDWINDOW,						//윈도우 스타일
      CW_USEDEFAULT,							//윈도우 위치, x좌표
      CW_USEDEFAULT,							//윈도우 위치, y좌표
      CW_USEDEFAULT,							//윈도우 폭  
      CW_USEDEFAULT,							//윈도우 높이 
      NULL,										//부모 윈도우 핸들
      NULL,										//메뉴 핸들	
      hInstance,								//응용 프로그램 ID
      NULL										//생성된 윈도우 정보
   );
   ShowWindow(hwnd, nCmdShow);					//윈도우의 화면 출력
   UpdateWindow(hwnd);							//O/S 에 WM_PAINT 메시지 전송

   while(GetMessage(&msg, NULL, 0, 0))			//WinProc()에서 PostQuitMessage() 호출 때까지 처리
   {
      TranslateMessage(&msg);   
      DispatchMessage(&msg);					//WinMain -> WinProc 
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
      x = y = mDown = 0;
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
      mDown = TRUE;
      // m_count++;
      // itoa(m_count, linebfr, 10);

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
      
      if(mDown == TRUE)
         TextOut(hdc, x, y, "H", 1);

      EndPaint(hwnd, &ps);

      mDown = FALSE; // 왼쪽을 누를 때마다 점 찍힘. 이 명령어 없으면 왼쪽을 한 번 누르고 쭉 그림 그리기 가능
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}