#include <iostream>
#include <array>
#include <Helper.h>
#include <iostream>
#include <string>
#include <limits>

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

int main() {
    std::string playerName;
    std::cout << "Enter player name: ";
    std::getline(std::cin, playerName);

    std::string wordToGuess;
    std::cout << "Enter the word to guess: ";
    std::getline(std::cin, wordToGuess);

    Player player(playerName);
    HangmanGame game(player, wordToGuess, 6);
    game.play();

    return 0;
}
