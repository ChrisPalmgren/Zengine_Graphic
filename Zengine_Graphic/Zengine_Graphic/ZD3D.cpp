#include "ZD3D.h"

void ZD3D::Initialize(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	SwapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.SampleDesc.Count = 4;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext
	);

	// Receive the address of the backbuffer from the swapchain
	ID3D11Texture2D* pTexture2D;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D);

	// Create COM-Object to represent rendertarget
	m_pDevice->CreateRenderTargetView(pTexture2D, NULL, &m_pBackBuffer);
	pTexture2D->Release();

	// Set this rendertarget as backbuffer
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);

	// Set Viewport
	D3D11_VIEWPORT Viewport;
	ZeroMemory(&Viewport, sizeof(D3D11_VIEWPORT));

	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = SCREEN_WIDTH;
	Viewport.Height = SCREEN_HEIGHT;

	m_pDeviceContext->RSSetViewports(1, &Viewport);
}

void ZD3D::Clean()
{
	m_pSwapChain->SetFullscreenState(false, NULL);

	m_pSwapChain->Release();
	m_pBackBuffer->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
}

void ZD3D::RenderFrame()
{
	// Clear backbuffer to display a color
	float fClearColor[4] = { 1.0, 0.0, 0.0, 1.0 };
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, fClearColor);

	// 3D Rendering on backbuffer goes here
	// ...

	m_pSwapChain->Present(0, 0);
}
