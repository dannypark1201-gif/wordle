#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// ─────────────────────────────────────────
//  Loader
//  Reads words_dictionary.json and builds
//  word lists grouped by length (3–8).
// ─────────────────────────────────────────
class Loader {
public:
    // Returns map: length -> list of words
    std::unordered_map<int, std::vector<std::string>>
        load(const std::string& filePath);

private:
    bool isAllAlpha(const std::string& s) const;
};
