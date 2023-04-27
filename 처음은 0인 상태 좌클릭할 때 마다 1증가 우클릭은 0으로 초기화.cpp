#include <windows.h>
#include<stdlib.h>
#include<string.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("ó���� 0�� ���� ��Ŭ���� �� ���� 1���� ��Ŭ���� 0���� �ʱ�ȭ");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : ������ ���α׷��̶�� �ǹ�
	LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																 //szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	HWND	hwnd;												 //iCmdShow : �����찡 ȭ�鿡 ��µ� ����
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass ��� ����ü ����									 
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;			 //��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
	WndClass.lpfnWndProc	= WndProc;							 //���ν��� �Լ���
	WndClass.cbClsExtra		= 0;								 //O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra		= 0;								 //O/s ��� ���� �޸� (Window)
	WndClass.hInstance		= hInstance;						 //���� ���α׷� ID
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	 //������ ����
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);		 //Ŀ�� ����
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//����   
	WndClass.lpszMenuName	= NULL;								 //�޴� �̸�
	WndClass.lpszClassName	= lpszClass;						 //Ŭ���� �̸�
	RegisterClass(&WndClass);									 //�ռ� ������ ������ Ŭ������ �ּ�

	hwnd = CreateWindow(lpszClass,								 //�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
		lpszClass,												 //������ Ŭ����, Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,									 //������ ��Ÿ��
		CW_USEDEFAULT,											 //������ ��ġ, x��ǥ
		CW_USEDEFAULT,											 //������ ��ġ, y��ǥ
		CW_USEDEFAULT,											 //������ ��   
		CW_USEDEFAULT,											 //������ ����   
		NULL,													 //�θ� ������ �ڵ�	 
		NULL,													 //�޴� �ڵ�
		hInstance,    											 //���� ���α׷� ID
		NULL     												 //������ ������ ����
		);
	ShowWindow(hwnd, nCmdShow);									 //�������� ȭ�� ���
	UpdateWindow(hwnd);											 //O/S �� WM_PAINT �޽��� ����

	while(GetMessage(&msg, NULL, 0, 0))							 //WinProc()���� PostQuitMessage() ȣ�� ������ ó��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;


char count[3] = "0";
char zero_count[2] = "0";
int temp;


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{
	PAINTSTRUCT ps;
	/*���콺 ���� ��ư Ŭ�� ��, count ���� ���� 1 ������Ű��, ȭ���� �ٽ� 
	�׷��ݴϴ�. ���콺 ������ ��ư Ŭ�� ��, count ���� ���� 0���� �ʱ�ȭ�ϰ�, 
	ȭ���� �ٽ� �׷��ݴϴ�.*/

	switch (iMsg) 
	{
	case WM_CREATE:
		//hdc = GetDC(hwnd);
		break;

	case WM_LBUTTONDOWN:
		temp = atoi(count);	//atoi:���� ��Ʈ���� ������ ��ȯ
		temp++;
		itoa(temp, count,10);
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_RBUTTONDOWN:
		temp = atoi(count);
		temp = 0 ;
		itoa(temp, count, 10);
		InvalidateRect(hwnd,NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		TextOut(hdc,107,100,count,strlen(count));		

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}