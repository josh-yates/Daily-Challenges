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
	-Use bitmap method to display the map and have text boxes for keeping track of time and resources
*/

#include <Windows.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ForestClasses.h"

const int WorldSize{ 50 };
HWND hParentWindow;

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

		//Resize window around client area and draw window below:
		//Display window
		hParentWindow = CreateWindowW(
			L"ParentWindowClass",		
			L"Pathfinder",				
			WS_SYSMENU | WS_VISIBLE,	
			100, 100,					
			100, 100,
			NULL, NULL, NULL, NULL);
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