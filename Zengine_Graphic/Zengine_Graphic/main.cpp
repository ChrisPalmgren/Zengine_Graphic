#include "windows.h"
#include "ZD3D.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Reserve memory for window instance
	HWND hWnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Fill WindowClass description and register
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";
	RegisterClassEx(&wc);

	// Adjust Window
	RECT wr = { 0, 0, 500, 400 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	// Create and show Window
	hWnd = CreateWindowEx
	(
		NULL,
		L"WindowClass",
		L"Zengine",
		WS_OVERLAPPEDWINDOW,
		300, 300, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, nShowCmd);

	// Initialize Direct3D
	ZD3D* p_ZD3D = new ZD3D;
	p_ZD3D->Initialize(hWnd);

	// Message Loop
	MSG msg;
	while (true)
	{
		// Check if there are messages waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
		}
		// Run Graphic code
		p_ZD3D->RenderFrame();
	}
	
	// Clean up DirectX and COM
	p_ZD3D->Clean();

	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}