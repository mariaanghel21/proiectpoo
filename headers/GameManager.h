#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

class GameManager {
private:
    std::vector<std::string> easyWords;   
    std::vector<std::string> mediumWords;
    std::vector<std::string> hardWords;   
    std::string currentWord;              
    std::string guessedWord;              
    int remainingAttempts;               

public:
    GameManager() : easyWords(), mediumWords(), hardWords(), currentWord(""), guessedWord(""), remainingAttempts(6) {
        loadWords();  
        srand(time(0));  
    }

    void loadWords() {
        std::ifstream file("cuvinte.txt");  
        if (!file) {
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
    }

    std::string getRandomWord(int level) {
        std::vector<std::string>* words = nullptr;
        if (level == 1) {
            words = &easyWords;
        } else if (level == 2) {
            words = &mediumWords;
        } else if (level == 3) {
            words = &hardWords;
        } else {
            std::cerr << "Invalid level!\n";
            return "";
        }

        if (words->empty()) {
            std::cerr << "No words available for the selected difficulty!\n";
            return "";
        }

        int randomIndex = rand() % words->size();
        return (*words)[randomIndex];  
    }

    void displayGuessedWord() const {
        std::cout << "Current word: " << guessedWord << "\n";
    }

    bool guessLetter(char letter) {
        bool found = false;

        for (size_t i = 0; i < currentWord.size(); ++i) {
            if (currentWord[i] == letter && guessedWord[i] == '_') {
                guessedWord[i] = letter;
                found = true;
            }
        }

        if (!found) {
            --remainingAttempts;
            std::cout << "Incorrect guess! Remaining attempts: " << remainingAttempts << "\n";
        }

        return found;
    }

    bool isWordGuessed() const {
        return currentWord == guessedWord;
    }

    bool isGameOver() const {
        return remainingAttempts == 0 || isWordGuessed();
    }

    void gameOver() const {
        if (isWordGuessed()) {
            std::cout << "Congratulations! You guessed the word: " << currentWord << "\n";
        } else {
            std::cout << "Game over! The correct word was: " << currentWord << "\n";
        }
    }

    void playGame(int level) {
        currentWord = getRandomWord(level);
        guessedWord = std::string(currentWord.length(), '_');
        remainingAttempts = 6;

        char letter;
        bool gameFinished = false;

        while (!gameFinished) {
            displayGuessedWord();
            std::cout << "Guess a letter: ";
            std::cin >> letter;

            bool found = guessLetter(letter);

            if (found) {
                std::cout << "Good guess!\n";
            } else {
                std::cout << "Try again.\n";
            }

            gameFinished = isGameOver();

            if (gameFinished) {
                gameOver();
            }
        }
    }
};
