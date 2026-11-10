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

//status: 0 = empty, 1 = has ship, 2 = shot MISSED, 3 = hit ship, 4 = sunk
const int EMPTY = 0;
const int OCCUPIED = 1;
const int MISSED = 2;
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
            else if(board[x][y] == MISSED ) {
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

//get random number, passing argument of max rows or max columns in function placeShipRandom
int getRandom(int upper_bound){
    return rand() % upper_bound;
}

struct hitbox {
    int starting_row;
    int starting_column;
    int ending_row;
    int ending_column;
};

//determine hitbox of ship --> ship body + one square around
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
    for (int i = ship_hitbox.starting_row; i <= ship_hitbox.ending_row; i++) {
        for (int j = ship_hitbox.starting_column; j <= ship_hitbox.ending_column; j++) {
            if (board[i][j] != EMPTY) {
                return false;
            }
        }
    }

    return true;
}

//places ships on player board and enemy board
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

//gives random coordinates to placeShip
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

struct targetCoordinates {
    unsigned short row_index;
    unsigned short column_index;
};

struct targetCoordinates validateInput(int board[MAX_ROWS][MAX_COLUMNS]) {
    struct targetCoordinates coordinates;
    bool is_input_valid = false;
    string input;
    char row_input;
    char column_input;
    unsigned short row_short;
    unsigned short column_short;
    
    do {
        cout << "Please input target coordinate:\n";
        cin >> input;

        //separating input coordinates
        row_input = input[1];
        column_input = tolower(input[0]); //making sure it's lower case just in case
        row_short = row_input - '0';
        column_short = column_input - 'a';

        if (input.length() != 2) {
            cout << "Invalid input, please type a valid coordinate (e.g. b4).\n";
        }
        else if (row_input < '0' || row_input > '0' + MAX_ROWS - 1 || column_input < 'a' || column_input > 'a' + MAX_COLUMNS - 1) {
            cout << "Invalid input, coordinate out of bounds. Please make sure the coordinate exists in the playing field.\n";
        }
        else if (board[row_short][column_short] != EMPTY && board[row_short][column_short] != OCCUPIED) {
            cout << "You have targeted this field before, please type a new coordinate.\n";
        }
        else {
            coordinates.row_index = row_short;
            coordinates.column_index = column_short;
            is_input_valid = true;
        }
    } while (!is_input_valid);
    
    return coordinates;
}

bool checkForHit(bool is_checking_row, bool is_checking_up, int board[MAX_ROWS][MAX_COLUMNS], int row_array[], int col_array[], int row_coordinate, int col_coordinate, unsigned short row_index, unsigned short col_index){
    bool is_ship_sunk = true;
    while (board[row_coordinate][col_coordinate] == HIT || board[row_coordinate][col_coordinate] == OCCUPIED)
    {
        if (board[row_coordinate][col_coordinate] == OCCUPIED)
        {
            is_ship_sunk = false;
            break;
        }
        
        col_array[col_index] = col_coordinate;
        row_array[row_index] = row_coordinate;
        col_index++;
        row_index++;
        if (is_checking_row && is_checking_up){
            row_coordinate++;
            cout << "checking row up\n";
        }
        else if (is_checking_row && !is_checking_up){
            row_coordinate--;
            cout << "checking row down\n";
        }
        else if (!is_checking_row && is_checking_up){
            col_coordinate++;
            cout << "checking col up\n";
        }
        else if (!is_checking_row && !is_checking_up){
            col_coordinate--;
            cout << "checking col down\n";
        }
        cout << board[row_coordinate][col_coordinate] << endl;
        cout << is_ship_sunk << endl;
    }
    return is_ship_sunk;
}

void checkSunkShip(targetCoordinates coordinates, int board[MAX_ROWS][MAX_COLUMNS]) {
    int row_coordinate = coordinates.row_index;
    int column_coordinate = coordinates.column_index;
    int row_positions[] = {};
    int column_positions[] = {};
    unsigned short array_column_index = 0;
    unsigned short array_row_index = 0;
    bool is_ship_sunk;

    //check column right
    is_ship_sunk = checkForHit(false, true, board, row_positions, column_positions, row_coordinate, column_coordinate, array_row_index, array_column_index);
    //reset column
    column_coordinate = coordinates.column_index;
    //check column left
    is_ship_sunk = checkForHit(false, false, board, row_positions, column_positions, row_coordinate, column_coordinate, array_row_index, array_column_index);
    //reset column
    column_coordinate = coordinates.column_index;
    //check row up
    is_ship_sunk = checkForHit(true, true, board, row_positions, column_positions, row_coordinate, column_coordinate, array_row_index, array_column_index);
    //reset row
    row_coordinate = coordinates.row_index;
    //check row down
    is_ship_sunk = checkForHit(true, false, board, row_positions, column_positions, row_coordinate, column_coordinate, array_row_index, array_column_index);
    
    if (is_ship_sunk)
    {
        for (int i = 0; i < sizeof(row_positions); i++){
            board[coordinates.row_index + i][coordinates.column_index] = SUNK;
        }
        for (int i = 0; i < sizeof(column_positions); i++){
            board[coordinates.row_index][coordinates.column_index + i] = SUNK;
        }
    }
    
}

void checkShotField(targetCoordinates coordinates, int board[MAX_ROWS][MAX_COLUMNS]) {
    int status = board[coordinates.row_index][coordinates.column_index];
    
    if (status == EMPTY) {
        board[coordinates.row_index][coordinates.column_index] = MISSED;
        cout << "You hit water!\n";
    }
    else if (status == OCCUPIED) {
        board[coordinates.row_index][coordinates.column_index] = HIT;
        cout << "You hit an enemy ship!\n";
        checkSunkShip(coordinates, board);
        if (board[coordinates.row_index][coordinates.column_index] == SUNK){
            cout << "You sunk the ship!\n";
        }
    }
    else {
        cout << "Invalid shot\n";
    }
    
}

void playerTurn(int board[MAX_ROWS][MAX_COLUMNS]) {
    //ask player input in coordinates "b4"
    cout << "PLAYER TURN\n";
    //make sure input coordinates have correct syntax, are inside the playing field, and haven't been hit before
    targetCoordinates coordinates = validateInput(board);
    //check if COM has a ship there & update field status
    checkShotField(coordinates, board);
    
    //give feedback MISSED, hit, sunk
}

void comTurn() {
    cout << "ENEMY TURN\n";
    //random shoot without player input
}

void showBoards(int enemy[MAX_ROWS][MAX_COLUMNS], int player[MAX_ROWS][MAX_COLUMNS]) {
    cout << "ENEMY BOARD\n";
    printBoard(enemy, false);
    cout << "--------------------------------------------------------\n";
    cout << "PLAYER BOARD\n";
    printBoard(player, true);
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

    

    while(isRunning == true) {
        //game loop
        showBoards(enemy_board, player_board);
        playerTurn(enemy_board);
        //comTurn();
    }

    return 0;
}