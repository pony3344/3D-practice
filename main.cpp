#include <iostream>
#include "D3D9App.h"
#include <windows.h>
#include <strsafe.h>
#include "SubMesh.h"


void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
using std::cout;
using std::endl;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND createWindow(LPCSTR title, UINT width, UINT height);

int main()
{

	HWND hWnd = createWindow("Direct3D9", 800, 600);
	
	if (hWnd)
	{
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}
	D3D9App* d3dApp = new D3D9App();
	d3dApp->createD3D9(hWnd, 800, 600);

	SubMesh* mesh = new SubMesh(d3dApp->getD3DDevice9());
	PolygonFace* face = mesh->createPolygons(
		VertexPT(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		VertexPT(1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
		VertexPT(1.0f, -1.0f, 1.0f, 1.0f, 0.0f),
		VertexPT(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f));

	d3dApp->addInterface(face->getVertexBuffer());

	cout << "Num vertices: " << face->getNumVertices() << endl;

	MSG msg = {};
	bool running = true;
	while (running)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				running = false;
			}
		}

		d3dApp->clear(0, 255, 0, 100, 255);
		d3dApp->begin();

		D3DXMATRIX pView;
		D3DXMATRIX pProjection;
		D3DXMATRIX pWorld;

		D3DXVECTOR3 pEye(0.0, 0.0, 5.0);
		D3DXVECTOR3 pAt(0.0, 0.0, 0.0);
		D3DXVECTOR3 pUp(0.0, 1.0, 0.0);
		D3DXMatrixLookAtLH(&pView,
			&pEye,
			&pAt,
			&pUp);

		d3dApp->getD3DDevice9()->SetTransform(D3DTS_VIEW, &pView);

		D3DXMatrixPerspectiveFovLH(&pProjection, 75.0f, 1.33f, 5.0f, 30.0f);

		d3dApp->getD3DDevice9()->SetTransform(D3DTS_PROJECTION, &pProjection);

		D3DXMatrixTranslation(&pWorld, 0.0f, 0.0f, 0.0f);
		d3dApp->getD3DDevice9()->SetTransform(D3DTS_WORLD, &pWorld);
		mesh->drawSubMesh(0);

		d3dApp->end();
		d3dApp->present();
	}

	if (d3dApp->destroyAllInterfaces())
	{
		delete d3dApp;
		d3dApp = 0;
		cout << "Memory freed." << endl;
	}
	return EXIT_SUCCESS; 
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND createWindow(LPCSTR title, UINT width, UINT height)
{
	WNDCLASSEX winClassEx;
	ZeroMemory(&winClassEx, sizeof(WNDCLASSEX));

	winClassEx.cbSize = sizeof(winClassEx);

	winClassEx.style = CS_HREDRAW | CS_HREDRAW;
	winClassEx.lpfnWndProc = WinProc;
	winClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winClassEx.hInstance = GetModuleHandle(NULL);
	winClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClassEx.lpszClassName = title;

	if (!RegisterClassEx(&winClassEx))
	{
		MessageBox(NULL, "Cannot create Window.", "Cannot create Window.", MB_OK);
	}


	return CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, 
		title, 
		title, 
		WS_OVERLAPPEDWINDOW, 
		0, 
		0, 
		width, 
		height, 
		NULL, 
		NULL, 
		GetModuleHandle(NULL), 
		NULL);
}