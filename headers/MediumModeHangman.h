#pragma once

#include "HangmanGame.h"
#include <memory>

class MediumModeHangman : public HangmanGame {
public:
    MediumModeHangman(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses)
        : HangmanGame(std::move(player), std::move(word), maxGuesses, 2) {}

    void play(int level) override {
        char guess;
        while (!word->isComplete() && stats->hasGuessesLeft()) {
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

            if (!word->guessLetter(guess)) {
                stats->decreaseGuesses();
                displayHangman();
            }
        }
        displayTrophy(word->isComplete());
    }

    std::unique_ptr<HangmanGame> clone() const override {
        return std::make_unique<MediumModeHangman>(*this);
    }
};
