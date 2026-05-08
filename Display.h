#pragma once
#include "Evaluator.h"
#include <string>
#include <vector>

// ─────────────────────────────────────────
//  Display
//  Renders the game board to the console.
//
//  CORRECT  →   A   (plain letter)
//  PRESENT  →  (A)  (parentheses)
//  ABSENT   →   _   (blank)
// ─────────────────────────────────────────
class Display {
public:
    void showBoard(
        const std::vector<std::pair<std::string, std::vector<LetterState>>>& history,
        int wordLength,
        int maxGuesses) const;

private:
    std::string renderGuess(const std::string& guess,
                            const std::vector<LetterState>& result) const;
    std::string renderBlank(int length) const;
};
