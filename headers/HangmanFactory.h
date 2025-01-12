
#pragma once

#include <memory>
#include <map>
#include <functional>
#include "HangmanGame.h"
#include "EasyModeHangman.h"
#include "MediumModeHangman.h"
#include "HardModeHangman.h"
#include "Player.h"
#include "Word.h"
#include "Exception.h"

class HangmanFactory {
public:
    
    virtual std::unique_ptr<HangmanGame> createGame(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses) = 0;

    static std::unique_ptr<HangmanGame> createGame(int level, std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses) {
        auto it = gameMap.find(level);
        if (it != gameMap.end()) {
            return it->second->createGame(std::move(player), std::move(word), maxGuesses);
        } else {
            throw InvalidLevelException();
        }
    }

protected:
    
    static std::map<int, std::unique_ptr<HangmanFactory>> gameMap;

    static bool initialize() {
        gameMap[1] = std::make_unique<EasyModeHangmanFactory>();
        gameMap[2] = std::make_unique<MediumModeHangmanFactory>();
        gameMap[3] = std::make_unique<HardModeHangmanFactory>();
        return true;
    }

    static bool initialized;
};

std::map<int, std::unique_ptr<HangmanFactory>> HangmanFactory::gameMap;
bool HangmanFactory::initialized = HangmanFactory::initialize();
