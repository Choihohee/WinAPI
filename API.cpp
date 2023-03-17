#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
////Ÿ�� �̸� �صδ°� ����

LPCTSTR lpszClass = TEXT("Menu");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
        /*WINAPI: ������ ���α׷��̶�� �ǹ�
		hInstance: �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
		szCmdLine: Ŀ������ �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
		iCmdShow: �����찡 ȭ�鿡 ��µ� ����*/
{
   HWND	hwnd;	//HWND��� Ÿ������ hwnd���� ����
	MSG		msg;	//MSG��� Ÿ������ msg���� ����
	WNDCLASS WndClass;   
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;	//��������� ���� ä����
	WndClass.lpfnWndProc	= WndProc;      //��������� ���� ä����
	WndClass.cbClsExtra		= 0;      //��������� ���� ä����
	WndClass.cbWndExtra		= 0;      //��������� ���� ä����
	WndClass.hInstance		= hInstance;      //��������� ���� ä����
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);//��������� ���� ä����
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);   //��������� ���� ä����
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);   //��������� ���� ä����
	WndClass.lpszMenuName	= NULL;      //��������� ���� ä����
	WndClass.lpszClassName	= lpszClass;   //��������� ���� ä����
	RegisterClass(&WndClass);   //���� �׸�� �����쿡 ���   

  hwnd = CreateWindow//�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ��
		(lpszClass,				// ������ Ŭ���� �̸�
		lpszClass,				// ������ Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
		CW_USEDEFAULT,			// ������ ��ġ, x��ǥ
		CW_USEDEFAULT,			// ������ ��ġ, y��ǥ
		CW_USEDEFAULT,			// ������ ��
        CW_USEDEFAULT,			// ������ ����
        NULL,					// �θ� ������ �ڵ�
        NULL,					// �޴� �ڵ�
        hInstance,				// ���� ���α׷� ID
		NULL);					// ������ ������ ����
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
   HDC hdc; // ȭ���� �ֹε�Ϲ�ȣ
   PAINTSTRUCT ps; // ȭ���� ĥ�ϴ� ����
   static COLORREF fColor;
   static char lineBfr[20][256];
   static int row, col;

   switch (iMsg) 
   {
   case WM_CREATE:  // �ʱ�ȭ �Լ�, ���α׷� ������ �� �� �� �� �����.
      row = col = 0;
      // fColor = RGB(0,0,0); // ������ | R 1byte, G 1byte, B 1byte | ����� 255, 255, 255
      break;
   
   // WM_CREAT, WM_MOUSE... ��� �⺻������ ���� �͵��� ����.

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
      InvalidateRect(hwnd, NULL, TRUE); //(FALSE�� �ܻ� ����)
      break;

   case WM_PAINT: //ȭ�鿡 ����ϴ� �̺�Ʈ
      hdc = BeginPaint(hwnd, &ps); 
      // SetTextColor(hdc, fColor); // ������ �۾�
      // TextOut(hdc, 10, 10, "Hello Windows API Programming", 29);       
	  // TextOut(ȭ�� �ֹε�Ϲ�ȣ, x��ǥ, y��ǥ, ����� ���ڿ�, ���ڿ� ����);
      for(int i = 0; i < 20; i++){
         TextOut(hdc, 100, i*20, lineBfr[i], strlen(lineBfr[i]));
      }

      EndPaint(hwnd, &ps); //�ݵ�� �Է�
      break;
   case WM_DESTROY: //���α׷� ���� �� ���� �̺�Ʈ
      PostQuitMessage(0);
      break;
   } 
   return DefWindowProc(hwnd, iMsg, wParam, lParam); 
}