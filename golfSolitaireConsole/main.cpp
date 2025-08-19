#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "shuffler.cpp"
#include <bits/stdc++.h>

using namespace std;
// // GAME VARIABLES
// tableau Ids
vector<vector<int>> tableau = {
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1}
};
// pileIds
vector<int> pileIds;
// pileSources
vector<int> pileSources = {-1};
// talon Ids
vector<int> talon;

vector<int> initialSeed = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};


// generate new permutation of initalSeed
void generateSeed() {

// divides up new initialSeed into tableau, (waste)pile, talon
    // Initialize RNG
    random_device rd;
    mt19937 g(rd());
    // shuffle vecotr
    shuffle(initialSeed.begin(), initialSeed.end(), g);
}

// transfer initialSeed to tableau, (waste)pile, talon (starting position)
void setupGame() {
    //clears game state vectors
    for (int x = 0; x < 7; x++) {
    tableau.at(x).clear();
    }
    pileIds.clear();
    pileSources.clear();
    talon.clear();

    // setup tableau
    int sum = 0;
    for (int y = 0; y < 7; y++) {
        for (int z = 0; z < 5; z++) {
            sum = 5 * y + z;
            tableau.at(y).push_back(initialSeed.at(sum));
//            cout << initialSeed.at(sum) << " ";
        }
//        cout << '\n';
    }
    // setup pile
    pileIds.push_back(initialSeed.at(35));
    pileSources.push_back(-1);
//    cout << initialSeed.at(35) << '\n';
    // setup talon
    for (int a = 51; a > 35; a--) {
        talon.push_back(initialSeed.at(a));
//        cout << initialSeed.at(a) << " " << '\n';
    }
}

// character reference
vector<string> rankCharacters = {"A.","2.","3.","4.","5.","6.","7.","8.","9.","10","J.","Q.","K."};
vector<string> suitCharacters = {"H","C","D","S"};

// converts raw Id to text w/ rank and suit
string convertIdtoCard(int Id) {
    string answer;
    int value = Id % 13;
    answer += rankCharacters.at(value);
    int suit = (Id - value) / 13;
    answer += suitCharacters.at(suit);
    return answer;
}

// accomodates absent cards
string checkPresence(int col, int row) {
    if (row < tableau.at(col).size()) {
        // card Id present - convert to string
        return convertIdtoCard(tableau.at(col).at(row));
    } else {
        // card Id not present - leave blank
        return "   ";
    }
}

// draws current tableau, top-most pile card, talon size
void drawGameState() {
// clears console
    system("cls");
 // draw tableau
        for (int row = 0; row < 5; row++) {
             for (int col = 0; col < 7; col++) {
            cout << checkPresence(col,row) << " ";
                }
        cout << '\n';
        }
// draw divider
cout << "---------------------------" << '\n';
// draw columns
cout << "(0) (1) (2) (3) (4) (5) (6)" << '\n';
// draw divider
cout << "---------------------------" << '\n';
// draw pile card
cout << convertIdtoCard(pileIds.back());
// draw talon
cout << " ";
if (talon.size() > 0) {
    cout << "\[\]";
    for (int x = 2; x < talon.size() + 1; x++) {
        cout << "\]";
    }
}
cout << '\n' << "input (press h to help): " << '\n' ;
}

// executes move where a card is drawn from the talon
void drawFromTalon() {
    // prevent move if talon is empty
    if (talon.size() == 0) {
        cout << '\n' << "No cards remaining in talon";
        return;
    }
    // adds drawn card to top of wastepile
    pileIds.push_back(talon.back());
    pileSources.push_back(7);
    // removes drawn card from talon
    talon.pop_back();
    // draws updated state of game
    drawGameState();
}

// executes move where a card is taken from tableau column
void drawFromTableau(int col) {
    // prevent move if tableau column is empty
    if (tableau.at(col).size() == 0) {
        cout << '\n' << "No cards remaining in tableau column";
        return;
    }
    // calculate ranks for card in front of tableau column + wastepile
    int colRank = tableau.at(col).back() % 13;
    int pileRank = pileIds.back() % 13;
    int difference = abs(colRank - pileRank);
    if (difference == 1 || difference == 12) {
        // // execute move if +/- 1 or A to K, K to A
        // Add card to top of wastepile
        pileIds.push_back(tableau.at(col).back());
        pileSources.push_back(col);
        // Remove card from tableau column
        tableau.at(col).pop_back();
        // Draws updated game state
        drawGameState();
    }
    else {
        cout << '\n' << "Card not able to be added to wastepile";
    }

}

// undoes move
void undoMove() {
    int source = pileSources.back();
    if (source == -1) {
        cout << '\n' << "Undo not available - no moves have been played";
        return;
    }
    // "7" goes to talon
    if (source == 7) {
        // // go from wastepile to talon
        // Add top wastepile card to top of talon
        talon.push_back(pileIds.back());
        // Remove top wastepile card from pileIds, Sources
        pileIds.pop_back();
        pileSources.pop_back();
    // "0" thru "6" - card came from tableau
    } else {
         // // go from wastepile to tableau column
        // Add top wastepile card to top of tableau column
        tableau.at(source).push_back(pileIds.back());
        // Remove top wastepile card from pileIds, Sources
        pileIds.pop_back();
        pileSources.pop_back();
    }
    drawGameState();
}

// check if player has won yet
bool checkVictory() {
    for (int x = 0; x < 7; x++) {
        if (tableau.at(x).size() == 0) {
            // PASSED;
        }
        else { // cards still in tableau
            return false;
        }
    }
    return true;
}

// check if player has run out of moves
bool checkNoMoreMoves() {
    if (talon.size() > 0) {
        // talon still has cards
        return false;
    }
    for (int x = 0; x < 7; x++) {
        if (tableau.at(x).size() == 0) {
            // tableau column is empty, move on
            continue;
        } else {
            int colId = tableau.at(x).back() % 13;
            int pileId = pileIds.back() % 13;
            int difference = abs(colId - pileId);
            if (difference == 1 || difference == 12) {
                return false;
            }
        }
    }
    return true;

}

// restarts the current game
void restartGame() {
    setupGame();
    drawGameState();
}

void startNewGame() {
    generateSeed();
    setupGame();
    drawGameState();
}
int main()
{
    startNewGame();
    bool programActive = true;
    while (programActive) {
        string input;
        cin >> input;
        if (input == "q") {
            programActive = false;
        } else if (input == "d") {
            drawFromTalon();
        } else if (input == "0") {
            drawFromTableau(0);
        } else if (input == "1") {
            drawFromTableau(1);
        } else if (input == "2") {
            drawFromTableau(2);
        } else if (input == "3") {
            drawFromTableau(3);
        } else if (input == "4") {
            drawFromTableau(4);
        } else if (input == "5") {
            drawFromTableau(5);
        } else if (input == "6") {
            drawFromTableau(6);
        } else if (input == "u") {
            undoMove();
        } else if (input == "r") {
            restartGame();
        } else if (input == "n") {
            startNewGame();
        } else if (input == "h") {
            cout << '\n' << "\[0-6\] draw from tableau, \[d\]raw from talon (stock), \[u\]ndo move, \[r\]estart game, \[q\]uit game, \[n\]ew game" << '\n';
        }
        else {
            cout << "input not recognized" << '\n';
        }
        if (checkVictory()) {
            cout << "Congratulations! You have cleared the board!" << '\n';
        }
        if (checkNoMoreMoves()) {
            cout << "No more moves - \[u\]ndo, \[r\]estart, \[n\]ew game or \[q\]uit" << '\n';
        }
    }

    return 0;
}
