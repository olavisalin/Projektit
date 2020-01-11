/* Module: Loan
 * ------------
 * Represent a single loan that is not yet returned.
 *
 * TIE-0220x S2019
 * */
#ifndef LOAN_HH
#define LOAN_HH

#include "book.hh"
#include "date.hh"
#include "person.hh"

#include<vector>
#include<string>

const int DEFAULT_RENEWAL_AMOUNT = 6;

class Loan
{
public:
    // Constructor.
    Loan(Book* title, Person* borrower, std::vector<int> borrow_date);
    ~Loan();

    // Attributes of the class that library needs to use.
    Person* borrower_;
    Date* due_to_;
    int renews_left_;

    // Prints the information of a loan in desired format. Print_borrower tells
    // if the borrower should be printed (cases: loaned_books and loans_by).
    void print_info(Date& today, bool print_borrower);

private:
    Book* title_;

    // Self-descriptive.
    bool is_late(Date& another);
};

#endif // LOAN_HH
