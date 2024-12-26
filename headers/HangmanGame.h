#pragma once

#include <iostream>
#include <array>
#include <limits>
#include "Player.h"
#include "Word.h"
#include "GameStats.h"

class HangmanGame {
protected:
    Player player;
    Word word;
    GameStats stats;
    int hintCount;
    int hintPenalty;

    HangmanGame(const Player& player, const std::string& word, int maxGuesses, int level)
        : player(player), word(word), stats(maxGuesses), hintCount(0) {
        if (level == 2) {
            hintPenalty = 2;
        } else if (level == 3) {
            hintPenalty = 3;
        } else {
            hintPenalty = 1;
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
        std::cout << hangmanStages[6 - stats.getGuessesRemaining()] << std::endl;
    }

    virtual void giveHint(int level) {
        if (static_cast<size_t>(hintCount) < word.getWord().size()) {
            for (size_t i = 0; i < word.getWord().size(); ++i) {
                if (word.getWord()[i] == '_') {
                    word.guessLetter(word.getWord()[i]);
                    hintCount++;
                    int penalty = (level == 2) ? 2 : (level == 3) ? 3 : 1;  
                    player.addScore(-penalty);
                    std::cout << "Hint: " << word << "\n";
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

    virtual HangmanGame* clone() const = 0;  

    virtual void displayTrophy(bool won) const {
        if (won) {
            std::cout << "Congratulations! You've guessed the word!\n";
            std::cout << " You managed to pass the word test. \n";
            std::cout << "You survived and weren't hanged!\n";
            std::cout << "You also earned a trophy!\n";
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
        
        std::cout << "The word was: " << word.getWord() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const HangmanGame& game) {
        os << game.player << "\n" << game.word << "\n" << game.stats;
        return os;
    }
};
