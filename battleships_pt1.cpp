#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

bool isRunning = true;

void initBoard(int array[10][10]) {
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            array[x][y] = 0;
        }
    }
}
//status: 0 = empty, 1 = has ship, 2 = shot water, 3 = hit ship, 4 = sunk

void printBoard(int array[10][10]) {
    for (char a = 'A'; a <= 'J'; a++){
        cout << setw(5) << a;
    }
    cout << endl;
    for (int x = 0; x <= 9; x++){
        cout << " " << x;
        
        for(int y = 0; y < 10 ; y++) {
            if(array[x][y] == 0 || array[x][y] == 1){
                cout << setw(5) << " |" ;
            }
            else if(array[x][y] == 2 ) {
                cout << setw(5) << "O|";
            }
            else if(array[x][y] == 3 ) {
                cout << setw(5) << "/|";
            }
            else if(array[x][y] == 4 ) {
                cout << setw(5) << "X|";
            }
	    }
        cout << "\n";
    }
}

struct ship {
    unsigned short shipLength; //5, 4, 3, 3, 2
    unsigned short shipOrientation; //0 vertical, 1 horizontal
    string position;
    bool isAlive;
};

void initShips(ship playerShips[5], ship enemyShips[5]) {
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

void placeShipRandom(ship playerShips[5], ship enemyShips[5]) {
    for (ship ship : enemyShips) {
        
    }
    //choose random orientation
    //loop through array
    //check if another ship would touch it (if yes, choose different location)
    //place ship
    //repeat for all ships
}

void playerTurn() {
    //ask player input in coordinates "b4"
    //IF field already struck previously or out of bounds: ask input again
    //check if COM has a ship there
    //give feedback water, hit, sunk
}

void comTurn() {
    //random shoot without player input
}

int main() {
    cout << "Welcome to Battleships!\n";
    //quick explanation of how game works

    int board[10][10];
    initBoard(board);

    ship playerShips[5];
    ship enemyShips[5];
    initShips(playerShips, enemyShips);

    printBoard(board);

    // while(isRunning == true) {
    //     //game loop
    //     cout << "Your turn!\n";
    //     playerTurn();
    //     cout << "Enemy turn!\n";
    //     comTurn();
    // }

    return 0;
}