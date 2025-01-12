#pragma once

#include "HangmanFactory.h"
#include "MediumModeHangman.h"

class MediumModeHangmanFactory : public HangmanFactory {
public:
    std::unique_ptr<HangmanGame> createGame(std::unique_ptr<Player> player, std::unique_ptr<Word> word, int maxGuesses) override {
        return std::make_unique<MediumModeHangman>(std::move(player), std::move(word), maxGuesses);
    }
};