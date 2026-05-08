#include "Evaluator.h"

std::vector<LetterState> Evaluator::evaluate(const std::string& guess,
                                              const std::string& answer) const {
    int len = static_cast<int>(guess.size());
    std::vector<LetterState> result(len, LetterState::ABSENT);
    std::vector<bool> used(len, false);

    // Pass 1 – exact matches
    for (int i = 0; i < len; ++i) {
        if (guess[i] == answer[i]) {
            result[i] = LetterState::CORRECT;
            used[i]   = true;
        }
    }

    // Pass 2 – present (right letter, wrong position)
    for (int i = 0; i < len; ++i) {
        if (result[i] == LetterState::CORRECT) continue;
        for (int j = 0; j < len; ++j) {
            if (answer[j] == guess[i] && !used[j]) {
                result[i] = LetterState::PRESENT;
                used[j]   = true;
                break;
            }
        }
    }

    return result;
}
