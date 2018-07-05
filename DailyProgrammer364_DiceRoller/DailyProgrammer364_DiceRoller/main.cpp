//Daily Programmer challenge 364 - Dice roller
//https://www.reddit.com/r/dailyprogrammer/comments/8s0cy1/20180618_challenge_364_easy_create_a_dice_roller/
/*AIMS
-Produce a number (dice output) from a dice description input: NdM (Dungeons and Dragons style, any-size dice)
-N is number of dice, M is number of sides
-Example: 4d6 (4 6-sided dice, can produce 1*4 to 6*4, ie 4 to 24)

-Extra challenge: Parse inputs so the program can't be crashed via input
*/

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ctime>
#include <cstdlib>

const int MaxDiceSides{ 100 };
const int MinDiceSides{ 2 };
const int MaxNumberDice{ 100 };
const int MinNumberDice{ 1 };


//TODO Move ValidateInt to input parsing library

//Function to check value is integer in a certain range
bool ValidateInt(const std::string InputToCheck, const int MinVal, const int MaxVal, std::string& ErrMessage) {
	//Auto remove spaces
	std::stringstream eolStream(InputToCheck);
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
	else if (TestDouble > static_cast<double>(MaxVal) || TestDouble < static_cast<double>(MinVal)) {
		ErrMessage = "Input outside of range";
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

int main() {
	try {
		//starting definitions
		std::string ErrMessage{ "No error" };
		int NumberDice;
		int DiceSides;
		srand(static_cast<unsigned int>(time(nullptr)));

		//Take input
		std::cout << "Please enter a value of NdM - N is number of dice, M is number of sides: ";
		std::string UserInput;
		std::getline(std::cin, UserInput);

		//split up into before 'd' and after 'd'
		std::string NumberDiceString, DiceSidesString;
		size_t dPos{ UserInput.find("d") };
		if (dPos == std::string::npos) {
			throw std::invalid_argument("'d' separator not found");
		}
		NumberDiceString = UserInput.substr(0, dPos);
		DiceSidesString = UserInput.substr(dPos + 1);

		if (!ValidateInt(NumberDiceString, MinNumberDice, MaxNumberDice, ErrMessage)) {
			throw std::invalid_argument("Number of dice error: " + ErrMessage);
		}
		else if (!ValidateInt(DiceSidesString, MinDiceSides, MaxDiceSides, ErrMessage)) {
			throw std::invalid_argument("Number of sides error: " + ErrMessage);
		}

		NumberDice = std::stoi(NumberDiceString);
		DiceSides = std::stoi(DiceSidesString);

		//generate number
		int MinRand{ 1 * NumberDice };
		int MaxRand{ NumberDice*DiceSides };
		int NumberOutput{ MinRand + (rand() % static_cast<int>(MaxRand - MinRand + 1)) };

		std::cout << "You rolled: " << NumberOutput << std::endl;
	}
	catch (std::invalid_argument& inval_arg) {
		std::cout << inval_arg.what() << std::endl;
	}
	getchar();
	return 0;
}