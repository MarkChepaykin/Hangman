#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype> 

using namespace std;


string decrypt(const string& cipher) {
    string decrypted = cipher;
    for (char& c : decrypted) {
        if (c >= 'a' && c <= 'z') {
            c = (c - 'a' - 3 + 26) % 26 + 'a';
        }
        else if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' - 3 + 26) % 26 + 'A';
        }

    }
    return decrypted;
}

vector<string> readWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string encryptedWord;

    if (file.is_open()) {
        while (getline(file, encryptedWord)) {
            words.push_back(decrypt(encryptedWord));
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }

    return words;
}


string chooseWord(const vector<string>& words) {
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}


void playHangman(const string& word) {
    string guessed(word.size(), '_');
    int attempts = 0;
    string triedLetters;
    char guess;
    bool wordGuessed = false;

    time_t startTime = time(nullptr);

    while (!wordGuessed && attempts < 6) {
        cout << "Guess the word: " << guessed << "\nAttempts: " << attempts << "\nEnter a letter: ";
        cin >> guess;
        guess = tolower(guess); 

        if (isalpha(guess) && triedLetters.find(guess) == string::npos) {
            triedLetters += guess;
            bool found = false;

            for (size_t i = 0; i < word.size(); ++i) {
                if (tolower(word[i]) == guess) { 
                    guessed[i] = word[i];
                    found = true;
                }
            }

            if (!found) {
                ++attempts;
            }

            if (guessed == word) {
                wordGuessed = true;
            }
        }
        else {
            cout << "Invalid input or letter already tried: " << triedLetters << endl;
        }
    }

    time_t endTime = time(nullptr);

    if (wordGuessed) {
        cout << "Congratulations! You guessed the word: " << word << endl;
    }
    else {
        cout << "You lost. The word was: " << word << endl;
    }

    cout << "Game time: " << difftime(endTime, startTime) << " seconds\n";
    cout << "Number of attempts: " << attempts << "\n";
    cout << "Used letters: " << triedLetters << "\n";
}

int main() {
    srand(time(nullptr)); 
    vector<string> words = readWordsFromFile("words.txt");

    if (!words.empty()) {
        string word = chooseWord(words);
        playHangman(word);
    }
    else {
        cout << "No valid words available for the game." << endl;
    }

    return 0;
}
