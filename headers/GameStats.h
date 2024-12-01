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

    friend std::ostream& operator<<(std::ostream& os, const GameStats& stats) {
        os << "Guesses Remaining: " << stats.guessesRemaining;
        return os;
    }
};