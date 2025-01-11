#pragma once

#include <memory>
#include "HangmanGame.h"
#include "EasyModeHangman.h"
#include "MediumModeHangman.h"
#include "HardModeHangman.h"  
#include "Player.h"
#include "Word.h"
#include "Exception.h"

class HangmanFactory {
public:
    static std::unique_ptr<HangmanGame> createGame(int level, std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses) {
        switch (level) {
            case 1:
                return std::make_unique<EasyModeHangman>(std::move(player), std::move(word), maxGuesses);
            case 2:
                return std::make_unique<MediumModeHangman>(std::move(player), std::move(word), maxGuesses);
            case 3:
                return std::make_unique<HardModeHangman>(std::move(player), std::move(word), maxGuesses);
            default:
                throw InvalidLevelException(); 
        }
    }
};
