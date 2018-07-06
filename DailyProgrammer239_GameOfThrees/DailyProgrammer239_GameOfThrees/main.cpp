//Daily Programmer challenge 239 - Game of Threes
//https://www.reddit.com/r/dailyprogrammer/comments/3r7wxz/20151102_challenge_239_easy_a_game_of_threes/
/*AIMS
-For any given starter number:
	-Try to divide by 3
	-If it is divisible by 3, do that. Else, add or subtract 1 to get a number divisble by 3
	-Output current number and whether 1, 0 or -1 is added before division by 3
	-Continue until 1 is reached
PLAN
-Use recursive function to carry out function
*/

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

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

void RunGame(int NumIn) {
	if (NumIn == 1) {
		std::cout << 1 << std::endl;
		return;
	}
	else if (NumIn % 3 == 0) {
		std::cout << NumIn << " " << 0 << std::endl;
		RunGame(NumIn / 3);
	}
	else {
		if ((NumIn + 1) % 3 == 0) {
			std::cout << NumIn << " " << 1 << std::endl;
			RunGame((NumIn + 1) / 3);
		}
		else {
			std::cout << NumIn << " " << -1 << std::endl;
			RunGame((NumIn - 1) / 3);
		}
	}
}

int main() {
	std::string UserInput;
	std::string ErrMessage{ "No error" };
	std::cout << "Enter a nice large integer of 1 or greater: ";
	std::getline(std::cin, UserInput);
	if (isInt(UserInput, ErrMessage)) {
		int UserInt{ std::stoi(UserInput) };
		if (UserInt < 1) {
			std::cout << "I said 1 or greater!" << std::endl;
		}
		else {
			RunGame(UserInt);
		}
	}
	else {
		std::cout << ErrMessage;
	}
	getchar();
	return 0;
}