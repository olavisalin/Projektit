/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 * */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>


NumberTile::NumberTile(int value, int x, int y )
    : value_(value), x_(x), y_(y){}

void NumberTile::print(int width){
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    std::cout << "|" << std::setw(width - 1) << value_;
}


bool NumberTile::setValue(int value){

    if (value_ == 0) {
        value_ = value;
        return true;

    } else {
        return false;
    }
}

int NumberTile::getValue(){
    return this->value_;
}

void NumberTile::changeValue(int value){
    value_ = value;
}
