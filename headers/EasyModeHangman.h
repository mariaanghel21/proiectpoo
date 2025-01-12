#pragma once

#include "HangmanGame.h"
#include <memory>

class EasyModeHangman : public HangmanGame {
public:
    EasyModeHangman(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses)
        : HangmanGame(std::move(player), std::move(word), maxGuesses, 1) {}

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

    void displayTrophy(bool won) const override {
        if (won) {
            std::cout << "Congratulations! You've guessed the word in Easy Mode!\n";
            std::cout << "        ________        \n";
            std::cout << "      //        \\      \n";
            std::cout << "     //   EASY   \\    \n";
            std::cout << "    ||   WINNER  ||    \n";
            std::cout << "  ___|___________|___  \n";
            std::cout << " |                   | \n";
            std::cout << " |      WELL DONE    | \n";
            std::cout << " |___________________| \n";
            std::cout << "      ||       ||      \n";
            std::cout << "   ___||_______||___   \n";
            std::cout << "  |                 |  \n";
            std::cout << "  |_________________|  \n";
        } else {
            std::cout << "You lost in Easy Mode! Better luck next time.\n";
            std::cout << "   _______   \n";
            std::cout << "  |       |  \n";
            std::cout << "  |       |  \n";
            std::cout << "  |_______|  \n";
            std::cout << "     |||     \n";
            std::cout << "   __|||__   \n";
            std::cout << "  |_______|  \n";
        }
        std::cout << "The word was: " << word->getWord() << "\n";
    }

    std::unique_ptr<HangmanGame> clone() const override {
        return std::make_unique<EasyModeHangman>(*this);
    }
};
