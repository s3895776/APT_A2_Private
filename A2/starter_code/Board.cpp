#include "Board.h"

Board::Board(){
    rows = ROW;
    columns = COLUMN;
    std::vector<std::vector<Tile>> b(rows, std::vector<Tile>(columns, Tile()));
    this->board = b;
}

Board::~Board(){

}

Board::Board(Board& other){
    board = other.board;
    rows = other.rows;
    columns = other.columns;
}

std::vector<std::vector<Tile>> Board::getBoard(){
    return board;
}

bool Board::placeTile(Tile tile, std::string coordinates) {
    // tilePlaced remains true unless rejected
    bool tilePlaced = true;

    // validate the length of coordinates and find the index for breakoff
    int breakOff = 0;
    // check if the string coordinates has the appropriate length of 2 i.e. '6A'
    if (coordinates.size() == 2) {
        breakOff = 1;
    }
    // check if the string coordinates has the appropriate length of 3 i.e. '11A'
    else if (coordinates.size() == 3) {   
        breakOff = 2;
    } else {
        tilePlaced = false;
    }
    // reject if string coordinates has the length of 3 but has two letters i.e. '4AA'
    if (coordinates.size() == 3) {
        int countAlphabet = 0;
        for (char c: coordinates) {
            if (isalpha(c)) {
                ++countAlphabet;
            }
        }
        // coorindates can only contain one alphabet
        if (countAlphabet != 1) {
            tilePlaced = false;
        }
    }

    // parse and validate column
    std::string columnString = coordinates.substr(0, breakOff);
    // cast columnString into int i.e '6' -> 6
    int col = std::stoi(columnString);
    // reject if column is not between 0 and 14
    if (col < 0 || col > 14) {
        tilePlaced = false;
    }

    // parse and validate row
    std::string rowString = coordinates.substr(breakOff);
    // get character from rowString
    char rowChar = rowString[0];    
    if (rowChar < 'A' || rowChar > 'O') {
        tilePlaced = false;
    }

    // place tile if rowChar and col is valid
    if (tilePlaced) {
        char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
        int row = -1;
        // iterate through row_letters to locate the rowChar and get its index
        for (int i = 0; i < ROW; ++i) {
            if (row_letters[i] == rowChar) {
                row = i;
            }
        }
        // add tile to board if the tile is not empty
        if ( (board[row][col].isEmpty()) & (row != -1)) {
            board[row][col] = tile;
        }
        // do nothing if tile is occupied
        else {
            tilePlaced = false;
        }
    }

    return tilePlaced;
}

std::string Board::removeTile(std::string coordinates){
    
    // TODO: maybe find a better way to do this, or just leave it as it is
    Column col = coordinates[0] - '0';
    char r = coordinates[1];
    Row row = 0;
    char row_letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    for (int i = 0; i < ROW; ++i) {
        if (r == row_letters[i]){
            row = i;
        }
    }

    board[row][col] = Tile();
    // no need to clean up if it ain't a pointer kekw

    return "in progress";
}

std::string Board::displayTile(int row, int col){
    std::string tile = " ";
    // if (board[row][col] != nullptr) {
    //     char letter = board[row][col]->letter;
    //     tile += letter;
    //     tile += " ";
    // } else {
    //     tile = "   ";
    // }

    // Guan: If i am correct this should equate to 
    tile += board[row][col].getLetter();
    tile += " ";

    return tile;
}

void Board::printRow(int row, std::string colLetter){
    std::cout << colLetter+" |";
    for (int i = 0; i < COLUMN; ++i){
        std::cout << displayTile(row, i) + "|";
    }
    std::cout << std::endl;
}

void Board::displayBoard(){

    /* BOARD OUTPUT VISUALISATION

         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 
       -------------------------------------------------------------
     A |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     C |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     D |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     E |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     G |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     H |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     I |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     J |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     K |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     L |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     M |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     N |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     O |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |

    */

    std::cout << "    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 " << std::endl;
    std::cout << "  -------------------------------------------------------------" << std::endl;
    printRow(0,"A");
    printRow(1,"B");
    printRow(2,"C");
    printRow(3,"D");
    printRow(4,"E");
    printRow(5,"F");
    printRow(6,"G");
    printRow(7,"H");
    printRow(8,"I");
    printRow(9,"J");
    printRow(10,"K");
    printRow(11,"L");
    printRow(12,"M");
    printRow(13,"N");
    printRow(14,"O");
}