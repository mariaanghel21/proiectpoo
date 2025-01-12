#pragma once

#include "HangmanGame.h"
#include <memory>

class HardModeHangman : public HangmanGame {
public:
    HardModeHangman(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses)
        : HangmanGame(std::move(player), std::move(word), maxGuesses, 3) {}

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
            std::cout << "Congratulations! You've guessed the word in Hard Mode!\n";
            std::cout << "              _______                    \n";
            std::cout << "            //       \\                  \n";
            std::cout << "           //   HARD   \\                 \n";
            std::cout << "          //   MASTER!  \\               \n";
            std::cout << "          |             |                \n";
            std::cout << "       ___|_____________|___             \n";
            std::cout << "       |                   |              \n";
            std::cout << "       |  LEGENDARY WIN!   |              \n";
            std::cout << "       |                   |              \n";
            std::cout << "       |   TRUE CHAMPION   |              \n";
            std::cout << "       |                   |              \n";
            std::cout << "       |___________________|              \n";
            std::cout << "            ||       ||                   \n";
            std::cout << "            ||       ||                   \n";
            std::cout << "            ||       ||                   \n";
            std::cout << "         ___||_______||___                \n";
            std::cout << "        |                 |               \n";
            std::cout << "        |                 |               \n";
            std::cout << "        |_________________|               \n";
        } else {
            std::cout << "You lost in Hard Mode! Better luck next time.\n";
            std::cout << "Here's a consolation trophy:\n";
            std::cout << "   __________   \n";
            std::cout << "  |          |  \n";
            std::cout << "  |   GREAT  |  \n";
            std::cout << "  |   JOB!   |  \n";
            std::cout << "  |__________|  \n";
            std::cout << "      |||        \n";
            std::cout << "      |||        \n";
            std::cout << "    __|||__      \n";
            std::cout << "   |_______|     \n";
        }
        std::cout << "The word was: " << word->getWord() << "\n";
    }

    std::unique_ptr<HangmanGame> clone() const override {
        return std::make_unique<HardModeHangman>(*this);
    }
};
