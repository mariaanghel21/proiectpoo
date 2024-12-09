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
    std::cout << "Welcome to Brutal Hangman!\n" ;
    std::cout << "Test your vocabulary and strategic thinking while trying to achieve the highest score possible!\n";
    std::cout << "Here are the rules:\n";
    std::cout << "You must guess the given word in 6 attempts.\n";
    std::cout << "You can use ? for a hint, but you will be penalized based on the difficulty level: 1 point for Easy, 2 for Medium, and 3 for Hard.\n";
    std::cout << "You will be hanged with the blue console cable!\n";
    std::cout << "Are you ready to be hanged?\n";
    
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
        
        HangmanGame game(player, wordToGuess, 6, static_cast<int>(level));

        game.play(level);

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

    return 0;}