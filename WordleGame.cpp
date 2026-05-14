#include "WordleGame.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <ctime>

WordleGame::WordleGame(WordBank& bank)
    : _bank(bank)
    , _rng(static_cast<unsigned>(std::time(nullptr)) + 42)
{}

int WordleGame::maxGuesses(int wordLength) const {
    return wordLength + 1;
}

const char* WordleGame::winMessage(int attempt) const {
    switch (attempt) {
        case 1:  return "Genius!";
        case 2:  return "Magnificent!";
        case 3:  return "Impressive!";
        case 4:  return "Splendid!";
        case 5:  return "Great!";
        case 6:  return "Phew!";
        default: return "Nice!";
    }
}

std::string WordleGame::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return s;
}

std::string WordleGame::toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::toupper(c); });
    return s;
}

bool WordleGame::isAlpha(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(),
        [](unsigned char c){ return std::isalpha(c); });
}

std::string WordleGame::trim(std::string s) {
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    auto last = s.find_last_not_of(" \t\r\n");
    if (last != std::string::npos) s.erase(last + 1);
    else s.clear();
    return s;
}

void WordleGame::play() {
    // Fixed 5-letter word
    int wordLength = 5;

    std::string answer = _bank.getRandom(wordLength);
    int maxG           = maxGuesses(wordLength);

    // Header
    std::cout << "\n";
    for (int i = 0; i < 40; ++i) std::cout << "-";
    std::cout << "\n  WORDLE  |  " << wordLength
              << " letters  |  " << maxG << " guesses\n";
    for (int i = 0; i < 40; ++i) std::cout << "-";
    std::cout << "\n\n  Guess the " << wordLength << "-letter word!\n";

    using Entry = std::pair<std::string, std::vector<LetterState>>;
    std::vector<Entry> history;
    _display.showBoard(history, wordLength, maxG);

    for (int attempt = 1; attempt <= maxG; ++attempt) {
        std::string raw;

        // Input loop – keep asking until valid
        while (true) {
            std::cout << "  Guess " << attempt << "/" << maxG << ": ";
            std::getline(std::cin, raw);
            raw = trim(toLower(raw));

            if (static_cast<int>(raw.size()) != wordLength)
                std::cout << "  X Must be " << wordLength << " letters.\n";
            else if (!isAlpha(raw))
                std::cout << "  X Letters only.\n";
            else if (!_bank.isValid(raw))
                std::cout << "  X Not a valid word.\n";
            else
                break;
        }

        auto result = _evaluator.evaluate(raw, answer);
        history.emplace_back(raw, result);
        _display.showBoard(history, wordLength, maxG);

        bool won = std::all_of(result.begin(), result.end(),
            [](LetterState s){ return s == LetterState::CORRECT; });

        if (won) {
            std::cout << "  " << winMessage(attempt)
                      << " The word was " << toUpper(answer) << ".\n\n";
            return;
        }
    }

    std::cout << "  X The word was " << toUpper(answer)
              << ". Better luck next time!\n\n";
}

void WordleGame::run() {
    while (true) {
        play();
        std::cout << "  Play again? (y/n): ";
        std::string again;
        std::getline(std::cin, again);
        again = trim(toLower(again));
        if (again != "y") {
            std::cout << "\n  Thanks for playing!\n\n";
            break;
        }
    }
}
