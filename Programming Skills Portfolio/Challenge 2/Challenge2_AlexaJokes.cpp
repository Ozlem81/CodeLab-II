
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <limits>
using namespace std;

// Load jokes from the text file
vector<string> loadJokes(const string& filename) {
    vector<string> jokes;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return jokes;
    }

    while (getline(file, line)) {
        if (!line.empty() && line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }

    file.close();
    return jokes;
}

// Display a random joke in two parts
void tellJoke(const vector<string>& jokes, mt19937& generator) {
    uniform_int_distribution<int> distribution(0, jokes.size() - 1);
    string joke = jokes[distribution(generator)];

    size_t position = joke.find('?');
    string setup = joke.substr(0, position + 1);
    string punchline = joke.substr(position + 1);

    cout << "\nAlexa: " << setup << endl;
    cout << "\nPress Enter to reveal the punchline...";
    cin.get();

    cout << "\nAlexa: " << punchline << "\n\n";
}

int main() {
    vector<string> jokes = loadJokes("randomJokes.txt");

    if (jokes.empty()) {
        cout << "No jokes available. Program exiting.\n";
        return 1;
    }

    random_device rd;
    mt19937 generator(rd());

    string command;

    cout << "=== Alexa Joke Generator ===\n";
    cout << "Type \"Alexa, tell me a joke\" to hear a joke.\n";
    cout << "Type \"quit\" to exit.\n";

    while (true) {
        cout << "\nYour command: ";
        getline(cin, command);

        if (command == "quit") {
            cout << "\nGoodbye!\n";
            break;
        }
        else if (command == "Alexa, tell me a joke") {
            tellJoke(jokes, generator);
        }
        else {
            cout << "Unknown command. Please try again.\n";
        }
    }

    return 0;
}
