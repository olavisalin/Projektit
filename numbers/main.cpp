/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author ( Fill with your own info )
 * Name: Olavi Salin
 * Student number: 284132
 * UserID: salino ( Necessary due to gitlab folder naming. )
 * E-Mail: olavi.salin@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */

#include "numbertile.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;


// Adds a single new value to board using rEng and distr for random positioning.
void newValue(std::vector<std::vector<NumberTile>> &board,
               std::default_random_engine &rEng,
               std::uniform_int_distribution<int> &distr){
    // Tries to assign NEW_VAl to randomly selected tile. Continues trying until
    // newVal() returns true.
    while(!board.at(distr(rEng)).at(distr(rEng)).setValue(NEW_VALUE));
}


// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(std::vector<std::vector<NumberTile>> &board,
                std::default_random_engine &rEng,
                std::uniform_int_distribution<int> &distr){

    // Initialize the board with SIZE x SIZE empty numbertiles.
    for ( auto y = 0; y < SIZE; y++ ){
        board.push_back({});
        for ( auto x = 0; x < SIZE; x++ ){
            // If you don't want to use pairs, replace "std::make_pair(y, x)"
            // with "y, x".
            board.at(y).push_back(NumberTile(0, y, x));
        }
    }

    // Ask user for the seed value and initialize rEng.
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if(seed == "") {
        // If the user did not give a seed value, use computer time as the seed
        // value.
        rEng.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rEng.seed(stoi(seed));
    }

    // Add some tiles to the board.
    for ( int i = 0 ; i < SIZE ; ++i ){
        newValue(board, rEng, distr);
    }
}

