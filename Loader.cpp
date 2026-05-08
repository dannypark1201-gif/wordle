#include "Loader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// ─────────────────────────────────────────
//  Parse plain text file.
//  Format: one word per line
//  e.g:  apple
//        brave
//        chess
// ─────────────────────────────────────────

bool Loader::isAllAlpha(const std::string& s) const {
    for (char c : s)
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    return !s.empty();
}

std::unordered_map<int, std::vector<std::string>>
Loader::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "  Error: cannot open " << filePath << "\n";
        std::cerr << "  Make sure the file is in the same folder as wordle.exe\n";
        exit(1);
    }

    std::unordered_map<int, std::vector<std::string>> result;
    std::string word;

    while (std::getline(file, word)) {
        // trim \r (Windows line endings)
        if (!word.empty() && word.back() == '\r')
            word.pop_back();

        // lowercase
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (isAllAlpha(word) && !word.empty()) {
            int len = static_cast<int>(word.size());
            result[len].push_back(word);
        }
    }

    return result;
}
