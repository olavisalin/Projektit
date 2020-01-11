/* Module: Library
 * ---------------
 * Library system that can be used to look at books and borrower accounts.
 * Students should expand this system to handle book loaning as well.
 * ---------------
 *
 *
 * (Add your info ( name, email, student number) and a short
 * description / comment of your solution here.)
 *
 *
 * ---------------
 * TIE-0220x S2019
 * */
#ifndef LIBRARY_HH
#define LIBRARY_HH
#include "book.hh"
#include "loan.hh"
#include "date.hh"

#include <string>
#include <vector>
#include <map>

// Forward declaration of Person class.
// If this concept feels odd, there's a short bit of material of it
// in PLUS 4.5: the waterdrop game.
class Person;

// All error messages.
const std::string MISSING_AUTHOR_ERROR = "Error: Book must have at least one author.";
const std::string DUPLICATE_PERSON_ERROR = "Error: People should have unique names.";
const std::string CANT_FIND_BOOK_ERROR = "Error: Can't find book with given title.";
const std::string CANT_FIND_ACCOUNT_ERROR = "Error: Can't find account with given name.";
const std::string ALREADY_LOANED_ERROR = "Error: Book is already loaned.";
const std::string OUT_OF_RENEWALS_ERROR = "Error: Loan is out of renewals.";
const std::string LOAN_NOT_FOUND_ERROR = "Error: Loan can't be found from the system.";

// And additional prints.
const std::string RENEWAL_SUCCESSFUL = "Renewal was successful. New due date: ";
const std::string RETURN_SUCCESSFUL = "Return was completed successfully.";
const std::string LOAN_INFO = "Book title : Borrower : Due date : Is late";
const std::string SEPARATOR_LINE = "--------------------------------------------";

class Library
{
public:
    Library();
    ~Library();    

    // Adds a book to the library datastructure.
    bool add_book(const std::string& title, const std::vector<std::string> authors,
                  const std::string& description,
                  const std::set<std::string> genres = {});
    // Adds a borrower account to the library.
    void add_borrower(const std::string& name,
                      const std::string& email = "",
                      const std::string& address = "");

    // Prints only the titles of all books.
    void all_books();
    // Prints all books with additional information.
    void all_books_with_info();
    // Prints all borrowers' names.
    void all_borrowers();
    // Prints all borrowers with additional information.
    void all_borrowers_with_info();

    // Sets the today's date to given date.
    void set_date(int day, int month, int year);
    // Advances today's date by param days.
    void advance_date(int days);

    // Student's should complete the following functions:

    // Should print LOAN_INFO and all loaned books in the format described.
    // If there's no loans, prints nothing.
    void loaned_books();

    // Should print all books loaned by borrower in
    // the format: " title : due date : is late "
    // If borrower can't be found, prints an appropriate error.
    void loans_by(const std::string& borrower);

    // Loans a book with title and sets the borrower as borrower_id.
    // If book/borrower can't be found, or book is already loaned, prints
    // an appropriate error.
    void loan(const std::string& book_title, const std::string& borrower_id);

    // Renews the loan if there's renewals remaining.
    // Prints RENEWAL_SUCCESSFUL or if any error happened, an appropriate error.
    void renew_loan(const std::string& book_title);

    // Returns a loan. If no errors occured, prints RETURN_SUCCESSFUL.
    // If any error happened, prints an appropriate error message.
    void return_loan(const std::string& book_title);

private:
    // Today's date.
    Date* today_;
    // All books in the library system.
    std::map<std::string, Book*> books_;
    // All authors in a map
    std::map<std::string, Person*> authors_;
    // All accounts of borrowers.
    std::map<std::string, Person*> accounts_;
    // All loans currently active.
    std::map<std::string, Loan*> loans_;

};

#endif // LIBRARY_HH
