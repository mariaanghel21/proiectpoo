#pragma once
#include <cstring>
#include <string.h>

class Word {
private:
    std::string word;
    std::string guessed;

public:
    Word(const std::string& word) : word(word), guessed(word.size(), '_') {}

    bool guessLetter(char letter) {
        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }
        return found;
    }

    bool isComplete() const { return guessed == word; }

    friend std::ostream& operator<<(std::ostream& os, const Word& word) {
        os << "Current Word: " << word.guessed;
        return os;
    }
};
