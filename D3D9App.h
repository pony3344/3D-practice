#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <stack>

using std::stack;

#pragma comment(lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "dxerr.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

typedef stack<IUnknown*> InterUnknown;
class D3D9App
{
protected:
	IDirect3D9* m_pD3D9;
	IDirect3DDevice9* m_pD3DDevice9;
	D3DPRESENT_PARAMETERS m_pPresent_parameters;
	HWND m_pHWND;
	UINT m_pWidth;
	UINT m_pHeight;
	bool m_pFullscreen;
	InterUnknown m_pInterfaces;
public:
	D3D9App();

	~D3D9App();

	bool createD3D9(HWND hWnd, UINT width, UINT height, bool fullScreen = false);

	void clear(UINT buffer, BYTE Alpha, BYTE Red, BYTE Green, BYTE Blue);

	void begin();

	void end();

	void present();

	void addInterface(IUnknown* inter);

	bool destroyAllInterfaces();

	IDirect3D9* getD3D9() const { return this->m_pD3D9; }

	IDirect3DDevice9* getD3DDevice9() const { return this->m_pD3DDevice9; }

	D3DPRESENT_PARAMETERS getDeviceParameters() const { return this->m_pPresent_parameters; }

	HWND getWindowHandle() const { return this->m_pHWND; }

	UINT getWindowWidth() const { return this->m_pWidth; }

	UINT getWindowHeight() const { return this->m_pHeight; }

	bool getFullscreen() const { return this->m_pFullscreen; }
};

