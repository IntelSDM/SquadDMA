#include "pch.h"
#include "Memory.h"
#include "CheatFunction.h"
#include "Globals.h"
#include "Init.h"
#include "GUI.h"
#include "Engine.h"
std::shared_ptr<Engine> EngineInstance;
std::string ProcessName;
std::atomic<int> LocalPlayerTeamID;
void main()
{
	bool gamefound = true;
	ProcessName = LIT("SquadGame.exe");
	TargetProcess.Init(ProcessName);
	
	TargetProcess.FixCr3();

	EngineInstance = std::make_shared<Engine>();
	EngineInstance->Cache();

	

	//uint64_t persistentlevel = 0x190;
	//persistentlevel = TargetProcess.Read<uint64_t>(gobjects + gameinstance);
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputWndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
std::shared_ptr<CheatFunction> Cache = std::make_shared<CheatFunction>(3000, [] {
	//	if (!EngineInstance)
	//	{
	//		EngineInstance = std::make_shared<Engine>();
	//		return;
	//	}

	if (EngineInstance->GetActorSize() <= 0)
	{
		EngineInstance = std::make_shared<Engine>();
	}
	EngineInstance->Cache();
	});

void CachingThread()
{
	while (true)
	{
		Cache->Execute();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, LIT("CONIN$"), LIT("r"), stdin);
	freopen_s(&fDummy, LIT("CONOUT$"), LIT("w"), stderr);
	freopen_s(&fDummy, LIT("CONOUT$"), LIT("w"), stdout);
	printf(LIT("Debugging Window:\n"));

	main();
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"GUI Framework";
	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, L"GUI Framework",
		WS_POPUP,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return -1;


	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	ShowWindow(hWnd, nCmdShow);

	InitD2D(hWnd);
	CreateGUI();
	MSG msg;
	SetProcessDPIAware();
	SetInput();
	std::thread cache(CachingThread);
	cache.detach();
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		RenderFrame();
	}
	CleanD2D();
	return msg.wParam;
}
