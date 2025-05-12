#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int randomize(int f, int s) {
    return std::rand() % s + f;
}

std::vector<std::string> loadWords() {
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    std::string word;

    while (std::getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    return words;
}

std::string getRandomWord() {
    std::vector<std::string> words = loadWords();
    if (words.empty()) return "hangman";
    return words[std::rand() % words.size()];
}

std::string getHiddenWord(const std::string& word) {
    std::string hidden;
    for (char c : word) {
        hidden += "_ ";
    }
    return hidden;
}

int main() {
    std::srand(std::time(0));
    std::string secretWord = getRandomWord();
    std::string hiddenWord = getHiddenWord(secretWord);
    std::string guessedLetters;
    std::cout << "Welcome to Hangman!\n";
    std::cout << "Guess the word: " << hiddenWord << "\n";

    while (true) {
        char guess;
        std::cout << "Enter a letter: ";
        std::cin >> guess;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool correctGuess = false;
        for (char c : secretWord) {
            if (tolower(c) == tolower(guess)) {
                correctGuess = true;
                break;
            }
        }

        if (correctGuess) {
            std::cout << "Correct!\n";
            for (int i = 0; i < secretWord.size(); ++i) {
                if (tolower(secretWord[i]) == tolower(guess)) {
                    hiddenWord[i * 2] = secretWord[i]; // * 2 (cuz of 'space')
                }
            }
        }
        else {
            std::cout << "Wrong! Try again.\n";
        }

        std::cout << "Word: " << hiddenWord << "\n";

        if (hiddenWord.find('_') == std::string::npos) {
            std::cout << "Congratulations! You won! The word was: " << secretWord << "\n";
            break;
        }
    }
}