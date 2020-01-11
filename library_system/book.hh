/* Module: Book
 * ------------
 * Represents a single book in the library.
 *
 * TIE-0220x S2019
 * */
#ifndef BOOK_HH
#define BOOK_HH

#include "person.hh"

#include <string>
#include <set>
#include <vector>


class Book
{
public:
    Book(const std::string& title,
         std::vector<Person*> authors,
         std::string description = "",
         std::set<std::string> genres = {});
    ~Book();

    // Self-descriptive getters
    std::string get_title() const;
    std::vector<Person*> get_authors() const;
    std::set<std::string> get_genres() const;

    // Prints the neatly formatted info of the book
    void print_info() const;

    // Self-descriptive search funcs.
    bool has_keyword( const std::string& keyword ) const;
    bool has_author( Person* author ) const;
    bool has_genre( const std::string& genre ) const;

private:
    std::string title_;
    std::vector<Person*> authors_;
    std::string description_;
    std::set<std::string> genres_;
};

#endif // BOOK_HH
