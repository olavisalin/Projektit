/* Main.cpp
 * --------
 * Creates the library object, uses the file_reader module to init the obj and
 * starts the cli module.
 *
 * TIE-0220x S2019
 * Name: Olavi Salin
 * Student number: 284132
 * UserID: salino ( Necessary due to gitlab folder naming. )
 * E-Mail: olavi.salin@tuni.fi
 * */
#include "file_reader.hh"
#include "cli.hh"
#include <iostream>

using namespace std;

int main()
{
    // Create the library and store it in a shared pointer.
    std::shared_ptr<Library> lib(new Library);
    // If we can't read the files, return error.
    if ( !read_file_to_lib(lib) ){
        return EXIT_FAILURE;
    }
    // Otherwise, start the cli.
    Cli cli(lib);
    while( cli.exec_prompt() ){}
    return EXIT_SUCCESS;
}
