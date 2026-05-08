#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>

// ─────────────────────────────────────────
//  WordBank
//  Stores words by length.
//  Picks a random word and validates guesses.
// ─────────────────────────────────────────
class WordBank {
public:
    explicit WordBank(
        const std::unordered_map<int, std::vector<std::string>>& wordsByLength);

    std::string getRandom(int length);
    bool        isValid(const std::string& word) const;

private:
    std::unordered_map<int, std::vector<std::string>>    _byLength;
    std::unordered_map<int, std::unordered_set<std::string>> _sets;
    std::mt19937 _rng;
};
