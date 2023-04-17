#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
			WPARAM wParam, LPARAM lParam);


LPCTSTR lpszClass = TEXT("1. Text out: 키보드입력");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
		   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND	hwnd;
	MSG		msg;
	WNDCLASS WndClass;   
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc	= WndProc;      
	WndClass.cbClsExtra		= 0;      
	WndClass.cbWndExtra		= 0;      
	WndClass.hInstance		= hInstance;      
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);   
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);   
	WndClass.lpszMenuName	= NULL;      
	WndClass.lpszClassName	= lpszClass;   
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

	HDC hdc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
			 WPARAM wParam, LPARAM lParam)     
{
	PAINTSTRUCT ps;
	static COLORREF fColor;
	static char linebfr[10][256]={0, };
	static int i, row, col;

	switch (iMsg) 
	{
		
	case WM_CREATE:   //CreateWindow() 함수에 의해 메인 윈도우가 생성된 직후에 화면에 보여지기 전에 보내지는 메시지.
		fColor = RGB(0,0,0);
		row=col=0;
		break;

	case WM_CHAR:
		if(wParam == VK_RETURN){
			row++;
			col=0;
		}
		else{
			linebfr[row][col++]=wParam;
			linebfr[row][col]='\0';
		}
		InvalidateRect(hwnd, NULL, FALSE);//화면 다시 그리기
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, fColor);
		
		for(i=0; i<10; i++)
			TextOut(hdc,100,100+20*i,linebfr[i],strlen(linebfr[i]) );

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}