// Prints the board.
void print(std::vector<std::vector<NumberTile>> &board){
    // The y isn't actually the y coordinate or some int, but an iterator that
    // is like a vector of NumberTiles.
    for ( auto y : board ){
        // Prints a row of dashes.
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        // And then print all cells in the desired width.
        for ( auto x : y ){
            x.print(PRINT_WIDTH);
        }
        // And a line after each row.
        std::cout << "|" << std::endl;
    }
    // Print a last row of dashes so that the board looks complete.
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

// Moves the numbers in a single vector as front as possible ignoring zeros.
// Param:serie: contains the numbers of a row or a column
// on the board in normal or reversed order, depending on the direction the tiles are going to move.
void moveNumbers(std::vector<NumberTile> &serie){

        std::vector<int> numbers = {};

        // Makes a copy of the param:serie.
        for (auto i : serie)
            numbers.push_back(i.getValue());

        int index = 0;
        auto copy = numbers;
        // If the tile at index is zero, moves the following tiles one step to the front of the vector.
        // If not, numbers cant be moved and loop jumps to the next index.
        for (int i = 0; i < SIZE - 1; ++i){

            if (numbers.at(index) == 0){
                copy = numbers;
                for ( int j = index; j < SIZE; ++j ){

                    if (j + 1 == SIZE){
                        numbers.at(j) = copy.at(index);
                    }
                    else{
                        numbers.at(j) = copy.at(j + 1);
                    }
                }
            }
            else{
                index++;
            }
        }

        // Set the moved numbeback into the original param:serie.
        for (int k = 0; k < SIZE; ++k){
            serie.at(k).changeValue(numbers.at(k));
        }
    }

// Combines two tiles next to each other with the same value if moved towards each other.
// Param:serie: contains the numbers of a row or a column
// on the board in normal or reversed order, depending on the direction the tiles are going to move.
void combineTiles(std::vector<NumberTile> &serie){

    for ( int i = 0; i < SIZE - 1; ++i )
    {
        if (serie.at(i).getValue() != 0){
            if (serie.at(i).getValue() == serie.at(i+1).getValue()){
                serie.at(i).changeValue((serie.at(i).getValue() * 2));
                serie.at(i+1).changeValue(0);
            }
        }
    }
}

// Executes a complete move to desired direction on the board.
// Returns true if move succeeded and false if not.
bool make_a_move(std::vector<std::vector<NumberTile>> &board, std::string command){

    // Vertical moves (up and down) are quite similar. They are under the same if-structure
    // to shorten the code.
    if ((command == "w") or (command == "s")){
        // Processes one column at a time.
        for (int x = 0; x < SIZE; ++x){

            // Creates vector 'serie' of the numbers on the column. Functions moveNumbers() and
            //combineTiles() use this vector as a parameter.
            std::vector<NumberTile> serie = {};

            if(command == "w"){
                for (int y = 0; y < SIZE; y++){
                    serie.push_back(board.at(y).at(x));
                }
            }

            else{
                //If moved down, the numbers will be stored in reversed order.
                for (int y = SIZE - 1; y > -1; y--){
                    serie.push_back(board.at(y).at(x));
                }
            }

            moveNumbers(serie);
            combineTiles(serie);
            moveNumbers(serie);

            // Return the processed columns into the board.
            if(command == "w"){
                for (int i = 0; i < SIZE; ++i){
                    board.at(i).at(x) = serie.at(i);
                }
            }

            else{
                for (int i = 0; i < SIZE; ++i){
                    board.at(i).at(x) = serie.at(SIZE - 1 - i);
                }
            }

        }return true;

    }// Horizontal moves (left and right) are quite similar. They are under the same if-structure
    // to shorten the code.
    else if ((command == "a") or (command == "d")){

        // Processes one row at a time.
        for (int y = 0; y < SIZE; y++){

            // Creates vector 'serie' of the numbers on the row. Functions moveNumbers() and
            // combineTiles() use this vector as a parameter.
            std::vector<NumberTile> serie = {};

            if(command == "a"){
                for (int x = 0; x < SIZE; ++x){
                    serie.push_back(board.at(y).at(x));
                }
            }
            else{
                // If moved right, the numbers will be stored in reversed order.
                for (int x = SIZE - 1; x > -1; --x){
                    serie.push_back(board.at(y).at(x));
                }
            }
            moveNumbers(serie);
            combineTiles(serie);
            moveNumbers(serie);

            // Return the processed rows into the board.
            if(command == "a"){
                for (int i = 0; i < SIZE; ++i){
                    board.at(y).at(i) = serie.at(i);
                }
            }
            else{
                for (int i = 0; i < SIZE; ++i){
                    board.at(y).at(i) = serie.at(SIZE - 1 - i);
                }
            }

        } return true;

    }else {
        std::cout << "Error: unknown command." << std::endl;
        return false;
    }
}

// Checks the situation on the board and ends the game if necessary (win or lose).
// Returns true if so, and false if the game is to be continued.
// Param:goal is the value to get in order to win the game.
bool gameOver(std::vector<std::vector<NumberTile>> &board, int goal){

    bool zeros_found = false;
    // Goes trough every single tile on the board.
    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++){

           if (board.at(y).at(x).getValue() == goal){
               print(board);
               std::cout<< "You reached the goal value of "<< goal << "!" << std::endl;
               return true;
           }

           else if (board.at(y).at(x).getValue() == 0){
               zeros_found = true;
           }
        }
    }
    if (!zeros_found){
        std::cout<< "Can't add new tile, you lost!"<< std::endl;
        return true;
    }

    return false;
}

// Asks the user for optional goal, else it will be the DEFAULT_GOAL.
// Returns the desired goal.
int getGoal(){

    std::cout << "Give a goal value or an empty line: ";
    std::string input = "";
    getline(std::cin, input);
    int goal;

    if(input == "") {
        goal = DEFAULT_GOAL;
    }else
        goal = stoi(input);
    return goal;
}


int main(){

    // Declare the board and randomengine.
    std::vector<std::vector<NumberTile>> board;
    std::default_random_engine randomEng;
    // And initialize the disrt to give numbers from the correct
    std::uniform_int_distribution<int> distr(0, SIZE - 1);

    initBoard(board, randomEng, distr);
    int goal = getGoal();
    print(board);

    for ( ;; ){
        std::cout << "Dir> ";
        std::string command = "";
        getline(std::cin, command);
        if (command == "q"){
            return 0;
        }
        if (make_a_move(board, command)){
            if (gameOver(board, goal)){
                break;
            }
            newValue(board, randomEng, distr);
            print(board);
        }
    }
}
