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
            std::cout << *this << "\n";
            stats.drawHangman(); 
            std::cout << "Enter your guess: ";
            std::cin >> guess;

            if (!std::cin || !std::isalpha(guess)) {
                std::cout << "Invalid input. Please enter a single letter.\n";
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                continue;
            }

            guess = tolower(guess);  

            if (!word.guessLetter(guess)) {
                stats.decreaseGuesses();
            }

            if (word.isComplete()) {
                std::cout << "Congratulations! You've guessed the word!\n";
                player.addScore(10);
            } else if (!stats.hasGuessesLeft()) {
                stats.drawHangman();  
                std::cout << "Game over! Out of guesses. The word was: " << word.getFullWord() << "\n";
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const HangmanGame& game) {
        os << game.player << "\n" << game.word << "\n" << game.stats;
        return os;
    }
};
