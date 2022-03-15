#include "CRectangle.h"
#include "CCircle.h"

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE
	hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWndClass";
	RegisterClass(&wc);

	hwnd = CreateWindow(
		"MyWndClass", // WNDCLASS name
		"SDK Application", // Window title
		WS_OVERLAPPEDWINDOW,// Window style
		CW_USEDEFAULT, // Horizontal position
		CW_USEDEFAULT, // Vertical position
		500, // Initial width
		500, // Initial height
		HWND_DESKTOP, // Handle of parent window
		NULL, // Menu handle
		hInstance, // Application's instance handle
		NULL // Window-creation data
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// Main.cpp
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	vector<CShape*> shapes;

	shapes.push_back(new CCircle({ 100, 100 }, 50));
	shapes.push_back(new CRectangle({ 300, 300 }, {100, 100 }));
	shapes.push_back(new CRectangle({ 200, 100 }, { 50, 150 }));
	shapes.push_back(new CCircle({ 100, 300 }, 150));
	shapes.push_back(new CRectangle({ 200, 200 }, { 200, 200 }));

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		/*RECT rect;
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "hello, Windows", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/

		for (auto shape : shapes)
		{
			shape->Draw(hdc);
		}
	
		for (auto shape : shapes)
		{
			delete shape;
			shape = NULL;
		}

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "haha", "Test!", MB_OK);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}