
#pragma once

#include <memory>
#include <map>
#include <functional>
#include "HangmanGame.h"
#include "Player.h"
#include "Word.h"
#include "Exception.h"


class HangmanFactory {
public:

    virtual ~HangmanFactory() = default;

    virtual std::unique_ptr<HangmanGame> createGame(
        std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses) = 0;

    static std::unique_ptr<HangmanGame> createGame(
        int level, std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses);

protected:
    static std::map<int, std::unique_ptr<HangmanFactory>> gameMap;
    static bool initialize();
    static bool initialized;
};

