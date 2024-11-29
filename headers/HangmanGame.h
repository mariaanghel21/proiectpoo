#pragma once
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
