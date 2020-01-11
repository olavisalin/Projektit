#include "file_reader.hh"
#include "date.hh"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

// Simple split
void split(const std::string& line, std::vector<std::string>& result,
           char separator = ';'){
    result.clear();
    result.push_back("");
    for ( char c : line ){
        if ( c == separator ){
            result.push_back("");
        } else {
            result.back().push_back(c);
        }
    }

    if ( result.size() > 0 && result.back() == "" ){
        result.erase(--result.end());
    }
}

bool read_books(std::shared_ptr<Library> lib){
    std::string book_input = "";
    // Choose the name of the file
    if(DEFAULT_DATA) {
        book_input = BOOKS_FILE_NAME;
    } else {
        std::cout << BOOKS_FILE_PROMPT;
        std::getline(std::cin, book_input);
    }
    std::ifstream books(book_input);
    // Check that the files exist
    if ( !books ){
        std::cout << FILE_ERROR << book_input << std::endl;
        return false;
    }

    std::vector<std::string> fields = {};
    std::vector<std::string> authors = {};
    std::vector<std::string> genres = {};
    std::string line = "";
    // For each line in the file:
    while ( getline(books, line) ){
        // Split the line
        split(line, fields);
        // Check the size
        if ( fields.size() != 4 ){
            std::cout << INCORRECT_FORMAT << std::endl;
            return false;
        }
        // Check for empty fields
        for ( std::string field : fields ){
            if ( field.empty() ){
                std::cout << INCORRECT_FORMAT << std::endl;
                return false;
            }
        }
        // Split the fields that contains multiple inputs
        split(fields.at(1), authors, ',');
        split(fields.at(3), genres, ',');

        // Move the genres from vector to a set
        std::set<std::string> genres_in_set;
        for ( std::string genre : genres){
            genres_in_set.insert(genre);
        }

        // Add the book to the library
        lib->add_book(fields.at(0), authors, fields.at(2), genres_in_set );
    }
    return true;
}

bool read_borrowers(std::shared_ptr<Library> lib){
    std::string borrower_input = "";
    // Choose the file name
    if(DEFAULT_DATA) {
        borrower_input = BORROWERS_FILE_NAME;
    } else {
        std::cout << BORROWERS_FILE_PROMPT;
        std::getline(std::cin, borrower_input);
    }
    // Check that the file exists
    std::ifstream borrowers(borrower_input);
    if ( !borrowers ){
        std::cout << FILE_ERROR << borrower_input << std::endl;
        return false;
    }

    std::vector<std::string> fields = {};
    std::string line = "";
    // For each line in the input
    while( getline(borrowers, line) ){
        // Split the line
        split(line, fields);
        // Check its size
        if ( fields.size() != 3 ){
            std::cout << INCORRECT_FORMAT << std::endl;
            return false;
        }
        // Check for empty fields
        for ( std::string field : fields ){
            if ( field.empty() ){
                std::cout << INCORRECT_FORMAT << std::endl;
                return false;
            }
        }
        // And add the borrower
        lib->add_borrower(fields.at(0), fields.at(1), fields.at(2));
    }
    return true;
}

// If everything goes right, return true.
bool read_file_to_lib(std::shared_ptr<Library> lib){
    return read_books(lib) && read_borrowers(lib);
}

