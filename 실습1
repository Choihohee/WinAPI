#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);	//타입 미리 해두는게 좋음


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

	ShowWindow(hwnd, nCmdShow);	/*윈도우의 화면 출력
	nCmdShow : SW_HIDE, SW_SHOW, SW_MAXIMIZE, SW_MINIMIZE*/

	UpdateWindow(hwnd);//윈도우 등록, 생성 화면에 보인 다음에// O/S에 WM_PAINT  메시지 전송

	while(GetMessage(&msg, NULL, 0, 0))//이벤트 메시지 보내기,무한 루프되다가 걸리는 거 있으면 WinProc한테 던져줌
	{	// WinProc()에서 PostQuitMessage() 호출 때까지 처리
		TranslateMessage(&msg);	// Shift ‘a’ -> 대문자 ‘A’
		DispatchMessage(&msg);	// WinMain -> WinProc
	}   
	return (int)msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
	HDC hdc;
	PAINTSTRUCT ps;
	static COLORREF fColor;


	switch (iMsg) 
	{
	case WM_CREATE:  //처음할 때 딱 한 번 실행됨.
		fColor = RGB(0,0,0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, fColor);
		TextOut(hdc, 10, 10, TEXT("Hello Windows API Programming"), 29);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:	//프로그램 종료할 때 딱 한 번 실행됨. 뒷정리 여기서 다 해야함
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}
