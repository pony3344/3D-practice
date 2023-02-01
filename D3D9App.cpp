#include "D3D9App.h"

D3D9App::D3D9App()
{
	this->m_pD3D9 = NULL;				// Direct3D9 interface.
	this->m_pD3DDevice9 = NULL;			// Direct3D9 Device interface.
	this->m_pPresent_parameters = {};	// Direct3D9 present parameters.
	this->m_pWidth = 1;					// Width.
	this->m_pHeight = 1;				// Height.
	this->m_pFullscreen = false;		// Fullscreen.
	this->m_pHWND = 0;					// Window handle.
}

D3D9App::~D3D9App()
{
	
}

bool D3D9App::createD3D9(HWND hWnd, UINT width, UINT height, bool fullScreen)
{
	// set class variable to function variable.
	this->m_pHWND = hWnd;				
	this->m_pWidth = width;
	this->m_pHeight = height;
	this->m_pFullscreen = fullScreen;

	// Create D3D9.
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D9 == NULL)
	{
		MessageBox(NULL, "D3D9Driver cannot be access", "Error: ", MB_OK | MB_ICONERROR);
		return false;
	}
	else
	{
		this->m_pInterfaces.push(m_pD3D9);
	}

	ZeroMemory(&m_pPresent_parameters, sizeof(D3DPRESENT_PARAMETERS));

	m_pPresent_parameters.BackBufferCount = 3;
	m_pPresent_parameters.BackBufferWidth = m_pWidth;
	m_pPresent_parameters.BackBufferHeight = m_pHeight;
	m_pPresent_parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_pPresent_parameters.Windowed = (!m_pFullscreen);
	m_pPresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pPresent_parameters.EnableAutoDepthStencil = TRUE;
	m_pPresent_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_pPresent_parameters.hDeviceWindow = m_pHWND;

	HRESULT hr = m_pD3D9->CreateDevice(0,		// Adaptor. Generally the main one.
		D3DDEVTYPE_HAL,							// Hardware layer.
		m_pHWND,								// Window.
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// Hardware vertex processing.
		&m_pPresent_parameters,					// present parameters. 
		&m_pD3DDevice9);						// Direct3D9 device.

	if (FAILED(hr))
	{
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Device not created.", MB_OK);
		return false;
	}
	else
	{
		this->m_pInterfaces.push(m_pD3DDevice9);
		return true;
	}


	return true;
}

void D3D9App::clear(UINT buffer, BYTE Alpha, BYTE Red, BYTE Green, BYTE Blue)
{
	DWORD ClearBuffer = 0;
	switch (buffer)
	{
	case 0:
		ClearBuffer |= D3DCLEAR_TARGET;
		break;
	case 1:
		ClearBuffer |= D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		break;
	case 2:
		ClearBuffer |= D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
		break;
	}
	m_pD3DDevice9->Clear(0, 0, ClearBuffer, D3DCOLOR_ARGB(Alpha, Red, Green, Blue), 1.0f, 1);

}

void D3D9App::begin()
{
	m_pD3DDevice9->BeginScene();
}

void D3D9App::end()
{
	m_pD3DDevice9->EndScene();
}

void D3D9App::present()
{
	m_pD3DDevice9->Present(0, 0, 0, 0);
}

void D3D9App::addInterface(IUnknown* inter)
{
	this->m_pInterfaces.push(inter);
}

bool D3D9App::destroyAllInterfaces()
{
	while (!m_pInterfaces.empty())
	{
		IUnknown* i = m_pInterfaces.top();
		if (i != NULL)
		{
			i->Release();
			i = 0;
		}
		m_pInterfaces.pop();
	}
	return (m_pInterfaces.empty() == true);
}