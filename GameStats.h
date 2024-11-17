#pragma once
class GameStats {
private:
    int guessesRemaining;
    int totalGuesses;

public:
    GameStats(int totalGuesses) : guessesRemaining(totalGuesses), totalGuesses(totalGuesses) {}

    void decreaseGuesses() { if (guessesRemaining > 0) --guessesRemaining; }
    int getGuessesRemaining() const { return guessesRemaining; }
    bool hasGuessesLeft() const { return guessesRemaining > 0; }

void drawHangman() const {
        switch (guessesRemaining) {
            case 6:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |\n"
                             " |\n"
                             " |\n"
                             " |\n"
                             "_|___\n";
                break;
            case 5:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |\n"
                             " |\n"
                             " |\n"
                             "_|___\n";
                break;
            case 4:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |       |\n"
                             " |\n"
                             " |\n"
                             "_|___\n";
                break;
            case 3:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |      /|\n"
                             " |\n"
                             " |\n"
                             "_|___\n";
                break;
            case 2:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |      /|\\\n"
                             " |\n"
                             " |\n"
                             "_|___\n";
                break;
            case 1:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |      /|\\\n"
                             " |      /\n"
                             " |\n"
                             "_|___\n";
                break;
            case 0:
                std::cout << "  _______\n"
                             " |/      |\n"
                             " |       O\n"
                             " |      /|\\\n"
                             " |      / \\\n"
                             " |\n"
                             "_|___\n";
                break;
            default:
                std::cout << "Invalid state\n";
                break;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const GameStats& stats) {
        os << "Guesses Remaining: " << stats.guessesRemaining;
        return os;
    }
};
