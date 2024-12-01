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

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& name, int score = 0) : name(name), score(score) {}

    Player(const Player& other) : name(other.name), score(other.score) {}

    Player& operator=(const Player& other) {
        if (this == &other) return *this;
        name = other.name;
        score = other.score;
        return *this;
    }

    ~Player() {}

    void addScore(int points) { score += points; }
    int getScore() const { return score; }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player: " << player.name << " | Score: " << player.score;
        return os;
    }
};

class Word {
private:
    std::string word;
    std::string guessed;

public:
    Word(const std::string& word) : word(word), guessed(word.size(), '_') {}

    bool guessLetter(char letter) {
        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }
        return found;
    }

    bool isComplete() const { return guessed == word; }

    friend std::ostream& operator<<(std::ostream& os, const Word& word) {
        os << "Current Word: " << word.guessed;
        return os;
    }
};

class GameStats {
private:
    int guessesRemaining;
    int totalGuesses;

public:
    GameStats(int totalGuesses) : guessesRemaining(totalGuesses), totalGuesses(totalGuesses) {}

    void decreaseGuesses() { if (guessesRemaining > 0) --guessesRemaining; }
    int getGuessesRemaining() const { return guessesRemaining; }
    bool hasGuessesLeft() const { return guessesRemaining > 0; }

    friend std::ostream& operator<<(std::ostream& os, const GameStats& stats) {
        os << "Guesses Remaining: " << stats.guessesRemaining;
        return os;
    }
};

class HangmanGame {
private:
    Player player;
    Word word;
    GameStats stats;

public:
    HangmanGame(const Player& player, const std::string& word, int maxGuesses)
        : player(player), word(word), stats(maxGuesses) {}

    void play() {
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

            if (!word.guessLetter(guess)) {
                stats.decreaseGuesses();
            }
            if (word.isComplete()) {
                std::cout << "Congratulations! You've guessed the word!\n";
                player.addScore(10);
            } else if (!stats.hasGuessesLeft()) {
                std::cout << "Game over! Out of guesses.\n";
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const HangmanGame& game) {
        os << game.player << "\n" << game.word << "\n" << game.stats;
        return os;
    }
};

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
    HangmanGame game(player, wordToGuess, 6);  
    game.play();

    return 0;
}
