#pragma once

#include "HangmanGame.h"

class EasyModeHangman : public HangmanGame {
public:
    EasyModeHangman(const Player& player, const std::string& word, int maxGuesses)
        : HangmanGame(player, word, maxGuesses, 1) {}

    void play(int level) override {
        char guess;
        while (!word.isComplete() && stats.hasGuessesLeft()) {
            std::cout << *this << "\nEnter your guess: ";
            std::cin >> guess;

            if (!std::cin) {
                std::cout << "Invalid input. Please enter a single letter.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (guess == '?') {
                giveHint(level);
                continue;
            }

            if (!word.guessLetter(guess)) {
                stats.decreaseGuesses();
                displayHangman();
            }
        }
        displayTrophy(word.isComplete());
    }

    HangmanGame* clone() const override {
        return new EasyModeHangman(*this);
    }
};
