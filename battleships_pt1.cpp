#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

const unsigned short MAX_ROWS = 10;
const unsigned short MAX_COLUMNS = 10;

const unsigned short TOTAL_SHIPS = 5;
const unsigned short HORIZONTAL = 0;
const unsigned short VERTICAL = 1;

//status: 0 = empty, 1 = has ship, 2 = shot water, 3 = hit ship, 4 = sunk
const int EMPTY = 0;
const int OCCUPIED = 1;
const int WATER = 2;
const int HIT = 3;
const int SUNK = 4;

void initBoard(int board[MAX_ROWS][MAX_COLUMNS]) {
    for (int x = 0; x < MAX_ROWS; x++){
        for (int y = 0; y < MAX_COLUMNS; y++){
            board[x][y] = EMPTY;
        }
    }
}

void printBoard(int board[MAX_ROWS][MAX_COLUMNS], bool is_player_field) {
    for (char a = 'A'; a <= 'J'; a++){
        cout << setw(5) << a;
    }
    cout << endl;
    for (int x = 0; x < MAX_ROWS; x++){
        cout << " " << x;
        
        for(int y = 0; y < MAX_COLUMNS; y++) {
            if(board[x][y] == EMPTY || (board[x][y] == OCCUPIED && !is_player_field)) {
                cout << setw(5) << "~|";
            }
            else if (board[x][y] == OCCUPIED && is_player_field) {
                cout << setw(5) << "S|";
            }
            else if(board[x][y] == WATER ) {
                cout << setw(5) << "O|";
            }
            else if(board[x][y] == HIT ) {
                cout << setw(5) << "/|";
            }
            else if(board[x][y] == SUNK ) {
                cout << setw(5) << "X|";
            }
	    }
        cout << "\n";
    }
}

struct ship {
    unsigned short shipLength; //5, 4, 3, 3, 2
    unsigned short shipOrientation; //0 vertical, 1 horizontal --> see constants
    string position;
    bool isAlive;
};

void initShips(ship ships[TOTAL_SHIPS]) {
    for (int i = 0; i < TOTAL_SHIPS; i++) {
        ships[i].isAlive = true;
    }
    ships[0].shipLength = 5;
    ships[1].shipLength = 4;
    ships[2].shipLength = 3;
    ships[3].shipLength = 3;
    ships[4].shipLength = 2;
}

int getRandom(int upper_bound){
    return rand() % upper_bound;
}

struct hitbox {
    int starting_row;
    int starting_column;
    int ending_row;
    int ending_column;
};


struct hitbox getHitbox(ship ship, int board[MAX_ROWS][MAX_COLUMNS], unsigned short row, unsigned short column, unsigned short orientation) {
    struct hitbox bounds;

    bounds.starting_row = (row == 0) ? 0 : row - 1;
    bounds.starting_column = (column == 0) ? 0 : column - 1;

    if (orientation == HORIZONTAL) {
        bounds.ending_row = (row == MAX_ROWS - 1) ? row : row + 1;
        bounds.ending_column = (column + ship.shipLength - 1 == MAX_COLUMNS - 1) ? column + ship.shipLength - 1 : column + ship.shipLength;
    }
    else if (orientation == VERTICAL) {    
        bounds.ending_column = (column == MAX_COLUMNS - 1) ? column : column + 1;
        bounds.ending_row = (row + ship.shipLength - 1 == MAX_ROWS - 1) ? row + ship.shipLength - 1 : row + ship.shipLength;
    }

    return bounds;
}

bool isShipPlaceable(ship ship, int board[MAX_ROWS][MAX_COLUMNS], unsigned short row, unsigned short column, unsigned short orientation) {
    //check if starting coordinate is out of bounds
    if (row < 0 || row >= MAX_ROWS || column < 0 || column >= MAX_COLUMNS) return false;

    //check if right most position of vertical ship is within bounds
    if (orientation == VERTICAL && row + ship.shipLength - 1 >= MAX_ROWS) return false;

    //check if right most position of horizontal ship is within bounds
    else if (orientation == HORIZONTAL && column + ship.shipLength - 1 >= MAX_COLUMNS) return false;

    hitbox ship_hitbox = getHitbox(ship, board, row, column, orientation);

    //check if area of and around ship is clear
    for (int i = ship_hitbox.starting_row; i < ship_hitbox.ending_row; i++) {
        for (int j = ship_hitbox.starting_column; j < ship_hitbox.ending_column; j++) {
            if (board[i][j] != EMPTY) {
                return false;
            }
        }
    }

    return true;
}

void placeShip(ship ship, int board[MAX_ROWS][MAX_COLUMNS], unsigned short row, unsigned short column, unsigned short orientation) {
    if (orientation == VERTICAL) {
        for (int i = row; i < row + ship.shipLength; i++) {
            board[i][column] = OCCUPIED;
        }
    }
    else if (orientation == HORIZONTAL) {
        for (int i = column; i < column + ship.shipLength; i++) {
            board[row][i] = OCCUPIED;
        }
    }
}

void placeShipRandom(ship ship, int board[MAX_ROWS][MAX_COLUMNS]) {
    unsigned short rand_row;
    unsigned short rand_column;
    unsigned short rand_orientation;

    do {
        //choose random coordinates
        rand_row = getRandom(MAX_ROWS); //setting range via Modulo
        rand_column = getRandom(MAX_COLUMNS);
    
        //choose random orientation
        rand_orientation = getRandom(2);
        
    } while (!isShipPlaceable(ship, board, rand_row, rand_column, rand_orientation));

    placeShip(ship, board, rand_row, rand_column, rand_orientation);
}

void playerTurn() {
    //ask player input in coordinates "b4"
    cout << "PLAYER TURN\n";
    cout << "Please input target coordinate:\n";
    //IF field already struck previously or out of bounds: ask input again
    //check if COM has a ship there
    //give feedback water, hit, sunk
}

void comTurn() {
    cout << "ENEMY TURN\n";
    //random shoot without player input
}

int main() {
    bool isRunning = true;
    int player_board[MAX_ROWS][MAX_COLUMNS];
    int enemy_board[MAX_ROWS][MAX_COLUMNS];

    srand(time(0));

    cout << "Welcome to Battleships!\n";
    //quick explanation of how game works

    initBoard(player_board);
    initBoard(enemy_board);

    ship player_ships[TOTAL_SHIPS];
    ship enemy_ships[TOTAL_SHIPS];
    initShips(player_ships);
    initShips(enemy_ships);

    for (ship s : player_ships){
        placeShipRandom(s, player_board);
    }
    for (ship s : enemy_ships){
        placeShipRandom(s, enemy_board);
    }

    cout << "ENEMY BOARD\n";
    printBoard(enemy_board, false);
    cout << "--------------------------------------------------------\n";
    cout << "PLAYER BOARD\n";
    printBoard(player_board, true);

    

    // while(isRunning == true) {
    //     //game loop
    //     playerTurn();
    //     comTurn();
    // }

    return 0;
}