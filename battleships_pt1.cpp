#include <iostream>
#include <string>

using namespace std;

//base variables
bool isRunning = true;

int board[10][10];

void initBoard() {
    for (int i = 0; i < 10; i++)
    {
        /* code */
    }
    
}

struct ship {
    unsigned short shipLength; //5, 4, 3, 3, 2
    unsigned short shipOrientation; //0 vertical, 1 horizontal
    bool isAlive;
};

ship playerShips[5];
ship enemyShips[5];

void initShips() {
    //init player ships
    for (ship ship : playerShips) {
        ship.isAlive = true;
    }
    playerShips[0].shipLength = 5;
    playerShips[1].shipLength = 4;
    playerShips[2].shipLength = 3;
    playerShips[3].shipLength = 3;
    playerShips[4].shipLength = 2;

    //init enemy ships
    for (ship ship : enemyShips) {
        ship.isAlive = true;
    }
    enemyShips[0].shipLength = 5;
    enemyShips[1].shipLength = 4;
    enemyShips[2].shipLength = 3;
    enemyShips[3].shipLength = 3;
    enemyShips[4].shipLength = 2;
}

void placeShipRandom() {
    
    //choose random orientation
    //largest ship first
    //check if another ship would touch it (if yes, choose different location)
    //place ship
    //repeat for all ships
}

void shoot() {
    //ask player input in coordinates "b4"
    //IF field already struck previously or out of bounds: ask input again
    //check if COM has a ship there
    //give feedback water, hit, sunk
}

void comTurn() {
    //random shoot without player input
}

void printBoard() {

}

int main() {
    cout << "Welcome to Battleships!\n";
    //quick explanation of how game works

    while(isRunning == true) {
        //game loop
        
    }
}