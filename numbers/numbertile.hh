/* Class: Numbertile
 *
 * Acts as a single tile in the board.
 *
 * Students can modify both parts of the class and add their own variables
 * and methods. Implementations for the methods should be in the source file.
 *
 * */
#ifndef NUMBERTILE_HH
#define NUMBERTILE_HH
#include <utility>
#include <vector>

class NumberTile
{
public:
    // Public part contains variables and methods that can be used outside the
    // class itself.

    /* About pairs: the elements in a pair can be accessed with pair.first
    * and pair.second. If you do not wish to use pairs, you can modify the
    * given code to work without. Just replace the pair-parameter here & in the
    * source file with "int y, int x" and then modify the main.cpp in the
    * indicated spot.
    * */
    // Constructor that takes in a value and coordinates.
    NumberTile(int value, int x, int y);

    // Prints the tile in the desired width.
    void print( int width );

    // Tries to set a new value to the tile. Returns true if successful, false
    // if the tile already contains some value.
    bool setValue( int value );
    
    // Returns the value of the tile.
    int getValue();

    // Sets a desired value to the tile.
    void changeValue(int value);
private:

    // Value of the tile.
    int value_;

    // X-coordinate of the tile.
    int x_;

    // Y-coordinate of the tile.
    int y_;
};

#endif // NUMBERTILE_HH
