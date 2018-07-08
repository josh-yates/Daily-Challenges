//Daily programmer challenge 165 - Simulated ecology - The forest
//https://www.reddit.com/r/dailyprogrammer/comments/27h53e/662014_challenge_165_hard_simulated_ecology_the/
/*AIMS
-Simulate a forest containg saplings, trees, elder trees, lumberjacks and bears
-Time is dictated by ticks lasting 1 month
-Take into account interactions and growth:
	-Every month, trees have a 10% chance of spawning saplings in the 8 surrounding tiles, if free
	-Every month, elder trees have a 20% chance of spawning saplings in the 8 surrounding tiles, if free
	-After 12 months, a sapling turns into a tree
	-After 120 months, a tree turns into an elder tree
	-Lumberjacks can move 3 steps in random directions each month
	-If a lumberjack encounters a tree, he will stop and chop it down
	-1 tree = 1 lumber, 1 elder tree= 2 lumber
	-Every 12 months, the amount of lumber is compared to number of lumberjacks
	-A new lumberjack is hired for every 10 lots of lumber more than there are lumberjacks, eg 10-19: hire 1 lumberjack
	-If the amount of lumber is below number of lumberjacks, let 1 go for every 10 below but do not reach 0
	-Bears move 5 random steps each month
	-If a bear meets a lumberjack, remove the lumberjack - "maw" incident
	-If there are no maws after a year add a bear, else remove a bear (hunted)
	-If the bears maw the last lumberjack, immediately replace him
-End conditions:
	-4800 months pass
	-Or 0 trees of any kind left

PLAN
	-Use OOP to create classes for map (2d array), bears, trees etc.
	-Have map as local reference and time as local reference
	-Use vectors of smart pointers to keep track of objects
	-Updated display method: use direct2D from previous game graphics engine to display shapes in a grid
*/

#include <Windows.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ForestClasses.h"
#include "Graphics.h"

const int WorldSize{ 50 };
const int ParentClientSize{ WorldSize * 15 };
HWND hParentWindow;
GraphicsEngine* Graphics;

//Function to convert string to wstring
std::wstring StringToWstring(const std::string StringIn) {
	std::wstring Converted(StringIn.length(), L' ');
	std::copy(StringIn.begin(), StringIn.end(), Converted.begin());
	return Converted;
}

LRESULT CALLBACK ParentWindowProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	try {
		//Generate clock and map
		GameClock WorldClock;
		Forest::ForestMap WorldMap(WorldSize, WorldClock);

		//Register window
		WNDCLASSW ParentWindowClass{ 0 };
		ParentWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		ParentWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		ParentWindowClass.hInstance = hInst;
		ParentWindowClass.lpszClassName = L"ParentWindowClass";
		ParentWindowClass.lpfnWndProc = ParentWindowProcedure;

		if (!RegisterClassW(&ParentWindowClass)) {
			throw std::invalid_argument("Unable to register parent window class");
		}

		RECT ParentClientRect = { 0,0,ParentClientSize,ParentClientSize };
		AdjustWindowRect(&ParentClientRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, false);

		//Resize window around client area and draw window below:
		//Display window
		hParentWindow = CreateWindowW(
			L"ParentWindowClass",		
			L"Forest Simulation",				
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			100, 100,					
			ParentClientRect.right-ParentClientRect.left, 
			ParentClientRect.bottom-ParentClientRect.top,
			nullptr, nullptr, nullptr, nullptr);

		//Initialise graphics engine
		Graphics = new GraphicsEngine();
		if (!Graphics->Init(hParentWindow)) {
			delete Graphics;
			throw std::invalid_argument("Unable to initialise graphics");
		}

		//Message loop
		MSG Message{ 0 };

		while (GetMessage(&Message, NULL, NULL, NULL)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);	
		}

		//Clean up memory
		delete Graphics;

	}
	//catch errors and put in message box
	catch (std::invalid_argument& inval_arg) {
		MessageBox(nullptr, StringToWstring(inval_arg.what()).c_str(), L"Programming error", MB_ICONERROR);
	}
	catch (...) {
		MessageBox(nullptr, L"Unknown error", L"Programming error", MB_ICONERROR);
	}
	return 0;
}

LRESULT CALLBACK ParentWindowProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	//TODO move drawing to while message loop
	case WM_PAINT:
		Graphics->BeginDraw();
		Graphics->ClearScreen(0.2, 0.9, 0.2);
		Graphics->EndDraw();
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
		return 0;
	default:
		return DefWindowProcW(hWnd, message, wp, lp);
		break;
	}
}