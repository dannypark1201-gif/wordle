#include "WordBank.h"
#include <stdexcept>
#include <ctime>

WordBank::WordBank(
    const std::unordered_map<int, std::vector<std::string>>& wordsByLength)
    : _byLength(wordsByLength)
    , _rng(static_cast<unsigned>(std::time(nullptr)))
{
    for (const auto& [len, words] : _byLength)
        _sets[len] = std::unordered_set<std::string>(words.begin(), words.end());
}

std::string WordBank::getRandom(int length) {
    auto it = _byLength.find(length);
    if (it == _byLength.end() || it->second.empty())
        throw std::runtime_error("No words of length " + std::to_string(length));

    std::uniform_int_distribution<size_t> dist(0, it->second.size() - 1);
    return it->second[dist(_rng)];
}

bool WordBank::isValid(const std::string& word) const {
    auto it = _sets.find(static_cast<int>(word.size()));
    if (it == _sets.end()) return false;
    return it->second.count(word) > 0;
}
