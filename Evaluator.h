#pragma once
#include <string>
#include <vector>

enum class LetterState { CORRECT, PRESENT, ABSENT };

// ─────────────────────────────────────────
//  Evaluator
//  Compares a guess against the answer.
//  Uses two-pass algorithm to handle
//  duplicate letters correctly.
// ─────────────────────────────────────────
class Evaluator {
public:
    std::vector<LetterState> evaluate(const std::string& guess,
                                      const std::string& answer) const;
};
