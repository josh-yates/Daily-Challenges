//Daily Programmer challenge 361 - Tally program
//https://www.reddit.com/r/dailyprogrammer/comments/8jcffg/20180514_challenge_361_easy_tally_program/
/*AIMS
-5 players (a-e) play a game and input their scores as a string
-Capital letter for lossing a point, lowercase for gaining a point, eg: aAbbDeEc
-Output as a tally with highest score to lowest score
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

int main() {
	try {
		//take input
		std::string UserInput;
		std::cout << "Please enter the scores: ";
		std::getline(std::cin, UserInput);
		if (UserInput.empty()) {
			throw std::invalid_argument("Invalid input: No input");
		}
		//make lowercase copy
		std::string LowerCopy{ UserInput };
		std::transform(LowerCopy.begin(), LowerCopy.end(), LowerCopy.begin(), ::tolower);

		//count storage
		std::map<char, int> CountStorage{
			std::make_pair('a',0),
			std::make_pair('b',0),
			std::make_pair('c',0),
			std::make_pair('d',0),
			std::make_pair('e',0)
		};
		auto InputIter{ UserInput.begin() };
		for (auto LowerIter{ LowerCopy.begin() }; LowerIter != LowerCopy.end(); LowerIter++, InputIter++) {
			if (CountStorage.find(*LowerIter) == CountStorage.end()) {
				throw std::invalid_argument("Invalid input; character not a-e");
			}
			//if lowercase, increase the score
			if (*LowerIter == *InputIter) {
				CountStorage[*LowerIter] += 1;
			}
			else {
				CountStorage[*LowerIter] -= 1;
			}
		}
		//transfer to vector for sorting and output
		std::vector<std::pair<char, int>> Results;
		for (auto StorageIter{ CountStorage.begin() }; StorageIter != CountStorage.end(); StorageIter++) {
			Results.push_back(std::make_pair(StorageIter->first, StorageIter->second));
		}
		std::sort(Results.begin(), Results.end(), [](std::pair<char, int> a, std::pair<char, int> b) {return a.second > b.second; });
		for (auto ResultsIter{ Results.begin() }; ResultsIter != Results.end(); ResultsIter++) {
			std::cout << ResultsIter->first << ": " << ResultsIter->second << std::endl;
		}
	}
	catch (std::invalid_argument& inval_arg) {
		std::cout << inval_arg.what() << std::endl;
	}
	getchar();
	return 0;
}