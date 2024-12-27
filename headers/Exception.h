#pragma once

#include <exception>
#include <string>

class HangmanException : public std::exception {
public:
    const char* what() const noexcept override {
        return "General Hangman exception occurred.";
    }
};

class InvalidLevelException : public HangmanException {
public:
    const char* what() const noexcept override {
        return "Invalid level selected for Hangman.";
    }
};

class WordNotFoundException : public HangmanException {
public:
    const char* what() const noexcept override {
        return "No valid word found for the game.";
    }
};

class FileOpenException : public HangmanException {
public:
    const char* what() const noexcept override {
        return "Error opening the word file.";
    }
};