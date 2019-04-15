// MyRenderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "MyRenderer.h"

MyRenderer::MyRenderer(UINT _width, UINT _height)
{
	mWindowWidth = _width;
	mWindowHeight = _height;
}

MyRenderer::~MyRenderer()
{
}

bool MyRenderer::onInit(HWND _hwnd)
{
	//dxgi factory creation
	UINT DXGIFactoryFlag = 0;
	ComPtr<IDXGIFactory2> factory;
	if (FAILED(CreateDXGIFactory2(DXGIFactoryFlag, IID_PPV_ARGS(&factory))))
	{
		return false;
	}

	//d3d device creation
	if (FAILED (D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mDevice))) )
	{
		return false;
	}

	//create command queue
	D3D12_COMMAND_QUEUE_DESC CommandQueueDesc = {};
	CommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	CommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	if (FAILED(mDevice->CreateCommandQueue(&CommandQueueDesc, IID_PPV_ARGS(&mCommandQueue))))
	{
		return false;
	}

	//create swapchain
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
//	SwapChainDesc.Width = mWindowWidth;
//	SwapChainDesc.Height = mWindowHeight;
//	SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.SampleDesc.Count = 1;

	ComPtr<IDXGISwapChain> SwapChain;
	if( FAILED(factory->CreateSwapChain( mCommandQueue.Get(), &SwapChainDesc, &SwapChain)) )
	{
		return false;
	}

	//CreateDescriptor Heap for render target view (RTV)
	D3D12_DESCRIPTOR_HEAP_DESC RenderTargetViewHeapDesc = {};
	RenderTargetViewHeapDesc.NumDescriptors = 1;
	RenderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RenderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	if ( FAILED(mDevice->CreateDescriptorHeap(&RenderTargetViewHeapDesc, IID_PPV_ARGS(&mRenderTargetHeap))) )
	{
		return false;
	}
	mRenderTargetDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//Create render target resource
	D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetHandle(mRenderTargetHeap->GetCPUDescriptorHandleForHeapStart());
	if (FAILED(mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mRenderTarget))) )
	{
		return false;
	}
	mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, RenderTargetHandle);

	//Create command allocator
	if (FAILED(mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCommandAllocator))) )
	{
		return false;
	}

	//Create main command list 
	if (FAILED(mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&mCommandList))))
	{
		return false;
	}
	mCommandList->Close();
	//Create depth buffer and its'view 

	return true;
}

void MyRenderer::onUpdate()
{
}

void MyRenderer::onDraw()
{
}

void MyRenderer::onDestroy()
{
}

int main()
{
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
