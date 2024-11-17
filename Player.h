#pragma once
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
