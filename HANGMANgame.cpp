#include <iostream>;
#include <string>;
#include <vector>;
#include <algorithm>;
#include <fstream>;
#include <cstdlib>;
#include <ctime>;
using namespace std;

//FUNCTION PROTOTYPES
string clean(string);       //removes chars if not alpha and sets all chars to upper
void gameOver(bool, string);//gameover message
char chooseDifficulty();    //user selects difficulty
short choosePlayers();      //user selects 1 or 2 player
char playAgain();           // if 'y' play again else quit
void display(string,int,vector<char>);          // displays current and lives 
bool isDuplicateGuess(vector<char>, char);      //checks if guess has already been chosen

int main()
{   //GLOBAL VARIABLES
    string word{};                  //the word to guess
    int lives = 7;                  //number of incorrect guesses a player can make before losing
    string current{};               //current knowledge about word e.g "c*rr*nt"
    char guess;
    char again = 'y';               // play again if equal to 'y' else exit
    int n{};                        //word length
    vector<char> guesses{};         //guesses made stored in a vector of chars
    const int numEasy = 849;        //number of words in HANGMANhard.txt
    const int numHard = 213;        //number of words in HANGMANhard.txt
    vector<string> easyWords{};     //easy words from textfile
    vector<string> hardWords{};     //hard words from textfile 
    ifstream inputFile,inputFile2;

    while (again != 'n') {
        //user chooses 1 or 2 players and 1 or 2 is stored in numPlayers
        short numPlayers = choosePlayers();

        //1 player
        if (numPlayers == 1) {
            char difficulty = chooseDifficulty();
            if (difficulty == 'e') {
                // get word from easy textfile
                inputFile.open("HANGMANeasy.txt");
                while (!inputFile.eof()) {
                    string temp;
                    getline(inputFile, temp);
                    easyWords.push_back(temp);
                }
                //randomly choose easy word
                srand(time(NULL));
                int x = rand() % numEasy;
                word = easyWords[x];
                word = clean(word);
            }
            else {
                //get word from hard textfile
                inputFile2.open("HANGMANhard.txt");
                while (!inputFile2.eof()) {
                    string temp;
                    getline(inputFile2, temp);
                    hardWords.push_back(temp);
                }
                //randomly choose word
                srand(time(NULL));
                int x = rand() % numHard;
                word = hardWords[x];
                word = clean(word);
            }
        }
        // 2 players
        else {
            std::cout << "Player 1- please enter a word for player 2 to guess:";
            cin >> word;
            word = clean(word);
        }

        // clear screen and create current
        system("CLS");
        n = word.length();
        for (int i = 0; i < n; ++i) {
            current += "*";
        }

        // play game until gameover
        bool gameover = false;
        bool win = false;
        while (!gameover) {
            display(current, lives,guesses);        // display current and remaining lives
            cin >> guess;
            guess = toupper(guess);
            bool done = false;
            // check if guess has already been chosen
            while(isDuplicateGuess(guesses, guess)) {
                cout << "You've already chosen this letter. Please guess again: ";
                cin >> guess; 
            }
            // add guess to vec
            guesses.push_back(toupper(guess));

            system("CLS");
            int count{};        //count number of correct letters in word
            for (int i = 0; i < n; ++i) {
                if (word[i] == toupper(guess)) {
                    current[i] = toupper(guess);        //update current
                    count++;
                }
            }

            // if count ==0 life lost
            if (count == 0) {
                lives--;
            }
            if (current == word) {
                gameover = true;
                win = true;     //game won
            }
            if (lives == 0) { gameover = true; }    //game lost
        }

        gameOver(win, word);        //print gameover message
        again = playAgain();        //ask user if they wish to play again
        // reset some variables
        guesses.clear();
        current = "";
        lives = 7;
        system("CLS");
    }
    cout << "Thank you for playing! Goodbye.";
}

//function definitions
void gameOver(bool w, string l) {
    if (!w) { cout << "\nGAMEOVER! The word was: " << l; }
    else { cout << "\nCONGRATULATIONS YOU WON! THE WORD WAS: " << l; }
}
string clean(string s) {
    string ans{};
    for (auto c : s) {
        if (isalpha(c)) { ans += toupper(c); }
    }
    return ans;
}              
char chooseDifficulty() {
    char c;
    std::cout << "Enter e for easy, h for hard:";
    std::cin >> c;
    return tolower(c); 
}
short choosePlayers() {
    short players{};
    std::cout << "Enter 1 for 1 player or 2 for 2 players:";
    std::cin >> players;
    return players;
}
char playAgain() {
    char temp;
    cout << "\nWould you like to play again?(y/n):";
    cin >> temp;
    if (tolower(temp) =='y') { return temp; } 
    return 'n'; 
}
void display(string s, int l, vector<char> vec) {
    string t{};
    for (auto c : vec) { t +=c; }
    cout << s;
    cout << "\nLives: " << l << "\t\tGuesses {"+t+"}"<<endl;
    cout << "enter GUESS: ";
}
bool isDuplicateGuess(vector<char> vec, char g) {
    bool flag = false;
    for (auto c : vec) {
        if (c == g) {
            flag = true;
        }
    }
    return flag;
}