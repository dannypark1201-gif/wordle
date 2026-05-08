#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Loader.h"
#include "WordBank.h"
#include "WordleGame.h"

int main() {
    std::cout << "\n  +========================+\n";
    std::cout <<   "  |     W O R D L E       |\n";
    std::cout <<   "  +========================+\n";
    std::cout << "\n  Do you want to play? (y/n): ";

    std::string choice;
    std::getline(std::cin, choice);

    // trim + lowercase
    choice.erase(0, choice.find_first_not_of(" \t\r\n"));
    choice.erase(choice.find_last_not_of(" \t\r\n") + 1);
    std::transform(choice.begin(), choice.end(), choice.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (choice != "y") {
        std::cout << "\n  Maybe next time!\n\n";
        return 0;
    }

    std::cout << "\n  Loading dictionary... ";
    std::cout.flush();

    Loader loader;
    auto wordsByLength = loader.load("words_dictionary.json");

    std::cout << "Ready!\n";

    WordBank    bank(wordsByLength);
    WordleGame  game(bank);
    game.run();

    return 0;
}
