#pragma once
#include "WordBank.h"
#include "Evaluator.h"
#include "Display.h"
#include <random>

// ─────────────────────────────────────────
//  WordleGame
//  Orchestrates the full game loop.
//  N-letter word -> N+2 guesses.
// ─────────────────────────────────────────
class WordleGame {
public:
    explicit WordleGame(WordBank& bank);

    void play();   // one round
    void run();    // loop with replay

private:
    WordBank&  _bank;
    Evaluator  _evaluator;
    Display    _display;
    std::mt19937 _rng;

    int         maxGuesses(int wordLength) const;
    const char* winMessage(int attempt) const;

    static std::string toLower(std::string s);
    static std::string toUpper(std::string s);
    static bool        isAlpha(const std::string& s);
    static std::string trim(std::string s);
};
