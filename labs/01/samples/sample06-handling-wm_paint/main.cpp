#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

TCHAR const CLASS_NAME[] = _T("MainWndClass");
TCHAR const WINDOW_TITLE[] = _T("My first window");

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MainLoop();
bool RegisterWndClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	// ������������ ����� �������� ����
	if (!RegisterWndClass(hInstance))
	{
		return 1;
	}

	// ������� ������� ���� ����������
	HWND hMainWindow = CreateMainWindow(hInstance);
	if (hMainWindow == NULL)
	{
		return 1;
	}
	
	// ���������� ������� ���� ����������
	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	// ��������� ���� ������� ���������, ���� �� ������� 
	// ������ � ���������� ����������
	return MainLoop();
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hMainWindow = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hMainWindow;
}

int MainLoop()
{
	MSG msg;
	BOOL res;
	while ((res = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (res == -1)
		{
			// ��������� ������ - ����� ���������� �� �, ��������,
			// ��������� ������ ����������
		}
		else
		{
			// ���� ��� ��������� � ������� ����������� �������,
			// �� ��������� � ������� ��������� ���������, ������� ���������� �
			// ���� ��������� ������������� �������
			TranslateMessage(&msg);
			// �������� ��������� � ��������������� ������� ���������
			DispatchMessage(&msg);
		}
	}

	// ���� �� ������� ������ � ��� ������ ���������� ��������� WM_QUIT
	// msg.wParam �������� ��� ��������, ���������� ��� ������ ������� PostQuitMessage()
	return msg.wParam;
}

void OnDestroy(HWND /*hWnd*/)
{
	PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	// ������� ������� ����
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// ������� ������ �����
	LOGBRUSH brushInfo;
	brushInfo.lbStyle = BS_SOLID;
	brushInfo.lbColor = RGB(255, 255, 0);
	brushInfo.lbHatch = 0;
	HBRUSH brush = CreateBrushIndirect(&brushInfo);

	// �������� ���� � ����� � ��������� ����������, ��������� ����� ��������� �������
	HPEN oldPen = SelectPen(dc, pen);
	HBRUSH oldBrush = SelectBrush(dc, brush);

	Ellipse(dc,		// ���������� ��������� ����������
		100, 50,	// x � y �������� ������ ���� ��������������� ��������������
		250, 150	// x � y ������� ������� ���� ��������������� ��������������
		);

	// �������� ����� ����������� ������� GDI � ��������� ����������
	// ��� ���� pen � brush ������������� ���������� � ��� �� �������
	SelectPen(dc, oldPen);
	SelectBrush(dc, oldBrush);

	// ������� GDI ����� ������� ���� ��� �� ������� �� � ����� �� ����������
	DeletePen(pen);
	DeleteBrush(brush);

	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass =
	{
		sizeof(wndClass),	//UINT cbSize;
		CS_HREDRAW | CS_VREDRAW, //UINT style;
		&WindowProc,		//WNDPROC lpfnWndProc;
		0,					//int cbClsExtra;
		0,					//int cbWndExtra;
		hInstance,			//HINSTANCE hInstance;
		NULL,				//HICON hIcon;
		LoadCursor(NULL, IDC_ARROW), //HCURSOR hCursor;
		(HBRUSH)(COLOR_BTNFACE + 1), //HBRUSH hbrBackground;
		NULL,				//LPCTSTR lpszMenuName;
		CLASS_NAME,			//LPCTSTR lpszClassName;
		NULL,				//HICON hIconSm;
	};

	return RegisterClassEx(&wndClass) != FALSE;
}

