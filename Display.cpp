#include "Display.h"
#include <iostream>
#include <cctype>

std::string Display::renderGuess(const std::string& guess,
                                  const std::vector<LetterState>& result) const {
    std::string out;
    for (int i = 0; i < static_cast<int>(guess.size()); ++i) {
        char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(guess[i])));
        if (result[i] == LetterState::CORRECT)
            out += std::string(" ") + ch + " ";
        else if (result[i] == LetterState::PRESENT)
            out += std::string("(") + ch + ")";
        else
            out += " _ ";

        if (i + 1 < static_cast<int>(guess.size())) out += " ";
    }
    return out;
}

std::string Display::renderBlank(int length) const {
    std::string out;
    for (int i = 0; i < length; ++i) {
        out += " _ ";
        if (i + 1 < length) out += " ";
    }
    return out;
}

void Display::showBoard(
    const std::vector<std::pair<std::string, std::vector<LetterState>>>& history,
    int wordLength,
    int maxGuesses) const
{
    std::cout << "\n";
    for (const auto& [guess, result] : history)
        std::cout << "  " << renderGuess(guess, result) << "\n";

    int remaining = maxGuesses - static_cast<int>(history.size());
    for (int i = 0; i < remaining; ++i)
        std::cout << "  " << renderBlank(wordLength) << "\n";

    std::cout << "\n";
}
