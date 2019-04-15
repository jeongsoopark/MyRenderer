#pragma once

#include <string>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;

class MyRenderer
{

public:

	MyRenderer(UINT _width, UINT _height);
	~MyRenderer();

	virtual bool onInit(HWND _hwnd);
	virtual void onUpdate();
	virtual void onDraw();
	virtual void onDestroy();

private:

	//FIXME : should viewport/windows size be in RenderBase class?
	//std::string mWindowTitle;
	UINT mViewportWidth;
	UINT mViewportHeight;
	float mAspectRatio;
	UINT mWindowWidth;
	UINT mWindowHeight;


	ComPtr<ID3D12Device> mDevice;
	ComPtr<ID3D12CommandQueue> mCommandQueue;
	ComPtr<IDXGISwapChain> mSwapChain;

	ComPtr<ID3D12DescriptorHeap> mRenderTargetHeap;
	ComPtr<ID3D12Resource> mRenderTarget;
	UINT mRenderTargetDescriptorSize;

	ComPtr<ID3D12GraphicsCommandList> mCommandList;
	ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	ComPtr<ID3D12RootSignature> mRootSignature;

};