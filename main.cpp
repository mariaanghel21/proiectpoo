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
#include "headersWord.h"
#include "headers/HangmanGame.h"
#include "headers/GameStats.h"

void loadWords(std::vector<std::string>& easyWords, std::vector<std::string>& mediumWords, std::vector<std::string>& hardWords) {
    std::ifstream file("tastatura.txt");
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
        HangmanGame game(player, wordToGuess, 6);
        game.play();

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
    }

    std::cout << "\nTotal Games Played: " << totalGames << "\n";
    std::cout << "Total Score: " << totalScore << "\n";

    return 0;
}
