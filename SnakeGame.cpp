#include <windows.h>
#define BSIZE 15 //
#define BS 14	//몸 사이즈

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

 
LPCTSTR lpszClass = TEXT("SNAKE GAME");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND	hwnd;
	MSG		msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
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

int Length(int food, int snake) {
	if (food >= snake)
		return (food - snake);
	else
		return (food - snake) * (-1);
}
bool correct(int food_x, int food_y, int snake_x, int snake_y) {

	if (Length(food_x, snake_x) < BSIZE && Length(food_y, snake_y) < BSIZE) {

		return TRUE;
	}
	else {
		return FALSE;
	}
}

//음식 랜덤 생성
void Food_Random(int* x, int* y) {
	for (int i = 0; i < 10; i++) {
		x[i] = (rand() % 500);
		y[i] = (rand() % 500);
	}
}

//뱀의 몸 출력
void Snake(HDC hdc, int length, int* x, int* y) {
	for (int i = 0; i < length; i++)
		Rectangle(hdc, x[i] - BS / 2, y[i] - BS / 2, x[i] + BS / 2, y[i] + BS / 2);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static COLORREF fColor;
	static int food_x[10];
	static int food_y[10];
	static int snake_x[50];
	static int snake_y[50];
	static int MOVE;
	static int start, length, eat;
	static char ch;

	switch (iMsg) {
	case WM_CREATE:
		fColor = RGB(0, 0, 0);
		// 타이머 생성 및 시작
		SetTimer(hwnd, 1, 300, NULL);	//1 블럭 이동
		SetTimer(hwnd, 2, 500, NULL);	//0.5초마다 꼬리가 1개씩 증가
		snake_x[0] = snake_y[0] = 100;

		eat = 0;
		start = -1;
		length = 1;
		Food_Random(food_x, food_y);
		MOVE = 2;
		break;

	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
			MOVE = 1;
		else if (wParam == VK_RIGHT)
			MOVE = 2;
		else if (wParam == VK_UP)
			MOVE = 3;
		else if (wParam == VK_DOWN)
			MOVE = 4;
		break;

	case WM_TIMER:
		int i;
		// 게임이 시작했을 때 타이머 1번(뱀 움직임용 타이머)
		if (wParam == 1 && start == 1) {
			if (MOVE == 1) {
				for (i = 0; i < length; i++) {
					snake_x[length - i] = snake_x[length - i - 1];
					snake_y[length - i] = snake_y[length - i - 1];
				}
				snake_x[0] -= BS;	//뱀의 머리 x좌표를 BS만큼 -
			}
			if (MOVE == 2) {
				for (i = 0; i < length; i++) {
					snake_x[length - i] = snake_x[length - i - 1];
					snake_y[length - i] = snake_y[length - i - 1];
				}
				snake_x[0] += BS;	//뱀의 머리 x좌표를 BS만큼 +
			}
			if (MOVE == 3) {
				for (i = 0; i < length; i++) {
					snake_x[length - i] = snake_x[length - i - 1];
					snake_y[length - i] = snake_y[length - i - 1];
				}
				snake_y[0] -= BS;	//뱀의 머리 y좌표를 BS만큼 -
			}
			if (MOVE == 4) {
				for (i = 0; i < length; i++) {
					snake_x[length - i] = snake_x[length - i - 1];
					snake_y[length - i] = snake_y[length - i - 1];
				}
				snake_y[0] += BS;	//뱀의 머리 y좌표를 BS만큼 +
			}

			if (snake_x[0] < 7) // 벽에 부딫혔을 때 게임 종료
				start = 0;
			else if (snake_x[0] > 593) // 벽에 부딫혔을 때 게임 종료
				start = 0;
			else if (snake_y[0] < 7) // 벽에 부딫혔을 때 게임 종료
				start = 0;
			else if (snake_y[0] > 555) // 벽에 부딫혔을 때 게임 종료
				start = 0;
		}
		if (wParam == 2 && start == 1) {
			length++;
		}

		for (int i = 0; i < 10; i++) {
			if (correct(food_x[i], food_y[i], snake_x[0], snake_y[0])) {
				food_x[i] = food_y[i] = 1000;
				eat++;
			}
		}
		
		if (eat == 9)
			start = 0;
		if (length == 50)
			start = 2;

		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_CHAR:	//s누르면 시작 e누르면 종료
		if (wParam == 115) {
			start = 1;
		}
		else if (wParam == 101) {
			start = 0;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TCHAR tmp[20];
		SetTextColor(hdc, fColor);
		if (start == -1)
			TextOut(hdc, 200, 250, "----- Press the 's' KEY -----", 28);

		else if (start == 1) {	//s누르고 시작할 때 먹이 랜덤 출력
			for (int i = 0; i < 9; i++) {
				TextOut(hdc, food_x[i], food_y[i], "T", 1);
			}
			Snake(hdc, length, snake_x, snake_y);
			wsprintf(tmp,"SCORE: %d", eat);
			TextOut(hdc,490, 10, tmp,lstrlen(tmp));
		}
		else if (start == 0) {
			TextOut(hdc, 250, 250, "GAME OVER", 9);
		}
		else if (start == 2) {
			TextOut(hdc, 250, 250, "TIME OVER", 9);
		}

		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
	
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}