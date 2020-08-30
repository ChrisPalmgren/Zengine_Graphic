#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <d3d11.h>

class ZD3D
{
public:
	void Initialize(HWND hWnd);
	void Clean();

	void RenderFrame();

private:
	IDXGISwapChain* m_pSwapChain;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	ID3D11RenderTargetView* m_pBackBuffer;
};

