/* Module: file_reader
 * -------------------
 * Reads the data files and parses them to commands the library module
 * can understand and use to populate itself.
 *
 * TIE-0220X S2019
 * */
#ifndef FILE_READER_HH
#define FILE_READER_HH
#include "library.hh"
#include <string>
#include <memory>

// True if default input files exist and the aim is to use them.
// If you toggle this off, toggle it back on to true before submitting the
// project work.
const bool DEFAULT_DATA = true;

const std::string BOOKS_FILE_PROMPT = "Give a name for the books input file: ";
const std::string BORROWERS_FILE_PROMPT = "Give a name for the borrowers input file: ";

const std::string BOOKS_FILE_NAME = "books.input";
const std::string BORROWERS_FILE_NAME = "borrowers.input";

const std::string FILE_ERROR = "Error: Can't read file: ";
const std::string INCORRECT_FORMAT = "Error: File has an erroneous line.";

/* Reads the input files to empty lib object, that's given as a shared_ptr.
 *
 * If error happens while reading, error msg is printed and false is returned.
 * Continuing the program execution is not adviced.
 * */
bool read_file_to_lib(std::shared_ptr<Library> lib);

#endif // FILE_READER_HH
