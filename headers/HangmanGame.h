#pragma once

#include <iostream>
#include <array>
#include <limits>
#include <memory>  
#include "Player.h"
#include "Word.h"
#include "GameStats.h"


class HangmanGame {
protected:
    std::unique_ptr<Player> player;  
    std::unique_ptr<Word> word;
    std::unique_ptr<GameStats> stats;
    int hintCount;
    int hintPenalty;

     HangmanGame(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses, int level)
        : player(std::move(player)), word(std::move(word)), stats(std::make_unique<GameStats>(maxGuesses)), hintCount(0) {
        if (level == 2) {
            hintPenalty = 2;
        } else if (level == 3) {
            hintPenalty = 3;
        } else if (level != 1) {
            throw InvalidLevelException(); 
        }
    }

    virtual void displayHangman() const {
        const std::array<std::string, 7> hangmanStages = {
            " _______ \n |       |\n |       \n |       \n |       \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |       \n |       \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |       |\n |       \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |      /|\n |       \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |      /|\\\n |       \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |      /|\\\n |      / \n |       \n |______ \n", 
            " _______ \n |       |\n |       O\n |      /|\\\n |      / \\\n |       \n |______ \n" 
        };
        std::cout << hangmanStages[6 - stats->getGuessesRemaining()] << std::endl;
    }

    virtual void giveHint(int level) {
        if (static_cast<size_t>(hintCount) < word->getWord().size()) {
            for (size_t i = 0; i < word->getWord().size(); ++i) {
                if (word->getWord()[i] == '_') {
                    word->guessLetter(word->getWord()[i]);
                    hintCount++;
                    int penalty = (level == 2) ? 2 : (level == 3) ? 3 : 1;  
                    player->addScore(-penalty);
                    std::cout << "Hint: " << *word << "\n";
                    std::cout << "You lost " << penalty << " points for this hint.\n";
                    break;
                }
            }
        } else {
            std::cout << "No more hints available.\n";
        }
    }

public:
    virtual ~HangmanGame() = default;

    virtual void play(int level) = 0;

    virtual std::unique_ptr<HangmanGame> clone() const = 0;

    virtual void displayTrophy(bool won) const {
        if (won) {
            std::cout << "Congratulations! You've guessed the word!\n";
            std::cout << " You managed to pass the word test. \n";
            std::cout << "You survived and weren't hanged!\n";
            std::cout << "You earned a trophy!\n";
            std::cout << "       _______        \n";
            std::cout << "      |       |       \n";
            std::cout << "      |       |       \n";
            std::cout << "   ___|_______|___    \n";
            std::cout << "  |               |   \n";
            std::cout << "  |     TROPHY    |   \n";
            std::cout << "  |_______________|   \n";
            std::cout << "       ||   ||        \n";
            std::cout << "       ||   ||        \n";
            std::cout << "       ||   ||        \n";
            std::cout << "     __||___||__      \n";
            std::cout << "    |___________|     \n";
        } else {
            std::cout << "Game over! You were hanged. Better luck next time.\n";
            std::cout << "Unfortunately, you failed to pass the word test.\n";
            std::cout << "You did not survive, and you were brutally hanged!\n";
            std::cout << "But I'll give you a consolation trophy!\n";
            std::cout << "   _______   \n";
            std::cout << "  |       |  \n";
            std::cout << "  |       |  \n";
            std::cout << "  |_______|  \n";
            std::cout << "     |||     \n";
            std::cout << "     |||     \n";
            std::cout << "   __|||__   \n";
            std::cout << "  |_______|  \n";
        }

        std::cout << "The word was: " << word->getWord() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const HangmanGame& game) {
        os << *game.player << "\n" << *game.word << "\n" << *game.stats;
        return os;
    }

    HangmanGame(const HangmanGame& other)
        : player(std::make_unique<Player>(*other.player)),
          word(std::make_unique<Word>(*other.word)),
          stats(std::make_unique<GameStats>(*other.stats)),
          hintCount(other.hintCount),
          hintPenalty(other.hintPenalty) {}

    HangmanGame& operator=(const HangmanGame& other) {
        if (this != &other) {
            player = std::make_unique<Player>(*other.player);
            word = std::make_unique<Word>(*other.word);
            stats = std::make_unique<GameStats>(*other.stats);
            hintCount = other.hintCount;
            hintPenalty = other.hintPenalty;
        }
        return *this;
    }

    HangmanGame(HangmanGame&& other) noexcept = default;
    HangmanGame& operator=(HangmanGame&& other) noexcept = default;
};
