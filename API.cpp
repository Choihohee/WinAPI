#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
////타입 미리 해두는게 좋음

LPCTSTR lpszClass = TEXT("Menu");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
        /*WINAPI: 윈도우 프로그램이라는 의미
		hInstance: 운영체제의 커널이 응용 프로그램에 부여한 ID
		szCmdLine: 커멘드라인 상에서 프로그램 구동 시 전달된 문자열
		iCmdShow: 윈도우가 화면에 출력될 형태*/
{
   HWND	hwnd;	//HWND라는 타입으로 hwnd변수 생성
	MSG		msg;	//MSG라는 타입으로 msg변수 생성
	WNDCLASS WndClass;   
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;	//멤버변수에 값을 채워줌
	WndClass.lpfnWndProc	= WndProc;      //멤버변수에 값을 채워줌
	WndClass.cbClsExtra		= 0;      //멤버변수에 값을 채워줌
	WndClass.cbWndExtra		= 0;      //멤버변수에 값을 채워줌
	WndClass.hInstance		= hInstance;      //멤버변수에 값을 채워줌
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);//멤버변수에 값을 채워줌
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);   //멤버변수에 값을 채워줌
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);   //멤버변수에 값을 채워줌
	WndClass.lpszMenuName	= NULL;      //멤버변수에 값을 채워줌
	WndClass.lpszClassName	= lpszClass;   //멤버변수에 값을 채워줌
	RegisterClass(&WndClass);   //위의 항목들 윈도우에 등록   

  hwnd = CreateWindow//윈도우가 생성되면 핸들(hwnd)이 반환됨
		(lpszClass,				// 윈도우 클래스 이름
		lpszClass,				// 윈도우 타이틀 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		CW_USEDEFAULT,			// 윈도우 위치, x좌표 
		CW_USEDEFAULT,			// 윈도우 위치, y좌표
		CW_USEDEFAULT,			// 윈도우 폭
        CW_USEDEFAULT,			// 윈도우 높이
        NULL,					// 부모 윈도우 핸들
        NULL,					// 메뉴 핸들
        hInstance,				// 응용 프로그램 ID
		NULL);					// 생성된 윈도우 정보
   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);   
      DispatchMessage(&msg);   
   }   
   return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
          WPARAM wParam, LPARAM lParam)     
{
   HDC hdc; // 화면의 주민등록번호
   PAINTSTRUCT ps; // 화면을 칠하는 도구
   static COLORREF fColor;
   static char lineBfr[20][256];
   static int row, col;

   switch (iMsg) 
   {
   case WM_CREATE:  // 초기화 함수, 프로그램 시작할 때 딱 한 번 실행됨.
      row = col = 0;
      // fColor = RGB(0,0,0); // 검은색 | R 1byte, G 1byte, B 1byte | 흰색은 255, 255, 255
      break;
   
   // WM_CREAT, WM_MOUSE... 등등 기본적으로 쓰는 것들이 있음.

   case WM_KEYDOWN:
      if(wParam == VK_LEFT){
         col -= 1;
      }
      break;
   case WM_CHAR:
      /*if(wParam == 'i')
         y -= 5; */
      // lineBfr[i++] = wParam;
      // lineBfr[i] = 0;
      if(wParam == VK_RETURN){ // VK_UP
         row++;
         col = 0;
      }
      else {
         lineBfr[row][col++] = wParam;
         lineBfr[row][col] = 0;
      }
      InvalidateRect(hwnd, NULL, TRUE); //(FALSE면 잔상 남음)
      break;

   case WM_PAINT: //화면에 출력하는 이벤트
      hdc = BeginPaint(hwnd, &ps); 
      // SetTextColor(hdc, fColor); // 검은색 글씨
      // TextOut(hdc, 10, 10, "Hello Windows API Programming", 29);       
	  // TextOut(화면 주민등록번호, x좌표, y좌표, 출력할 문자열, 문자열 길이);
      for(int i = 0; i < 20; i++){
         TextOut(hdc, 100, i*20, lineBfr[i], strlen(lineBfr[i]));
      }

      EndPaint(hwnd, &ps); //반드시 입력
      break;
   case WM_DESTROY: //프로그램 끝날 때 쓰는 이벤트
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}
