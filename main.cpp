#include <iostream>
#include <array>
#include <Helper.h>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "headers/Player.h"
#include "headers/Word.h"
#include "headers/HangmanGame.h"
#include "headers/EasyModeHangman.h"  
#include "headers/MediumModeHangman.h"  
#include "headers/HardModeHangman.h"
#include "headers/GameStats.h"

void loadWords(std::vector<std::string>& easyWords, std::vector<std::string>& mediumWords, std::vector<std::string>& hardWords) {
    std::ifstream file("cuvinte.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return;
    }

    std::string word;
    while (file >> word) {
        if (word.length() <= 5) {
            easyWords.push_back(word);
        } else if (word.length() <= 10) {
            mediumWords.push_back(word);
        } else {
            hardWords.push_back(word);
        }
    }

    file.close();
}

std::string getRandomWord(const std::vector<std::string>& words) {
    if (words.empty()) {
        return "";
    }
    srand(time(0));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

int main() {
    std::vector<std::string> easyWords, mediumWords, hardWords;
    loadWords(easyWords, mediumWords, hardWords);

    if (easyWords.empty() || mediumWords.empty() || hardWords.empty()) {
        std::cerr << "No words loaded from file. Exiting.\n";
        return 1;
    }
    std::cout << "----------------------------------\n";
    std::cout << "       Welcome to Hangman!       \n";
    std::cout << "----------------------------------\n";
    std::cout << "Rules of the Game:\n";
    std::cout << "The player must guess a secret word letter by letter.\n";
    std::cout << "Each incorrect guess adds a part to the hangman drawing.\n";
    std::cout << "The player can request a hint by pressing ? (a hint reveals one letter from the word).\n";
    std::cout << " Requesting a hint deducts points from the total score.\n";
    std::cout << "The game allows multiple rounds, with the total score carried over between rounds.\n";
    std::cout << "The player earns points for each word guessed completely.\n";
    std::cout << "The game ends when the player chooses to stop or loses.\n";
    std::cout << "Already guessed letters are displayed to avoid repetition.\n";
    std::cout << "The progress of the guessed word is shown as dashes and letters.\n";
    std::cout << "The goal is to score as many points as possible and guess all the words.\n";
    std::cout << "Difficulty levels:\n";
    std::cout << "   - Easy: Words up to 5 letters, -1 point per hint.\n";
    std::cout << "   - Medium: Words up to 10 letters, -2 points per hint.\n";
    std::cout << "   - Hard: Words longer than 10 letters, -3 points per hint.\n";
    std::cout << "You will be hanged with the blue console cable!\n";
    std::cout << "Good luck and have fun!\n";

    std::string playerName;
    std::cout << "Enter player name: ";
    std::getline(std::cin, playerName);

    int level;
    std::cout << "Select difficulty level (1: Easy, 2: Medium, 3: Hard): ";
    std::cin >> level;

    std::string wordToGuess;
    if (level == 1) {
        wordToGuess = getRandomWord(easyWords);
    } else if (level == 2) {
        wordToGuess = getRandomWord(mediumWords);
    } else if (level == 3) {
        wordToGuess = getRandomWord(hardWords);
    } else {
        std::cout << "Invalid level selected!\n";
        return 1;
    }

    if (wordToGuess.empty()) {
        std::cerr << "No valid word selected for the game. Exiting.\n";
        return 1;
    }

    Player player(playerName);
    int totalGames = 0;
    int totalScore = 0;
    bool playAgain = true;

    while (playAgain) {
        
        HangmanGame* game = nullptr;

        if (level == 1) {
            game = new EasyModeHangman(player, wordToGuess, 6);
        } else if (level == 2) {
            game = new MediumModeHangman(player, wordToGuess, 6);
        } else if (level == 3) {
            game = new HardModeHangman(player, wordToGuess, 6);
        }

        game->play(level);

        totalGames++;
        totalScore += player.getScore();

        std::cout << "Total Games Played: " << totalGames << "\n";
        std::cout << "Total Score: " << totalScore << "\n";

        char playChoice;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playChoice;

        if (playChoice != 'y' && playChoice != 'Y') {
            playAgain = false;
        } else {
            std::cout << "Select difficulty level for the next round (1: Easy, 2: Medium, 3: Hard): ";
            std::cin >> level;
            if (level == 1) {
                wordToGuess = getRandomWord(easyWords);
            } else if (level == 2) {
                wordToGuess = getRandomWord(mediumWords);
            } else if (level == 3) {
                wordToGuess = getRandomWord(hardWords);
            }
        }

        delete game;
    }

    std::cout << "\nTotal Games Played: " << totalGames << "\n";
    std::cout << "Total Score: " << totalScore << "\n";

    return 0;
}
