//Daily Programmer challenge 353 - Pancake Sorting
//https://www.reddit.com/r/dailyprogrammer/comments/82pt3h/20180307_challenge_353_intermediate/
/*AIMS
-Sort a stack of different sized pancakes from smallest (left) to largest (right)
-Can only flip substacks from top (left) to n pancakes down
-Try to make it as quick as possible (algorithm optimisation)

PLAN
-Winning conditions: a<b<c...<n
-Simple solution: find largest and flip to top, then flip stack to bottom. Repeat as necessary
*/

#include <iostream>
#include <vector>
#include <stdexcept>

#include <string>
#include <sstream>
#include <limits>

void printStack(std::vector<int>& Stack, int SeparatorPos) {
	for (auto Pancake{ Stack.begin() }; Pancake != Stack.end(); Pancake++) {
		std::cout << *Pancake << " ";
		if (Pancake - Stack.begin() == SeparatorPos) {
			std::cout << "| ";
		}
	}
	std::cout << std::endl << std::endl;
}

bool isInt(const std::string InputString, std::string& ErrMessage) {
	//Auto remove spaces
	std::stringstream eolStream(InputString);
	char BuffPeek;
	while ((BuffPeek = static_cast<char>(eolStream.peek())) == ' ') {
		eolStream.ignore(1, '\n');
	}
	//Auto remove eol, if present, then put it back on
	std::string DumpString;
	std::getline(eolStream, DumpString);
	//Put dumpstring and eol character in eolstream
	std::stringstream(DumpString + '\n').swap(eolStream);
	double TestDouble;
	eolStream >> TestDouble;
	if (eolStream.fail()) {
		eolStream.ignore(std::numeric_limits < std::streamsize>::max(), '\n');	//WARNING: if using windows.h, #define NOMINMAX
		ErrMessage = "Input contained non-numeric characters";
		return false;
	}
	//check if anything followed the number
	else if ((BuffPeek = static_cast<char>(eolStream.peek())) != '\n') {
		eolStream.ignore(std::numeric_limits < std::streamsize>::max(), '\n');	//WARNING: if using windows.h, #define NOMINMAX
		ErrMessage = "Input contained non-numeric characters";
		return false;
	}
	else {
		//split double into int and fraction parts
		double intPart, fractPart;
		fractPart = modf(TestDouble, &intPart);
		if (fractPart == 0.0) {
			return true;
		}
		else {
			ErrMessage = "Input not integer";
			return false;
		}
	}
}

bool isStackSorted(std::vector<int>& Stack) {
	if (Stack.size() == 0) {
		throw std::invalid_argument("Empty stack");
	}
	for (size_t i{ 0 }; i < Stack.size() - 1; i++) {
		if (!(Stack[i] <= Stack[i + 1])) {
			return false;
		}
	}
	return true;
}

int findLargest(std::vector<int>& Stack, int SubStackDepth) {
	if (Stack.size() == 0) {
		throw std::invalid_argument("Empty stack");
	}
	int largestPos{ 0 };
	int largestVal{ 0 };
	for (size_t i{ 0 }; i < (size_t)SubStackDepth; i++) {
		if (Stack[i] > largestVal) {
			largestVal = Stack[i];
			largestPos = i;
		}
	}
	return largestPos;
}

void flipSubstack(std::vector<int>& Stack, int Depth, int& FlipCount) {
	if ((size_t)Depth >= Stack.size()) {
		throw std::invalid_argument("Depth exceeds stack size");
	}
	std::vector<int> tempStack;
	for (int i{ Depth }; i >= 0;i--) {
		tempStack.push_back(Stack[i]);
	}
	for (size_t i{ (size_t)(Depth + 1) }; i < Stack.size(); i++) {
		tempStack.push_back(Stack[i]);
	}
	std::swap(tempStack, Stack);
	FlipCount++;
}

void sortStack(std::vector<int>& Stack, int OperatingDepth, int& FlipCount) {
	int largestPos{ findLargest(Stack, OperatingDepth) };
	if (largestPos > 0 && largestPos < OperatingDepth-1) {
		printStack(Stack, largestPos);
		flipSubstack(Stack, largestPos, FlipCount);
	}
	if (largestPos < OperatingDepth-1) {
		printStack(Stack, OperatingDepth - 1);
		flipSubstack(Stack, OperatingDepth - 1, FlipCount);
	}
	std::cout << std::endl;
}

int main() {
	try {
		//take input
		std::cout << "Input pancake stack one pancake at a time, enter x to end" << std::endl;
		std::vector<int> Stack;
		bool takeInput{ true };
		int FlipCount{ 0 };
		std::string errMessage{ "No error" };
		while (takeInput) {
			std::string UserInput;
			std::cout << "Pancake size: ";
			std::getline(std::cin, UserInput);
			if (UserInput == "x" || UserInput == "X") {
				takeInput = false;
			}
			else if (!isInt(UserInput, errMessage)) {
				throw std::invalid_argument(errMessage);
			}
			else if (std::stoi(UserInput) < 1) {
				throw std::invalid_argument("Input must be greater than size 1");
			}
			else {
				Stack.push_back(std::stoi(UserInput));
			}
		}
		bool sorted{ false };
		int OperatingDepth{ (int)Stack.size() };
		printStack(Stack, Stack.size());
		while (!sorted) {
			if (isStackSorted(Stack)) {
				sorted = true;
			}
			else {
				sortStack(Stack,OperatingDepth, FlipCount);
				OperatingDepth -= 1;
			}
		}
		std::cout << "Finished in " << FlipCount << " flips: ";
		printStack(Stack, Stack.size());
	}
	catch (std::invalid_argument& inval_arg) {
		std::cout << "Error: " << inval_arg.what() << std::endl;
	}
	getchar();
	return 0;
}